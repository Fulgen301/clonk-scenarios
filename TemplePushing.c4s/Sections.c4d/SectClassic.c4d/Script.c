/*-- Classic scenario section --*/

#strict 2

public func SectionName() { return "Classic"; }

public func SpawnpointLocations() { return [[550, 282], [603, 205], [682, 282], [784, 227], [912, 168], [1040, 120],
	[648, 460], [432, 438], [170, 118], [299, 170], [441, 230], [1170, 290], [105, 375], [910, 400], [560, 610], [1040, 530], [300, 530], [780, 530], [1040, 400]]; }

protected func Initialize()
{
	// Moving bricks
	var bricks = [CreateObject(BRK2, 240, 150, NO_OWNER), CreateObject(BRK2, 970, 150, NO_OWNER)];

	if (ambienceEnabled)
	{	
		// Fog
		for (var i; i < 300; ++i)
		{
			CreateParticle("Fog", Random(LandscapeWidth()), Random(LandscapeHeight()) + 500, RandomX(3, 9), 0, RandomX(1000, 1500));
		}
		
		// Rain
		if (mode != MODE_Festive) AddEffect("Rain", 0, 20, 1);
		
		// Create sun and lenseflare
		if (mode != MODE_Festive)
		{
			CreateObject(SONE, 0, 0, NO_OWNER);
			CreateObject(LENS, 0, 0, NO_OWNER);
		}
	}
	
	if (mode == MODE_Apocalyptic)
	{
		// Modulate brick color (object + material)
		for (var brick in bricks)
		{
			brick->SetClrModulation(RGB(220, 20, 20));
		}
		
		SetMaterialColor(Material("Brick"), 100, 0, 0, 150, 0, 0, 20, 0, 0);
	}
	
	if (mode == MODE_Festive)
	{	
		// Modulate brick color (object + material)
		for (var brick in bricks)
		{
			brick->SetClrModulation(RGBa(125, 200, 255, 30));
		}
		
		// Modulate material colour
		SetMatAdjust(RGBa(125, 200, 255, 30));
	}
}

public func SectionAmbienceSounds()
{
	if (ambienceEnabled) return [["Ambience.ogg", 50], ["Rain.ogg", 75]];
	else return [["Ambience.ogg", 50]];
}
