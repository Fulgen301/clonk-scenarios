/* Zurückwerfen */

#strict 2

func Activate(pCaster,pRealcaster)
{
	var pClonk=pRealcaster;
	if(!pClonk) pClonk=pCaster;

	// Auswählen wenn möglich
	var comDir = pClonk->GetComDir();
	var selector;
	if ((selector = pClonk->~DoSpellSelect(this,300,pCaster)) && selector->CountTargets() > 1) return 1;
	if (selector)
	{
		pCaster->SpellSucceeded(GetID(), pClonk);
		RemoveObject(selector);
	}
	pClonk->SetComDir(comDir);

	// Clonk kann nicht auswählen: Clonk bekommst selbst ein Schild
	if (SelectorTarget(pClonk))
		return ActivateTarget(pClonk, pClonk);

	// ansonsten geth nich
	RemoveObject();
	return 0;
}

public func ActivateTarget(object pCaller, object pTarget)
{
	// Effekt geben
	AddEffect("DeflectionPSpell",pTarget,250,1,0,GetID());
	// Objekt löschen
	return RemoveObject();
}

public func SelectorTarget(object pTarget)
{
	// nur außerhalb von Gebäuden
	if(Contained(pTarget)) return;
	// muss ein Mannschaftsmitglied sein
	if(!(GetOCF(pTarget)&OCF_CrewMember)) return;
	// muss verbündet sein oder NTMG muss aktiviert sein
	if(Hostile(GetOwner(),GetOwner(pTarget)) && !ObjectCount(NTMG)) return;
	// sichtbar
	if(!Visible(GetOwner(),pTarget)) return;
	return 1;
}

func FxDeflectionPSpellStart(pClonk, iEffectNumber, iTemp)
{
	if(iTemp) return;
	// Zeit setzen
	EffectVar(0,pClonk,iEffectNumber)+=720;
}

func FxDeflectionPSpellTimer(pClonk, iEffectNumber, iEffectTime)
{
	// Zeit um
	if(!EffectVar(0,pClonk,iEffectNumber)--) return -1;
	// Nicht in Gebäuden
	if(Contained(pClonk)) return;
	var x = GetX(pClonk), y = GetY(pClonk), xdir = GetXDir(pClonk), ydir = GetYDir(pClonk);
	x = x + xdir/10;
	y = y + ydir/10;
	//Funken an der benötigten Stelle
	for(var pObj in FindObjects(Find_Not(Find_And(Find_Func("GetContact", 0, -1, CNAT_Bottom)), Find_Not(Find_Func("GetSpeed"))), Find_Layer(GetObjectLayer()), Find_NoContainer(), Find_Category(C4D_Object), Find_Distance(200, GetX(pClonk), GetY(pClonk)), Find_Not(Find_Distance(11, GetX(pClonk), GetY(pClonk)))))
	{
		// Wenn das Objekt auf den Clonk zufliegt
		if( (GetXDir(pObj)<GetXDir(pClonk)) == (GetX(pObj)>GetX(pClonk)) || (GetYDir(pObj)<GetYDir(pClonk)) == (GetY(pObj)>GetY(pClonk)))
		{
			var ox = GetX(pObj), oy = GetY(pObj), oxdir = GetXDir(pObj), oydir = GetYDir(pObj);
			ox = ox + oxdir/10;
			oy = oy + oydir/10;

			if(ObjectDistance(pClonk, pObj) > 21 && Distance(x, y, ox, oy) > 21) continue;

			// Eigenen Stab ignorieren
			if(GetEffect("StaffFlight", pObj))
				if(EffectVar(0, pObj, GetEffect("StaffFlight", pObj))==pClonk)
					continue;

			var objDirAngle = Angle180(Angle(GetXDir(pClonk), GetYDir(pClonk), GetXDir(pObj), GetYDir(pObj)));
			var objShieldAngle = Angle180(Angle(GetX(pClonk), GetY(pClonk), GetX(pObj), GetY(pObj)));
			var diffAngle = Angle180((objShieldAngle - objDirAngle) - 180);
			var exitAngle = objShieldAngle + diffAngle;
			var objSpeed = GetSpeed(pObj);
			var exitSpeed = Distance(0, 0, Sin(exitAngle, objSpeed) + GetXDir(pClonk), -Cos(exitAngle, objSpeed) + GetYDir(pClonk));

			if (Abs(diffAngle) >= 90) continue;

			SetSpeed(Sin(exitAngle, exitSpeed),-Cos(exitAngle, exitSpeed), pObj);

			CreateParticle("NoGravSpark", AbsX(GetX(pObj)), AbsY(GetY(pObj)), 0, 0, 80, RGB(80,50,50));
			if(!GetEffect("IntDeflected", pObj))
				EffectVar(0,pClonk,iEffectNumber) = Max(EffectVar(0,pClonk,iEffectNumber)-80,0);
			AddEffect("IntDeflected", pObj, 1, 20);
			Sound("Rip", 0, pObj);
		}
	}
	// Partikel Kreiseffekt
	if(iEffectTime % 4) return;
	var iAngle = (iEffectTime*10) % 360;
	var px= Sin(iAngle, 15);
	var py= Cos(iAngle, 15);
	CreateParticle("NoGravSpark", px+GetX(pClonk), py+GetY(pClonk), 0, 0, 50, RGB(50,80,50), pClonk);
	CreateParticle("NoGravSpark",-py+GetX(pClonk), px+GetY(pClonk), 0, 0, 50, RGB(50,50,80), pClonk);
	CreateParticle("NoGravSpark",-px+GetX(pClonk),-py+GetY(pClonk), 0, 0, 50, RGB(50,80,50), pClonk);
	CreateParticle("NoGravSpark", py+GetX(pClonk),-px+GetY(pClonk), 0, 0, 50, RGB(50,50,80), pClonk);
	return 1;
}

private func FxDeflectionPSpellEffect(string szNewEffectName, object pTarget, int iNumber) 
{ 
	// Andere Effekte aufnehmen
	if(szNewEffectName == "DeflectionPSpell")
	{
		return -2;
	}
}

private func FxDeflectionPSpellAdd(object pTarget, int iNumber, string szNewEffectName, int iNewEffectTimer, int iChange0, int iChange1, int iChange2, int iTime) {
	// Effekt übernehmen
	EffectVar(0,pTarget,iNumber) += 360;
}

protected func FxDeflectionPSpellInfo() { return "{{MDFL}} $SpellInfo$"; }

/* Zaubercombo */

public func GetSpellStaff() { return SMAR; }
public func GetSpellStaffCombo() { return ("56"); } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
