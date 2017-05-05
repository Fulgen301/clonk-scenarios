/*-- Armbrust --*/

#strict 2

local iPower;
local iAngle;
local idBolt;
local iBoltIndex;

local pCrosshair;

/* Aktivieren (zum Zielen per Maussteuerung) */
public func Activate(pClonk)
{
  [$CtrlActivateDesc$]
  // Der Clonk kann dieses Objekt nicht verwenden
  if (!pClonk->~CanUse(GetID())) return 0;
  // Tr�ger nicht bereit zum neuen Zielen
  if (!pClonk->~ReadyToFire()) return;
  // Tr�ger: neue Zielaktion setzen
  if (!pClonk->~LoadCrossbow(1))
      return;
  // Fadenkreuz zum besseren Zielen erzeugen
  pCrosshair = CreateObject(WCHR, 0, 0, GetOwner(pClonk));
  pCrosshair->StartCheck("*Crossbow*", pClonk);
  iAngle = 84;
  ActualizePhase(pClonk);
  iPower = 100;
  // Munitionsid suchen
  idBolt = GetMunitionID();
  iBoltIndex = 0;
  if(idBolt) PlayerMessage(GetOwner(pClonk), "%s", this, GetName(0,idBolt));
  if(idBolt && idBolt->~GetMaxShootPower()) iPower = Min(iPower, idBolt->~GetMaxShootPower());
  // Erfolg
  return 1;
}

/* Spezialsteuerung durch Tr�ger */
public func ControlThrow(pClonk)
{
  // Tr�ger hat gezielt
  if (IsAiming())
    { Fire(pClonk); return(1); }
  // Bogen einsetzen
  return Activate(pClonk);
}

public func ControlUp (pClonk)               // hoch zielen
{
  AimUp(pClonk, 1, "ControlConf", CRBW);
}

public func ControlDown(pClonk)             // runter zielen
{
  AimDown(pClonk, 1, "ControlConf", CRBW);
}

public func ControlUpdate(object clonk, int comdir, bool dig, bool throw)
{
  AimUpdate(clonk, comdir, 1, "ControlConf", CRBW);
}

public func ControlConf(int conf, object clonk)
{
  if(clonk->GetAction() != "AimCrossbow" && clonk->GetAction() != "LoadCrossbow")
  {
    AimCancel(clonk);
  }
  else
  {
    // Feinere Abstufung mit JnR m�glich
    var angle_change;
    if(GetPlrCoreJumpAndRunControl(clonk->GetController()))
      angle_change = conf * 1;
    else
      angle_change = conf * 6;

    iAngle = BoundBy(iAngle + angle_change, 0, 140);
    ActualizePhase(clonk);
  }
}

public func ActualizePhase(pClonk)
{
  // Nur wenn noch gezielt/geladen wird
  if(!IsAiming() && !IsLoading()) return;

  // Phase des Clonks an Winkel anpassen
  if(GetAction(pClonk)=="AimCrossbow")
  {
    if(iAngle<6)       SetPhase(0, pClonk);
    else if(iAngle<24)  SetPhase(1, pClonk);
    else if(iAngle<36)  SetPhase(2, pClonk);
    else if(iAngle<48)  SetPhase(3, pClonk);
    else if(iAngle<72)  SetPhase(4, pClonk);
    else if(iAngle<90)  SetPhase(5, pClonk);
    else if(iAngle<108)  SetPhase(6, pClonk);
    else SetPhase(7, pClonk);
  }

  // Fadenkreuz anpassen
  var iDir = GetDir(pClonk); if(!iDir) iDir = -1;
  SetVertexXY(0, -Sin(iAngle, 40)*iDir, Cos(iAngle, 40), pCrosshair);

  // Schussparameter sammeln
  var iOutX, iOutY, iOutR, iOutXDir, iOutYDir, iOutRDir;
  GetCrossbowOut(this, iAngle, 0, iOutX, iOutY, iOutR, iOutXDir, iOutYDir, iOutRDir);
  iOutXDir *= iDir; iOutX *= iDir;
  // Farbe Gr�n beim Zielen oder Rot beim Laden
  var iColor = RGB(0, 255);
  if(pClonk->GetAction() == "LoadCrossbow") iColor = RGB(255);
  // Und los!
  AddTrajectory(pClonk, iOutX+GetX(pClonk), iOutY+GetY(pClonk), iOutXDir, iOutYDir, iColor);
}

