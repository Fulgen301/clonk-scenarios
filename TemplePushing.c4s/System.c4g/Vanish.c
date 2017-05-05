/*-- Make certain items vanish over time --*/

#strict 2

#appendto ARRW
#appendto FARW
#appendto TSWB
#appendto SPER
#appendto ICE1

protected func Hit()
{
	if (GetID() == FARW)
	{
		Schedule("CastParticles(\"MSpark\", 20, 5, 0, 0, 25, 30, RGBa(128,128,255,0), RGBa(255,255,255,127))", 69, 0, 0);
		Schedule("RemoveObject()", 70, 0, 0);
	}
	else if (GetID() == SPER)
	{
		Schedule("CastParticles(\"MSpark\", 20, 5, 0, 0, 25, 30, RGBa(255,128,128,0), RGBa(255,128,128,127))", 49, 0, 0);
		Schedule("RemoveObject()", 50, 0, 0);
	}
	else if (GetID() == TSWB)
	{
		CastParticles("Snow", 50, 20, 0, 0, 50, 80, RGBa(255,255,255,0), RGBa(255,255,255,0));
		RemoveObject();
	}
	else
	{
		CastParticles("MSpark", 20, 5, 0, 0, 25, 30, RGBa(128,128,255,0), RGBa(255,255,255,127));
		Schedule("RemoveObject()", 5, 0, 0);
		return _inherited();
	}
}


