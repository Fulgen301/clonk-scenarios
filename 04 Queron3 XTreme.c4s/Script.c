/*-- Queron --*/

// script v3.6 by miniwipf
#strict 2

static const C4P_Host = 0;

static g_aClonksOnRelaunch;
static g_iRelaunchNumber; // Anzahl Relaunches
static g_fGameOptionsDone;

static const VIEW_range = 300;

/*--------------------------------/ ENGINE /----------------------------------*/

protected func Initialize()
{
  if (!CheckVersion())
    return;
  // Szenario: Landschaft und Objekte erzeugen
  if (!GetScenarioVal("NoInitialize", "Head")) Scenario();
  SetPlayList("*");
  Music("01 Maus.ogg");
  // Statics initialisieren
  g_aClonksOnRelaunch = [KNIG, ASAS, PLDN, MAGE, KING];
  g_iRelaunchNumber = GetLength(g_aClonksOnRelaunch)-1;
  g_fGameOptionsDone = 0;
  return 1;
}

/*--------------------------------/ PLAYER /----------------------------------*/

protected func InitializePlayer(int iPlr, x, y, base, int iTeam)
{
	// FOW aktivieren
	SetFoW(1, iPlr);
	var crew = GetCrew(iPlr);
	// Einstellungen
	if (!g_fGameOptionsDone) {
		// Spieler-Blind-Effekt :D
		SetPlrViewRange(-1, crew);
		// Der Host kriegt das Menü
		if (iPlr == C4P_Host) return crew -> HostMenu();
		else return PlrMessage("@Der Host stellt gerade alles Nötige ein. Wenn er damit fertig ist geht's endlich los!", iPlr);
	}
	else
		return PostInitializePlayer(iPlr);
}

public func OnGameOptionsDone()
{
	// Change Color
	for(var pObj in FindObjects(Find_Owner(NO_OWNER))) {
		pObj->SetClrModulation(RGB(0,0,255));
	}

    Sound("Kleiner_Hai_Mixed", 1);
	g_fGameOptionsDone = 1; // Einstellungen abgeschlossen
	// Und los gehts
	// Alle Spieler joinen
	for (var i=0, plr; i < GetPlayerCount(); i++) {
		plr = GetPlayerByIndex(i);
		if (GetPlayerTeam(plr) < 0) return; // Noch am Teamwählen
		GameCall("PostInitializePlayer", plr);
	}
        var a;
        CheckItems(a);
}

public func PostInitializePlayer(int iPlr)
{
	// Team-Relaunches aufstocken
	g_aTeamData[GetPlayerTeam(iPlr)][0] += g_iRelaunchNumber;
	FindObject(SBRD) -> UpdatePlayer(iPlr, SBRD_dwRelaunches);
	// Spielerobjekt entfernen
	var crew = GetCrew(iPlr);
	RemoveObject(crew);
	// Und joinen
	return JoinPlayer(iPlr);
}

private func JoinPlayer(int iPlr, bool fRejoin)
{
	var clonk = JoinClonk(iPlr);
	if (!clonk) return;
	if (!fRejoin) {
		SetCursor(iPlr, clonk, 1, 1);
		SetPlrView(iPlr, clonk);
	}
	// Warten bis zum Launch
	var time = 15+iPlr;
	if (fRejoin) time += 50; // Zusatzzeit um dem gestorbenen Clonk zu gedenken
	AddEffect("IntWait2Launch",, 75, 5,,, iPlr, time);
	return 1;
}

