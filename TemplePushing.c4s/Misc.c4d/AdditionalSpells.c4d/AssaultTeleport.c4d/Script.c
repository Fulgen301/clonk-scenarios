/*-- Teleport --*/

#strict 2

func Range() { return 225; }

protected func Activate(object pCaster, object pRealCaster)
{
	// Effekt erzeugen
	if (!pRealCaster) pRealCaster = pCaster;

	var target = FindObject2(Find_Distance(Range()), Find_OCF(OCF_CrewMember), Find_Hostile(GetOwner(pRealCaster)), Sort_Distance());
	if (!target) return 0;

	var preferredDir = (GetXDir(target) / Abs(GetXDir(target))) || -1 * (GetDir(target) || -1);

	var solid = false;
	var deltax;
	var deltay;
	for (deltax = 8; (GetX(target) + deltax < LandscapeWidth() || GetX(target) - deltax > 0) && !solid; deltax += 10)
	{
		for (deltay = 10; GetY(target) + deltay < LandscapeHeight() && deltay < Range() && !solid; deltay += 10)
		{
			if (target->GBackSolid(preferredDir * deltax + 1, deltay) && target->GBackSolid(preferredDir * deltax - 1, deltay)) solid = preferredDir;
			else if (target->GBackSolid(-preferredDir * deltax + 1, deltay) && target->GBackSolid(-preferredDir * deltax - 1, deltay)) solid = -preferredDir;
			if (solid) break;
		}
		if (solid) break;
	}

	if (!solid) return 0;

	var oldx = GetX(pRealCaster);
	var oldy = GetY(pRealCaster);

	var dir = -1;
	if (GetDir(target) == DIR_Left) dir = 1;

	SetSpeed(0, 0, pRealCaster);
	SetPosition(GetX(target) + deltax * solid, GetY(target) + deltay, pRealCaster);
	while (pRealCaster->Stuck()) SetPosition(GetX(pRealCaster), GetY(pRealCaster) - 1, pRealCaster);
	pRealCaster->SetDir(GetX(target) > GetX(pRealCaster));
	pRealCaster->SetComDir(COMD_Up);

	for (var cnt = 0; cnt < 5; cnt++)
	{
		CreateParticle("PSpark", AbsX(oldx + RandomX(-5, 5)), AbsY(oldy + RandomX(-10, 10)), 0, 0, 150, GetColorDw(pRealCaster));
		CreateParticle("PSpark", AbsX(GetX(pRealCaster) + RandomX(-5, 5)), AbsY(GetY(pRealCaster) + RandomX(-10, 10)), 0, 0, 150, GetColorDw(pRealCaster));
	}

	Sound("Scream");
	return RemoveObject();
}


func FxScheduledRemoveStop(target, effect, reason, temp)
{
	if (temp) return;
	if (!target) return;
	target->RemoveObject();
}

/* Zaubercombo */

public func GetSpellClass(object pMage) { return(AIR1); }
public func GetSpellCombo(pMage) { return ("222"); } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
