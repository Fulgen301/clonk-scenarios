/*-- Ambient rain effect for Liquid Temple --*/

#strict 2

global func FxLavaRainStart()
{
	return 1;
}

global func FxLavaRainTimer()
{
	for (var i; i < 5; ++i)
	{
		CreateParticle("LavaRaindrop", Random(LandscapeWidth()), 0, 0, 200, Random(300), RGB(255, 255, 0));
	}
	return 1;
}