public func ControlLeft(pClonk)
{
  // Tr�ger Zielaktion
  if (IsAiming() || IsLoading())
  {
    SetDir(DIR_Left, pClonk);
    ActualizePhase(pClonk);
    return 1;
  }
  // Keine Spezialsteuerung
  return 0;
}

public func ControlRight(pClonk)
{
  // Tr�ger Zielaktion
  if (IsAiming() || IsLoading())
  {
    SetDir(DIR_Right, pClonk);
    ActualizePhase(pClonk);
    return 1;
  }
  // Keine Spezialsteuerung
  return 0;
}

public func ControlDig(pClonk)
{
  // Tr�ger Zielaktion
  if (IsAiming() || IsLoading())
  {
    iPower += 10;
    var iMaxPower = 150;
    if(idBolt && idBolt->~GetMaxShootPower()) iMaxPower = idBolt->~GetMaxShootPower();
    if(iPower>iMaxPower) iPower = 50;
    ActualizePhase(pClonk);
    PlayerMessage(GetOwner(pClonk), "Power %d", pClonk, iPower);
    return 1;
  }
  // Keine Spezialsteuerung
  return 0;
}

public func ControlRightDouble(pClonk)
{
  // Zielaktion abbrechen
  if (IsAiming() || IsLoading())
  {
    pClonk->StopAiming();
    SetComDir(COMD_Right, pClonk);
  }
  // Keine Spezialsteuerung
  return 0;
}

public func ControlLeftDouble(pClonk)
{
  // Zielaktion abbrechen
  if (IsAiming() || IsLoading())
  {
    pClonk->StopAiming();
    SetComDir(COMD_Left, pClonk);
  }
  // Keine Spezialsteuerung
  return 0;
}

public func ControlSpecial(pClonk)
{
  if (IsAiming() || IsLoading())
  {
    // N�chste Munition
    iBoltIndex++;
    idBolt = GetMunitionID(iBoltIndex);
    if(idBolt) PlayerMessage(GetOwner(pClonk), "%s", this, GetName(0,idBolt));
    if(idBolt && idBolt->~GetMaxShootPower()) iPower = Min(iPower, idBolt->~GetMaxShootPower());
    ActualizePhase(pClonk);
    return 1;
  }
  return 0;
}

/* Wird gerade vom Tr�ger gezielt? */
public func IsAiming()
{
  if(!Contained()) return false;
	return (Contained()->~IsAiming());
}

public func IsLoading()
{
  if(!Contained()) return false;
	return (Contained()->~IsLoading());
}

/* Munitionssuche */
private func GetMunitionID(iIndex)
{
  if(!Contained()) return;
  var aAmmo = [], idTest, idFound, fFound;
  // Liste mit Munitionsid's machen
  for(var pObj in FindObjects(Find_Container(Contained()), Find_Or(Find_Func("IsBolt"), Find_Func("IsHook"), Find_Func("IsBoltPack"))))
  {
    // ID suchen
    idFound = GetID(pObj);
    if(pObj->~IsBoltPack()) idFound = pObj->~UnpackTo();
    // Haben wir die ID schon?
    fFound = 0;
    for(idTest in aAmmo)
      if(idTest == idFound) fFound = 1;
    if(!fFound) aAmmo[GetLength(aAmmo)] = idFound;
  }
  // den Eintrag mit passendem Index ausgeben
  return aAmmo[ Mod(iIndex, GetLength(aAmmo)) ];
}

// Haben wir noch was von der Munitionssorte?
private func CheckMunitionID(idID)
{
  // Liste mit Munitionsid's machen
  var idFound;
  for(var pObj in FindObjects(Find_Container(Contained()), Find_Or(Find_Func("IsBolt"), Find_Func("IsHook"), Find_Func("IsBoltPack"))))
  {
    // ID suchen
    idFound = GetID(pObj);
    if(pObj->~IsBoltPack()) idFound = pObj->~UnpackTo();
    // Ist die ID die gesuchte?
    if(idFound == idID) return 1;
  }
}