private func JoinClonk(int iPlr)
{
	var ID = g_aClonksOnRelaunch[g_aPlayerData[iPlr][0]];
	// Relaunchposition mithilfe eines Testclonks bestimmen
	var tester, x, y, f;
	while (1) {
		tester = PlaceAnimal(CLNK);
		f = AckPos(x, y, tester);
		RemoveObject(tester);
		if (f) break; // Relaunchposition ok
	}
	var clonk = CreateObject(ID, x, y, iPlr);
	MakeCrewMember(clonk, iPlr);
	// Nach der Geburt ist man ja noch blind
	SetPlrViewRange(-1, clonk);
	// Clonk aufpumpen
	DoEnergy(100, clonk);
	DoBreath(100, clonk);
	// Relaunch-Checker
	AddEffect("IntTrackClonk", clonk, 500);
	if (ID == MAGE)
		; //DoMagicEnergy(50, clonk, 1);
//	if (ID == ASAS)
//		clonk -> Hide(true, false, true); // Tarnen
	// Waffenauswahlmenü öffnen
	clonk -> WeaponMenu();
	// Clonk ist bis zum Launch bewegungsunfähig
	AddEffect("IntInactive", clonk, 50,, clonk);
	return clonk;
}

private func AckPos(& iX, & iY, object pClonk)
{
	iX = GetX(pClonk);
	iY = GetDefBottom(pClonk);
	// Bedinungen
	if (!Stuck(pClonk))
	if (!Inside(iX, 1060, 1060+200) && !Inside(iY, 940, 940+50)) // Höhle rechts unten
	if (!Inside(iX, 1160, 1160+190) && !Inside(iY, 670, 670+210)) // Dach vom rechten Burgturm
	if (!Inside(iX, 640, 640+30) && !Inside(iY, 420, 420+30)) // Geheimkammer in der Burg
	if (!Inside(iX, 30, 30+220) && !Inside(iY, 440, 440+510)) // Dach vom Turm links
	if (!Inside(iX, 920, 920+1090) && !Inside(iY, 0, 70)) // Dach vom rechten Burgturm
	return 1;
}

public func LaunchPlayer(int iPlr)
{
	// Alle inaktiven Clonks launchen
	for (var i=0, clonk; i < GetCrewCount(iPlr); i++) {
		clonk = GetCrew(iPlr, i);
		if (GetEffect("IntInactive", clonk)) LaunchClonk(clonk);
	}
}

public func LaunchClonk(object pClonk)
{
	var plr = GetOwner(pClonk);
	// Los geht's
	PlrMessage("$MsgGo$", plr);
  RemoveEffect("IntInactive", pClonk);
  // Clonk soll anhalten, sonst fällt er nur runter :/
  SetComDir(COMD_Stop, pClonk);
	AddEffect("FadeFoW2", pClonk, 150, 2, pClonk,, -1, VIEW_range, 20); // Vorhang auf
  // Scoreboard anpassen (Clonktyp anzeigen)
	FindObject(SBRD) -> UpdatePlayer(plr, SBRD_dwCaption);
	// Assas haben das ganze Spektakel nicht so gern :>
	if (GetID(pClonk) == ASAS) return 1;
	// Sound
	Sound("PlayerJoin",, pClonk);
	// Effekte
	pClonk -> CastParticles("PxSpark", 50, 100,,, 5*8, 5*50, RGB(196, 196, 196), RGB(255, 255, 255));
  for (var i = 0; i < 5; i++)
    pClonk -> DrawParticleLine("PSpark", RandomX(-200, 200), -400,,, 8, 150 + 100*!Random(3), RGBa(255, 50+Random(100), 50+Random(100), 255), RGBa(50+Random(100), 200, 50+Random(100), 80));
	return 1;
}

// Callback

public func OnFoWFadeFinished(object pClonk)
{

	// Clonk nicht tot? Dann egal.
	if (GetAlive(pClonk)) return 1;
	var plr = GetOwner(pClonk);
	// Fokus auf den neuen Clonk
	var clonk = GetCrew(plr);
	SetCursor(plr, clonk, 1, 1);
	SetPlrView(plr, clonk);
	return 1;
}

// Callbacks

protected func OnClonkDeath(object pClonk)
{
	// Damit der Cursor auf dem toten Clonk hängen bleibt
	return SetCursor(GetOwner(pClonk), pClonk);
}

/*--------------------------------/ EFFEKTE /---------------------------------*/

// IntTrackClonk

