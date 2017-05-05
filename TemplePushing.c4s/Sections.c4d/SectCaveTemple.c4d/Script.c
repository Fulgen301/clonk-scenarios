/*-- Cave temple scenario section --*/

#strict 2

// public func SectionName() { return "Cave"; }

/*

public func SpawnpointLocations() { return [[550, 282], [603, 205], [682, 282], [784, 227], [912, 168], [1040, 120],
	[648, 460], [432, 438], [170, 118], [299, 170], [441, 230], [1170, 290], [105, 375], [910, 400], [560, 610], [1040, 530], [300, 530], [780, 530], [1040, 400]]; }

protected func Initialize()
{
	// Moving bricks
	var bricks = [CreateObject(BRK2, 240, 150, NO_OWNER), CreateObject(BRK2, 970, 150, NO_OWNER)];

	if (ambienceEnabled)
	{	
		// Ambiente!?
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

*/

public func SectionAmbienceSounds()
{
	if (mode == MODE_Festive) return [["FestiveAmbience.ogg", 25]];
	else if (mode == MODE_Apocalyptic) return [["ExtremeAmbience.ogg", 75]];
	else return [["CaveAmbience.ogg", 50], ["Rain.ogg", 75]];
}
