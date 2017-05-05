/*-- Medieval Mode --*/

#strict 2

static const MODE_Knightly = MKNI;

protected func Activate(int player) { MessageWindow(GetDesc(), player); }

func ModeName() { return "$ModeName$"; }
func SpawnpointDefinitions() { return [[SFLN, 3], [EFLN,3], [SWOR, 5], [AXE1, 5], [SPER, 2], [ARWP, 5], [SCRL, 5], [FARP, 3]]; }
func SpawnpointInterval() { return 800; }

//TODO: Ambience, Festive Clonks