global func FxIntTrackClonkStop(object pTarget, int iNr, int iReason, bool fTemp)
{
	// Temporäre Effekte ignorieren
	if (fTemp) return;
	if (iReason != 4) {
		if (Contained(pTarget) || GetID(pTarget) == CITB)
			pTarget ->~Death(); // So tun als ob der Clonk sterben würde
		else return;
	}
	var plr = GetOwner(pTarget), team = GetPlayerTeam(plr);
	var killer = GetKiller(pTarget), killerteam = GetPlayerTeam(killer);

	// Wer hats getan?
	Sound("hobbyarschficker", 1);
	if (GetPlayerName(killer)) {
		if (killer != plr) {
			if (team != killerteam) {
				Log(["$MsgKill$", "$MsgKill2$", "$MsgKill3$"][Random(3)], GetTaggedPlayerName(killer), GetTaggedPlayerName(plr));
				// +1 Kill für Killer
				++g_aPlayerData[killer][1];
				++g_aTeamData[killerteam][1];
				FindObject(SBRD) -> UpdatePlayer(killer, SBRD_dwKills);
				// Sound
				Sound("1Up",, pTarget,, killer+1);
				// Nachricht
				CastMsg("$MsgPlusKill$", GetCursor(killer), 0xffff00);
				// Bonusgeld
				DoWealth(killer, 50);
			}
			else Log(["$MsgTeamkill$", "$MsgTeamkill2$", "$MsgTeamkill3$"][Random(3)], GetTaggedPlayerName(killer), GetTaggedPlayerName(plr));
		}
		else Log(["$MsgSuicide$", "$MsgSuicide2$", "$MsgSuicide3$"][Random(3)], GetTaggedPlayerName(plr));
	}
	else Log(["$MsgDeath$", "$MsgDeath2$", "$MsgDeath3$"][Random(3)], GetTaggedPlayerName(plr));

	// Letztes Mannschaftsmitglied tot?
	if (GetCrewCount(plr) == 1)
		if (GetCrew(plr) == pTarget) {
			// +1 Tod für den Besitzer und sein Team
			++g_aPlayerData[plr][0];
			FindObject(SBRD) -> UpdatePlayer(plr, SBRD_dwRelaunches);
			if (g_aPlayerData[plr][0] > g_iRelaunchNumber) return 1; // Kein Relaunch mehr übrig!
			// Spieler relaunchen
			GameCall("JoinPlayer", plr, 1);
		}
	// Effekt
	AddEffect("FadeFoW2", pTarget, 150, 2, pTarget,, VIEW_range, -1, 5);
	return 1;
}

global func FxIntTrackClonkDamage(object pTarget, int iNr, int iDmg, int iCause)
{
	if (!iDmg || iCause == 1337) return; // Kein Schadensabzug (Wtf Callback??)
	var plr = GetOwner(pTarget), team =  GetPlayerTeam(plr);
	var dmgr = GetKiller(pTarget), dmgrteam = GetPlayerTeam(dmgr);

	// Energieveränderung berechnen
	var change = BoundBy(GetEnergy(pTarget)+iDmg*100/GetPhysical("Energy",, pTarget), 0, GetPhysical("Energy",, pTarget)*100/100000)-GetEnergy(pTarget);
	// .. und anzeigen
	var txt = Format("%d", change);
	if (change > 0) txt = Format("+%s", txt);
	CastMsg(txt, pTarget, GetPlrColorDw(plr), 1);

	// Wer ist schuld?
	if (GetPlayerName(dmgr)) {
		if (dmgr != plr) {
			if (team != dmgrteam) {
				// + Punkte für den Schadner
				DoWealth(dmgr, -change);
			}
			else DoWealth(dmgr, change); // Punktabzug
		}
		else DoWealth(dmgr, change); // Punktabzug
	}
	return iDmg;
}


// IntInactive

