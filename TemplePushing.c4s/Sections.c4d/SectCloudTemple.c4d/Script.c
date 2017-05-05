/*-- Cloud temple scenario section --*/

#strict 2

public func SectionName() { return "CloudTemple"; }

public func SpawnpointLocations() { return [[70, 100], [140, 310], [1105, 310], [431, 443], [830, 160], [420, 160], [300, 90], [230, 440], [320, 310], [530, 90], [625, 160],[720, 90], [930, 310], [820, 440], [950, 90], [1180, 100], [1020, 440]]; } 

protected func Initialize()
{
	if (ambienceEnabled)
	{
		// Create "Clouds"	
		for (var i; i < 60; ++i)
		{
			if (mode == MODE_Apocalyptic)
			{
				CreateParticle("Fog3", Random(LandscapeWidth()), RandomX(570, 700) -10, 0, 0, RandomX(1250, 2000), RGBa(200,0,0,60));
			}
			else
			{
				CreateParticle("Fog3", Random(LandscapeWidth()), RandomX(570, 700) -10, 0, 0, RandomX(1250, 2000));
			}
		}
		
		// Create sun and lenseflare
		if (mode != MODE_Festive)
		{
			CreateObject(SONE, 0, 0, NO_OWNER);
			CreateObject(LENS, 0, 0, NO_OWNER);
		};
		
		SetSkyParallax(0, 0, 0, 2, 0, 0, 0);
		
		// Create crystals
		CreateObject(BCRY, LandscapeWidth()/2, 171, NO_OWNER);
		// CreateObject(BCRS, 100, 100, NO_OWNER);
	}

	if (mode == MODE_Apocalyptic)
	{	
		SetSkyParallax(0, 0, 0, 5, 0, 0, 0);
		
		// Modulate brick and crystal colour
		SetMaterialColor(Material("Brick"), 100, 0, 0, 150, 0, 0, 20, 0, 0);
		SetMaterialColor(Material("SkyCrystal"), 245, 0, 0, 255, 0, 0, 20, 0, 0);
		
		// Modulate huge/giant crystal colour - work in progress!
		
	}
	
	if (mode == MODE_Festive)
	{	
		// Modulate material colour
		SetMatAdjust(RGBa(175, 230, 255, 55));
		
		// Modulate crystal colour
		SetClrModulation(RGBa(175, 230, 255, 55), FindObject(BCRY));	
	}
}

public func SectionAmbienceSounds()
{
	return [["CloudAmbience.ogg", 50]];
}
