/*-- Apocalyptic Mode --*/

#strict 2

static const MODE_Apocalyptic = APCE;

protected func Activate(int player) { MessageWindow(GetDesc(), player); }

func Initialize()
{
	AddEffect("CreateTeraFlints", 0, 20, 90);
	AddEffect("ShakeScreen", 0, 20, 50);
	AddEffect("Bottom", 0, 20, 2);
	AddEffect("SkyAdjust", 0, 20, 1);
	
	FindObjects(Find_Func("IsDecorativeCrystal"), Find_Func("SetClrModulation", RGB(255, 50, 50)));
}

func ModeName() { return "$ModeName$"; }
func NoSpawnpoints() { return true; }
func NoCorpses() { return true; }
func AmbienceSounds() { return [["ExtremeAmbience.ogg", 75]]; }
