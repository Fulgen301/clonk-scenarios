/* Clonk */

#strict 2

#appendto CLNK

local teamHud;
local rotateInJump;
local removeOnDeath;

protected func Initialize()
{
	teamHud = CreateObject(THUD);
	teamHud->Attach(this);
	AddEffect("CheckStuck2", this, 20, 1, this);
	AddEffect("CheckBurn", this, 101, 0, this);
	SetPhysical("Fight", 75000, PHYS_Temporary, this);
	SetPhysical("Scale", 60000, PHYS_Temporary, this);
	SetPhysical("Hangle", 60000, PHYS_Temporary, this);
	SetPhysical("Energy", 100000, PHYS_Temporary, this);
	SetPhysical("CanScale", 1, PHYS_Temporary, this);
	SetPhysical("CanHangle", 1, PHYS_Temporary, this);
	DoEnergy(100, this);
	return _inherited(...);
}

/*
protected func ControlThrow(object byObj)
{
	// First check if the clonk already handles the throw control
	var ret = _inherited(byObj);
	if (ret) return ret;

	// Launch arrow from pack in inventory
	var arrowPack = Contents();
	if (!arrowPack || !arrowPack->~IsArrowPack()) return 0;
	arrowPack->Activate(this);
	return 1;
}
*/

protected func ControlSpecial()
{
	[$Push$|Image=CXIV]

	if (GetAction() != "Walk") return 0;

	// Use action "Throw" starting with phase 3
	SetAction("Throw");
	SetPhase(3);

	// Find clonks in range
	var clonks = FindObjects(
		Find_ID(CLNK),
		Find_InRect(-20 + GetDir() * 29, 0, 12, 10),
		Find_OCF(OCF_Alive),
		Find_Hostile(GetOwner()),
		Find_Not(Find_Action("Tumble")));
		
	if (GetLength(clonks) == 0) return 0;

	// Randomly select clonk to be pushed
	var target = clonks[Random(GetLength(clonks))];
	var effect;
	if(effect = GetEffect("StoneShieldPSpell", target))
	{
		EffectCall(target, effect, "Damage", -12000, FX_Call_EngGetPunched);
	}
	else
	{
		Fling(target, -1 + GetDir() * 2, -1);
		target->SetKiller(GetOwner());
	}

	return 1;
}

protected func ControlLeft()
{
	if (rotateInJump && GetAction() == "Jump" || GetAction() == "Tumble") SetDir(DIR_Left);
	return _inherited();
}

protected func ControlRight()
{
	if (rotateInJump && GetAction() == "Jump" || GetAction() == "Tumble") SetDir(DIR_Right);
	return _inherited();
}

protected func Death(int killedBy)
{
	var ret = _inherited(killedBy);
	if (teamHud) RemoveObject(teamHud);
	if (removeOnDeath) RemoveObject();
	return ret;
}

public func QueryCatchBlow(object arrow)
{
	if (arrow->~QueryOwnCatchBlow(this)) return 1;
	return _inherited(arrow, ...);
}

private func FxCheckStuck2Timer(object pTarget, int iEffectNumber, int iEffectTime)
{
	if (GetAction(pTarget) != "Walk") return;

	var d = GetDir(pTarget)*2 - 1;
	if (!pTarget->GBackSolid(0, 4) && !pTarget->GBackSolid(d, 3) && pTarget->GBackSolid(d, 4))
	{
		SetPosition(GetX(pTarget), GetY(pTarget) - 1, pTarget);
		ObjectSetAction(pTarget, "KneelDown");
		pTarget->Schedule("SetXDir(0)", 1);
		if ((d == -1 && GetComDir(pTarget) != COMD_Left) || (d == 1 && GetComDir(pTarget) != COMD_Right)) SetComDir(COMD_Up, pTarget);
	}
}

func FxCheckBurnEffect(string newEffectName, object target, int effectNumber, int newEffectNumber, int causedBy, bool fBlasted, object incineratingObject)
{
	if (newEffectName == "Fire" && incineratingObject && incineratingObject->~QueryIncinerateObject(target)) return FX_Effect_Deny;
}

func ShowTeamHUD(string text)
{
	if (teamHud) teamHud->Show(text, 72);
}

func Collection(object obj)
{
	obj->~Entrance2(this);
	return _inherited(obj, ...);
}
