#strict 2
static const ICNA_Speed = 50,
	ICNA_AutoAimAngle = 30,
	ICNA_TurnSpeed = 1,
	ICNA_AutoAimDistance = 300,
	ICNA_Lifetime = 200;

local timer;
local iOldX, iOldY;
local iAngle;
local Caster;
local contacts;

func Initialize()
{
	iOldX = -1;
	iOldY = -1;
}

public func Activate(pCaster, Angle)
{
	iAngle = Angle;
	Caster = pCaster;
	Check();
}

protected func Check()
{
	var target = FindObject2(Find_Distance(ICNA_AutoAimDistance), Find_OCF(OCF_Alive), Find_OCF(OCF_CrewMember), Find_Hostile(GetOwner(Caster)), Find_NoContainer(), Find_Angle(iAngle - ICNA_AutoAimAngle, iAngle + ICNA_AutoAimAngle), Find_Exclude(Caster), Find_PathFree(this), Sort_Distance());

	if(target)
	{
		var angle = Angle(GetX(), GetY(), target->GetX(), target->GetY());
		var range1 = Angle360(iAngle) - ICNA_TurnSpeed;
		var range2 = Angle360(iAngle) + ICNA_TurnSpeed;
		iAngle = Angle180(BoundBy(angle, range1, range2));
	}

	var speed = ICNA_Speed;
	if (GetEffect("StopNSpell", this)) speed /= 2;

	SetR(iAngle);
	SetXDir(Sin(iAngle, speed));
	SetYDir(-Cos(iAngle, speed * 100) - 2 * GetGravity(), this, 1000);


	if (++timer > ICNA_Lifetime) RemoveObject();
	if (timer % 2)
	{
		CreateParticle("PSpark", 0, 0, 0, 0, 180, RGBpA(GetPlrColorDw(GetOwner()), 120));
		CreateParticle("FSSpark", 0, 0, 0, 0, 150, GetPlrColorDw(GetOwner()));
		CreateParticle("MaterialParticle2", 0, 0, RandomX(2, -2)-GetXDir()/2, RandomX(2, -2)-GetYDir()/2, 250, GetPlrColorDw(GetOwner()));
	}

	CheckHit();
	iOldX = GetX(); iOldY = GetY();
}

private func CheckHit()
{
	if (iOldX == -1 && iOldY == -1) return;
	var targets = FindObjects(Find_OnLine(AbsX(iOldX), AbsY(iOldY), 0, 0), Find_OCF(OCF_Alive), Find_OCF(OCF_CrewMember), Find_Hostile(GetOwner(Caster)), Find_NoContainer());
	if (FindObject2(Find_OnLine(AbsX(iOldX), AbsY(iOldY), 0, 0), Find_OCF(OCF_OnFire), Find_NoContainer())) return RemoveObject();
	if (GetLength(targets) > 0) return HitObject(targets[Random(GetLength(targets))]);
}

private func HitObject(living, pObj)
{
	if (living == Caster) return 0;
	CastParticles("MaterialParticle", 20, 50, 0, 0, 20, 60, GetPlrColorDw(GetOwner()), GetPlrColorDw(GetOwner()));
	Sound("Crystal2", this);
	// Schaden machen
	if(Caster)
	{
		Caster->Punch(living, RandomX(7, 12));
	}
	else
	{
		Punch(living, RandomX(7, 12));
	}
	if (!Frozen(living)) Freeze(living, Caster);
	return RemoveObject();
}


protected func Destruction()
{
	CreateParticle("PSpark", RandomX(-1, 2), RandomX(-2, 1), RandomX(-3, 2), RandomX(-2, 1), RandomX(150, 90), GetPlrColorDw(GetOwner()));
	CreateParticle("PSpark", RandomX(-2, 1), RandomX(-1, 2), RandomX(-2, 3), RandomX(-1, 2), RandomX(150, 90), GetPlrColorDw(GetOwner()));
}

func ContactLeft()
{
	CastParticles("MaterialParticle", 20, 50, 0, 0, 20, 60, GetPlrColorDw(GetOwner()), GetPlrColorDw(GetOwner()));
	if (Stuck(this) || ++contacts > 2)
	{
		return RemoveObject();
	}
	var contact = GetContact(this, 0, CNAT_Left | CNAT_Right | CNAT_Bottom | CNAT_Top);
	if (contact & (CNAT_Bottom | CNAT_Top))
	{
		iAngle = 180 - iAngle;
	}
	else if (contact & (CNAT_Left | CNAT_Right))
	{
		iAngle = -iAngle;
	}
	Sound("Crystal*", 0, this);
}
