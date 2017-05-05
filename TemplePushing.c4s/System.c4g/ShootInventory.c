/*-- Make Clonks able to shoot certain objects --*/

#strict 2

#appendto AXE1
#appendto EGBL
#appendto SFLN
#appendto EFLN
#appendto GBLT
#appendto ROCK
#appendto SWOR
#appendto SPER
#appendto TSWB
#appendto METO

local shotFrame, shooter;

protected func Activate(object clonk)
{
	[$Shoot$|Image=GNPW]

	// Sound
	if (GetID() == EGBL)
	{
		Sound("Blast*");
		Sound("Crystal3");
	}
	else if (GetID() == SPER)
	{
		Sound("Arrow");
	}
	else if (GetID() == TSWB)
	{
		Sound("Arrow");
	}
	else if (GetID() == GBLT)
	{
        Sound("Blast*");	
		Sound("Crystal3");
	}
	else if (GetID() == SWOR)
	{
		Sound("Blast*");
		Sound("SwordHit*");
	}
	else if (GetID() == AXE1)
	{
		Sound("Blast*");
		Sound("AxeHit*");
	}
	else
	{
		Sound("Blast*");
	}

	// Make shooting clonk responsible for possible kill and owner of object to be shot
	SetController(clonk->GetOwner());
	SetOwner(clonk->GetOwner());

	// Shoot
	if (GetID() == EGBL)
	{
		Exit(0, -10 + 20 * clonk->GetDir());
		SetYDir(-10);
		SetXDir(-100 + 200 * clonk->GetDir());
	}
	else if (GetID() == ROCK)
	{
		Exit(0, -10 + 20 * clonk->GetDir());
		SetYDir(-15);
		SetXDir(-100 + 200 * clonk->GetDir());
	}
	else if (GetID() == TSWB)
	{
		Exit(0, -7 + 14 * clonk->GetDir());
		SetYDir(-30);
		SetXDir(-50 + 100 * clonk->GetDir());
	}
	else if (GetID() == SPER)
	{
		Exit(0, -10 + 20 * clonk->GetDir(), -4, 0 + 180 * clonk->GetDir(), -150 + 300 * clonk->GetDir(), -7);
		SetYDir(-7);
		SetXDir(-175 + 350 * clonk->GetDir());
	}
	else
	{
		Exit(0, -10 + 20 * clonk->GetDir(), 0, 0 + 360 * clonk->GetDir(), -80 + 160 * clonk->GetDir(), -15);
		SetYDir(-15);
		SetXDir(-80 + 160 * clonk->GetDir());
	}

	shotFrame = FrameCounter();
	shooter = clonk;
	
	return 1;
}

func QueryOwnCatchBlow(object target)
{
	return target == shooter && FrameCounter() - shotFrame < 3;
}
