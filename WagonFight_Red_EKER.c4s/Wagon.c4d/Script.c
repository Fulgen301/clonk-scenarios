/*--- Waggon ---*/

#strict
local mode;

public func Initialize()
{
	if (!FindObject(0, -80, -28, 160, 28, OCF_Alive))
		if (FindObject(WAGN, -20, -14, 40, 28))
			RemoveObject();
	SetAction("Fly");
	SetMode(WMODE_RED);
	/*
	if (!Random(28)) {
		SetMode(1);
	}
	if (!mode)
		if (!Random(28)) {
			SetMode(2);
		}
  */
}


public func Fade()
{
	AddEffect("Fade", this(), 20, 1, this());
	Set(dir);
}

static const WMODE_RED = 1;
static const WMODE_BLUE = 2;

public func SetMode(imode)
{
	mode = imode;
	if (imode == WMODE_RED)
	{
		SetClrModulation(RGB(250, 0, 0));
	}
	if (imode == WMODE_BLUE)
	{
		SetClrModulation(RGB(100, 100, 250));
	}
	Set(dir); // for good measure
}

public func FadeIn()
{
	SetMode(WMODE_RED);
	if (!Random(2))
		SetMode(WMODE_BLUE);
	AddEffect("FadeIn", this(), 20, 1, this());
	SetSolidMask();
	Set(dir);
}

public func FxFadeInTimer(pTarget, iNumber)
{
	EffectVar(1, this(), iNumber) += 23;
	if (mode == WMODE_BLUE)
		SetClrModulation(RGBa(100, 100, 250, 253 - EffectVar(1, this(), iNumber)), pTarget);
	else if (mode == WMODE_RED)
		SetClrModulation(RGBa(250, 0, 0, 253 - EffectVar(1, this(), iNumber)), pTarget);
	else 
		SetClrModulation(RGBa(250, 250, 250, 253 - EffectVar(1, this(), iNumber)), pTarget);
	if (253 - EffectVar(1, this(), iNumber) == 0)
	{
		SetSolidMask(0, 0, 40, 28);
		return -1;
	}
}

public func FxFadeTimer(pTarget, iNumber)
{
	EffectVar(1, this(), iNumber)++;
	SetClrModulation(RGBa(250, 250, 250, EffectVar(1, this(), iNumber)), pTarget);
	if (EffectVar(1, this(), iNumber) == 255)
		RemoveObject(pTarget);
}

public func Set(iDir)
{
	if (iDir == 0)
		SetComDir(COMD_Left);
	if (iDir == 1)
		SetComDir(COMD_Right);
}

public func Damage(iDmg, iTyp)
{
	SetController(iTyp);
	if (GetEffect("Fade", this()))
		return 1;
	if (mode == WMODE_RED)
		Do();
	if (mode == WMODE_BLUE)
		Do2();
	if (GetDamage() > 29)
	{
		for (var obj in FindObjects(Find_AtRect(-24, -18, 48, 36))) 
			obj->Schedule(Format("SetKiller(%d)", GetController()), 2, 1);
		//SetController(GetController(),obj);
		Incinerate();
	}
}

public func Do()
{
	CastObjects2(FLNT, 7, 15, 0, 0, GetController());
	CastParticles("Splinter", 3, 70, 0, 0, 70, 120, RGB(250, 250, 250), RGB(250, 250, 250));
	Explode(15);
	for (var obj in FindObjects(Find_AtRect(-24, -18, 48, 36))) 
		obj->Schedule(Format("SetKiller(%d)", GetController()), 2, 1);
	//SetController(GetController(),obj);
}

public func Do2()
{
	RGBa();
	CastObjects(_SPK, 5 + Random(2), 15);
	CreateObject(COKI, 0, 0, -1);
	CastParticles("Splinter", 3, 70, 0, 0, 70, 120, RGB(250, 250, 250), RGB(250, 250, 250));
	Explode(15);
	for (var obj in FindObjects(Find_AtRect(-24, -18, 48, 36))) 
		obj->Schedule(Format("SetKiller(%d)", GetController()), 2, 1);
}