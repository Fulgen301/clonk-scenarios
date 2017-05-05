/*-- Classic Mode --*/

#strict 2

static const MODE_Classic = CLSC;

protected func Activate(int player) { MessageWindow(GetDesc(), player); }

func ModeName() { return "$ModeName$"; }
func SpawnpointDefinitions() { return [[ROCK, 5], [SCRL, 5], [FLNT, 4], [SFLN, 9], [STFN, 3], [EFLN, 5], [FBMP, 4]]; }
func SpawnpointInterval() { return 800; }
