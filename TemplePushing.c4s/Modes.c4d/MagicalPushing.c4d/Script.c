/*-- Magical Mode --*/

#strict 2

static const MODE_Magic = MLPG;

protected func Activate(int player) { MessageWindow(GetDesc(), player); }

func ModeName() { return "$ModeName$"; }
func SpawnpointDefinitions() { return IIf(suddendeathEnabled, [[SCRL, 19]], [[SCRL, 19], [GBLT, 1]]); }
func SpawnpointInterval() { return 750; }

func Gamma() { return [RGB(5, 5, 10), RGB(80, 80, 150), RGB(200, 200, 255)]; }