/* Pfeil abfeuern */
public func Fire()
{
  var pClonk = Contained();
  // Kein Tr�ger?
  if(!pClonk) return 0;
  // Im Geb�ude?
  if (pClonk->Contained()) { pClonk->~StopAiming(); return(0); }
  // Unvollst�ndig?
  if (~GetOCF() & OCF_Fullcon) return 0;
  // Noch beim Nachladen
  if (GetAction() == "Reload") return 0;
  // Pfeil vom Tr�ger holen
  var pArrow = pClonk->~GetBolt(idBolt);
  if (!pArrow)
  {
    // andere Munition?
    ControlSpecial(Contained());
    pArrow = pClonk->~GetBolt(idBolt);
    // wohl doch nicht :-(
    if (!pArrow)
      return 0;
  }
  // Beim Tr�ger ggf. Bogen wieder ausw�hlen
  ShiftContents(pClonk, 0, CRBW);
  // Austrittsgeschwindigkeit ermitteln
  var iOutX, iOutY, iOutR, iOutXDir, iOutYDir, iOutRDir;
  var iDir = GetDir(pClonk); if(!iDir) iDir = -1;
  GetCrossbowOut(this, iAngle, 0, iOutX, iOutY, iOutR, iOutXDir, iOutYDir, iOutRDir);
  iOutXDir *= iDir; iOutX *= iDir; iOutR *= iDir;
  // Besitzer des Projektils setzen
  pArrow->SetOwner(Contained()->GetOwner());
  // Pfeil abfeuern
  Exit(pArrow, iOutX,iOutY,iOutR, 0,0,iOutRDir );
  pArrow->SetXDir(iOutXDir); pArrow->SetYDir(iOutYDir);
  pArrow->~Launch(pClonk);
  // Sicht verfolgen
  if (GetPlrView(GetController(pClonk)) != 2)
    SetPlrView(GetController(pClonk), pArrow);
  // Sound
  Sound("Crossbow*");
  // Nachladen
  if(!pArrow->~IsSilent())
  ActualizePhase(pClonk);
  // Munitionscheck
  if(!CheckMunitionID(idBolt))
  {
    // Leer? Dann andere Munition
    ControlSpecial(Contained());
  }
  // Fertig!
  return 1;
}

/* Ausgangsgeschwindigkeit und -position, wenn der Ritter mit dem Bogen in angegebene Richtung schie�t */
public func GetCrossbowOut(pBow, iAngle, fDeviate, &iOutX, &iOutY, &iOutR, &iOutXDir, &iOutYDir, &iOutRDir)
  {
  // Austrittsgeschwindigkeit ermitteln
  iOutXDir = Sin(iAngle, iPower);
  iOutYDir = -Cos(iAngle, iPower);
  // Austrittsposition...
  iOutX = Sin(iAngle, 25 * GetCon() / 100);
  iOutY = -Cos(iAngle, 25 * GetCon() / 100);
  // Pfeildrehung
  iOutR = iAngle;
  if(iAngle > 0) iOutRDir = 3; else iOutRDir = -3;
  // Fertig
  return 1;
  }


/* Pfeil abfeuern */
public func FireAngle(iAngle)
{
  var pClonk = Contained();
  // Kein Tr�ger?
  if(!pClonk) return 0;
  // Im Geb�ude?
  if (pClonk->Contained()) { pClonk->~StopAiming(); return(0); }
  // Unvollst�ndig?
  if (~GetOCF() & OCF_Fullcon) return 0;
  // Noch beim Nachladen
  if (GetAction() == "Reload") return 0;
  // Pfeil vom Tr�ger holen
  var pArrow = Contained()->~GetBolt(idBolt);
  if (!pArrow) return;
  // Beim Tr�ger ggf. Bogen wieder ausw�hlen
  ShiftContents(Contained(), 0, CRBW);
  // Austrittsgeschwindigkeit ermitteln
  var iOutX, iOutY, iOutR, iOutXDir, iOutYDir, iOutRDir;
  pClonk->~GetCrossbowOut(this, iAngle, true, iOutX, iOutY, iOutR, iOutXDir, iOutYDir, iOutRDir);
  // Besitzer des Projektils setzen
  pArrow->SetOwner(Contained()->GetOwner());
  // Pfeil abfeuern
  Exit(pArrow, iOutX,iOutY,iOutR, 0,0,iOutRDir );
  pArrow->SetXDir(iOutXDir); pArrow->SetYDir(iOutYDir);
  pArrow->~Launch(pClonk);
  // Sound
  Sound("Crossbow*");
  // Nachladen
  // Munitionscheck
  if(!CheckMunitionID(idBolt))
  {
    // Leer? Dann andere Munition
    ControlSpecial(Contained());
  }
  return 1;
}


/* Anz�nden: Verbrannte Aktion zur Markierung, dass er unbenutzbar ist */

protected func Incineration()
  {
  return SetAction("Burned");
  }

/* Aufwertungszauberkombo: Mit Armbrust wird der Clonk zum Assassinen */
public func GetRevaluationCombo(object pClonk) { return ASAS; }

/* Kann geschmiedet werden */
public func IsAnvilProduct() { return 1; }
