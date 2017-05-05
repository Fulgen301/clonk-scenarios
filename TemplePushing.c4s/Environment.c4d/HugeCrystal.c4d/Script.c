/*-- Riesiger Kristall --*/

#strict 2

func Set(int phase, int size, int rotation, int dir, int color)
{
	SetAction("Be");
	SetPhase(phase);
	SetCon(size);
	SetR(rotation);
	SetDir(dir);
	SetClrModulation(color);
}

func IsDecorativeCrystal() { return true; }
