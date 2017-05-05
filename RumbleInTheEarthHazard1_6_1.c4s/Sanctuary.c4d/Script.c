/* Zufluchtsort */

#strict

local homeCount;

func Countdown()
{
  if (homeCount < 0) return;

  var clonk = GetActionTarget();
  var text = Format("Du bist im Kampf gestorben.|Relaunch in %d Sekunden.", homeCount);

  if (!homeCount)
  {
    GameCall("ChooseClonk", clonk);
  }
  else
  {
    ClearMenuItems(clonk);  
    AddMenuItem("Relaunch", 0, 0, clonk, 0, 0, text);
  }
  homeCount--;
}
