/* Crystal Spikes */

#strict 2

public func Activate(pCaster, pRealCaster)
{
	if(pRealCaster) pCaster = pRealCaster;
	Sound("Magic1");
	
	// Effekt prüfen
	var iResult;
	if (iResult = CheckEffect("CrystallSpikesNSpell", 0, 75)) return(iResult!=-1 && RemoveObject());
	
	// Dinger erzeugen
	var iCount = RandomX(4,7);
	var sum = 0;
	
	for(var i = 0; i < iCount; i++)
	{
		sum += PlaceCrystal(5 * (i - i/2), -5, pCaster);
	}
	if(!sum) return 0;
	
	// Fertig; Zauber entfernen
	RemoveObject();
	return 1;
}

protected func PlaceCrystal(int startx, int starty, object pCaster)
{
	var dir = 2 * GetDir(pCaster) - 1;
	startx += dir * (!!Random(3) * 50 + RandomX(0, 125));

	var solid = false;
	var deltax;
	for (deltax = 0; deltax < 100 && !solid; deltax += (10 * RandomX(1, 3)))
	{
		for (var y = 0; GetY() + y < LandscapeHeight() && !solid; y += 10)
		{
			if (GBackSolid(startx + dir * deltax, y)) solid = true;
		}
	}
	var x = startx + dir * deltax;
	if (!solid || GetX() + startx >= LandscapeWidth() || GetX() + startx + LandscapeWidth() < 0) return;

	var y;
	solid = false;
	var free = false;
	var upy, downy;
	for (y = starty; GetY() + y > 0 && !free; --y)
	{
		if (!solid)
		{
			if (GBackSolid(x, y)) solid = true;
		}
		else
		{
			if (!GBackSolid(x, y))
			{
				free = true;
				upy = ++y;
			}
		}
	}
	var down = Random(2);
	if (!free || down)
	{
		solid = false;
		free = false;
		for (y = starty; GetY() + y < LandscapeWidth() && !solid; ++y)
		{
			if (!free)
			{
				if (!GBackSolid(x, y)) free = true;
			}
			else
			{
				if (GBackSolid(x, y))
				{
					solid = true;
				}
			}
		}
		if (!solid)
		{
			if (!upy)
			{
				return;
			}
			else y = upy;
		}
		else
		{
			downy = y;
		}
	}
	if (upy && downy && down) y = downy;

	CreateBigCrystal(x, y + 3, RandomX(50, 100), RandomX(100, 200), GetOwner());
	return 1;
}

public func GetSpellClass(object pMage) { return(EART); }
public func GetSpellCombo(pMage) { return ("244"); } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)

