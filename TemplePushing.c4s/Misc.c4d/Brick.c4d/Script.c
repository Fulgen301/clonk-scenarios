/*-- Brick --*/

#strict 2

local yMin, yMax;

protected func Initialize()
{
	SetAction("Flying");
	SetPhase(Random(2));
	SetDir(Random(2)); 
	ContactTop(); 
	yMin = 100;
	yMax = 650;
}

protected func ContactBottom() { SetYDir(-10); }
protected func ContactTop() { SetYDir(10); }

func CheckHit()
{
	if (GetXDir() == 0 && GetYDir() == 0)
	{
		SetXDir(RandomX(-100, 100));
		SetYDir(RandomX(-100, 100));
	}
	if (GetY() >= yMax) ContactBottom(); 
	if (GetY() <= yMin) ContactTop(); 
}

protected func IgnoreFloatSpell() { return true; }
