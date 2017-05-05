/*-- Rule for toggling ambient music --*/

#strict 2

protected func Activate(int player) { GameCall("ToggleAmbienceSounds", player); }