global func FxIntInactiveStart(object pTarget, int iNr, int iTemp)
{
	if (!pTarget) return -1;
	// Clonk inaktiv machen
	pTarget -> SetObjectStatus(C4OS_INACTIVE); DoBreath(100, pTarget); // Der Clonk verschluckt sich manchmal
	return 1;
}

global func FxIntInactiveStop(object pTarget, int iNr, int iReason, bool fTemp)
{
	// Clonk reaktivieren
	pTarget -> SetObjectStatus(C4OS_NORMAL);
    if (GetID(pTarget) == ASAS)
    {
      SetPhysical("Energy", GetPhysical("Energy", PHYS_Permanent, pTarget) * 3 / 5, PHYS_Temporary, pTarget);
      pTarget->~Hide(true, false, true);
    }
	return 1;
}

// IntWait2Launch

global func FxIntWait2LaunchStart(object pTarget, int iNr, int iTemp, int iPlr, int iTime)
{
	if (iTemp) return;
	g_aPlayerData[iPlr][4] = iTime;
	EffectVar(0, pTarget, iNr) = iPlr;
	// Zeit anzeigen
	EffectCall(pTarget, iNr, "ShowTime");
	return 1;
}

global func FxIntWait2LaunchTimer(object pTarget, int iNr, int iTime)
{
	var plr =  EffectVar(0, pTarget, iNr);
	// Spieler eliminiert?
	if (!GetPlayerName(plr)) return -1; // Effekt löschen
	// Zeit prüfen
	if (!--g_aPlayerData[plr][4]) return -1;
	EffectCall(pTarget, iNr, "ShowTime");
	return 1;
}

global func FxIntWait2LaunchStop(object pTarget, int iNr, int iReason, bool fTemp)
{
	if (fTemp) return;
	var plr = EffectVar(0, pTarget, iNr);
	GameCall("LaunchPlayer", plr);
	return 1;
}

global func FxIntWait2LaunchShowTime(object pTarget, int iNr)
{
	var plr = EffectVar(0, pTarget, iNr);
	// Nachricht + Scoreboard
	PlayerMessage(plr, Format("$MsgTimeToRelaunch$", g_aPlayerData[plr][4]));
	FindObject(SBRD) -> UpdatePlayer(plr, SBRD_dwCaption);
	return 1;
}


// Fade FOW
// ACHTUNG: ViewRange = 0 entspricht kein Kriegsnebel!

global func FxFadeFoW2Effect(string szNewName, object pTarget, int iNr, int iNewNr)
{
	// Mehrere gleiche Effekte sind ungesund: Platz machen für neuen Effekt
	if (szNewName == GetEffect(, pTarget, iNr, 1))
		return RemoveEffect(, pTarget, iNr);
}

global func FxFadeFoW2Start(object pTarget, int iNr, int iTemp, int iStartRange, int iEndRange, int iVelocity)
{
	if (iTemp) return;
	// Init
	EffectVar(0, pTarget, iNr) = iStartRange;
	EffectVar(1, pTarget, iNr) = iEndRange;
	EffectVar(2, pTarget, iNr) = iVelocity;
	// Startwert setzen
	SetPlrViewRange(iStartRange, pTarget, 1);
	return 1;
}

global func FxFadeFoW2Timer(object pTarget, int iNr, int iTime)
{
	// Neue Sichtweite berechnen
	var s = EffectVar(0, pTarget, iNr);
	var e = EffectVar(1, pTarget, iNr);
	var v = EffectVar(2, pTarget, iNr);
	var newR;
	if (s < e) newR = BoundBy(s+v*iTime, s, e);
	else newR = BoundBy(s-v*iTime, e, s);
	if (newR) // 0 überspringen
		SetPlrViewRange(newR, pTarget, 1);
	if (newR == e) return -1; // Zielrange erreicht
}

global func FxFadeFoW2Stop(object pTarget, int iNr, int iReason, bool fTemp)
{
	// Callback
	if (fTemp) return;
	GameCall("OnFoWFadeFinished", pTarget);
	return 1;
}

//AddEffect("FadeFoW2", this, 50, 1,,, 1, 500, 1)
