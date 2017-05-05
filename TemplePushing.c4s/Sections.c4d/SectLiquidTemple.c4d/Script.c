/*-- Liquid temple scenario section --*/

#strict 2

// public func SectionName() { return "LiquidTemple"; }

 public func SpawnpointLocations() { return [[100, 515], [290, 490], [480, 460], [180, 315], [370, 285], [1440, 515], [1250, 490], [1060, 460], [1360, 315], [1170, 285], [715, 330], [685, 420], [770, 90], [715, 210], [825, 390], [825, 270], [825, 150]]; } 
 
 protected func Initialize()
{
	if (ambienceEnabled)
	{
		// Create lava rain
		if (mode != MODE_Festive) AddEffect("LavaRain", 0, 20, 1);
		
		/*
		for (var i; i < 300; ++i)
		{
			CreateParticle("Fog", Random(LandscapeWidth()), Random(LandscapeHeight()) + 300, 0, 1, RandomX(2000, 2500));
		}
		*/
	}
	
	if (mode == MODE_Apocalyptic)
	{	
		// Modulate brick colour (material)
		SetMaterialColor(Material("Brick"), 100, 0, 0, 150, 0, 0, 20, 0, 0);
	}
	
	if (mode == MODE_Festive)
	{
		// Modulate colours
		SetSkyAdjust(RGB(90,90,255));
		SetMaterialColor(Material("Brick"), 150, 150, 255, 150, 150, 255, 150, 150, 255);
	}
}

public func SectionAmbienceSounds()
{
	return [["LiquidAmbience.ogg", 50], ["Rain.ogg", 10]];
}
