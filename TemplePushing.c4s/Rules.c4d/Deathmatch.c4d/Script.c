/*-- Deathmatch --*/

#strict 2

protected func Activate(int player)
{
	MessageWindow(Format("$InfoMessage$", deathmatchWinScore), player);
}
