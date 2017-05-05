/*-- Ambient rain effect for Temple Ruins --*/

#strict 2

global func FxRainStart()
{
	return 1;
}

global func FxRainTimer()
{
	for (var i; i < 3; ++i)
	{
		CreateParticle("Raindrop", Random(LandscapeWidth()), 0, 0, 200, Random(300), RGB(170, 170, 255));
	}
	if (!Random(200)) Sound("Thunders*");
	return 1;
}

global func FxFireRainTimer()
{
	if (!Random(50)) CreateObject(DFLM, Random(LandscapeWidth()), 0, NO_OWNER);
	return 1;
}