/*-- Crystal Spike --*/

#strict 2

local iMaxTime;

public func IsBigCrystal() { return 1; }

func Initialize()
{
	SetGraphics(["A", "B", "C", "D"][Random(4)], this, GetID(), 1, GFXOV_MODE_ExtraGraphics);
	SetAction("Bohr");
	return 1;
}

public func Set(int inMaxTime)
{
	iMaxTime = inMaxTime;
	return 1;
}

func StossEffect()
{
	for (var pClonk in FindObjects(Find_Distance(20), Find_OCF(OCF_Living), Find_NoContainer(), Find_Hostile(GetOwner())))
	{
		if (GetAlive(pClonk))
		{
			if (!GetEffect("NoCrystalAttack", pClonk)) HitObject(pClonk);
		}
	}
	for (var pDing in FindObjects(Find_Distance(30), Find_Category(C4D_Object), Find_NoContainer(), Find_Not(Find_ID(QBCY)), Find_Not(Find_Procedure("ATTACH"))))
	{
		HitDing(pDing);
	}

	CreateParticle("Smoke", 0, +21, RandomX(-4, 4), -5, 80, RGB(120, 120, 120));
}

func ExistTimer()
{
	if (!Random(4)) Sound("Sparkle");
	CreateParticle("NoGravSpark", RandomX(-8, 8), RandomX(-28, 26), 0, -5, RandomX(10, 30), GetTeamColor(GetPlayerTeam(GetOwner())));

	for (var pClonk in FindObjects(Find_Distance(40), Find_OCF(OCF_Living), Find_NoContainer()))
	{
		if (GetAlive(pClonk)) EffectObject(pClonk);
	}

	if (iMaxTime > 0)
	{
		if (GetActTime() > iMaxTime) SetAction("Remove");
	}
}

global func CreateBigCrystal(int iX, int iY, int iCon, int iMTime, int iOwner)
{
	var pCrys = CreateObject(QBCY, iX, iY, iOwner);
	pCrys->Set(iMTime);
	SetCon(iCon, pCrys);
	return pCrys;
}

func HitObject(object pClonk)
{
	Sound("Crystal2", 0, pClonk);
	DoEnergy(-20, pClonk);
	Fling(pClonk, RandomX(-4, 4), RandomX(-5, -9));
	AddEffect("NoCrystalAttack", pClonk, 100, 20, pClonk);
}

func HitDing(object pDing)
{
	SetSpeed(RandomX(-4, 4), RandomX(-20, -40), pDing);
	pDing->~Hit();
}

func EffectObject(object pClonk)
{
	CreateParticle("NoGravSpark", GetX() - GetX(pClonk) + RandomX(-8, 8), GetY() - GetY() + RandomX(-12, 12), 0, -5, RandomX(10, 20), GetColorDw(this));
	if (!Hostile(GetOwner(), GetOwner(pClonk))) DoEnergy(1, pClonk);
	else DoEnergy(-2, pClonk);
}

func RemoveMe()
{
	RemoveObject(this);
}

func SoundBamm()
{
	Sound("RockBreak*");
	Sound("Blast2", 0, 0, 50);
}
