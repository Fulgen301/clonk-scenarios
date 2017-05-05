/*-- Festive Mode --*/

#strict 2

static const MODE_Festive = FSTV;

protected func Activate(int player) { MessageWindow(GetDesc(), player); }

func Initialize()
{
	if (ambienceEnabled) CreateObject(SNOR, 0, 0, NO_OWNER);
	SetSkyAdjust(RGB(189, 189, 255));
	SetGamma(RGB(0, 0, 50), RGB(100, 100, 128), RGB(200, 200, 255));
	SetScrollSpells([MICS, ABLA, MFWV, MLGT, MGPL, ICNL, AFST, MDFL, MGCY, MATT]);
}

func ModeName() { return "$ModeName$"; }
func SpawnpointDefinitions() { return [[TSWB, 7], [SCRL, 5], [ICE1, 3]]; }
func SpawnpointInterval() { return 600; }
func AmbienceSounds() { return [["FestiveAmbience.ogg", 25]]; }
