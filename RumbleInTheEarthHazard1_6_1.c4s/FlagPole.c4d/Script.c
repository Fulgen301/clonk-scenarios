/* Flag Pole */

#strict

local flag;

func CreateFlag(color)
{
  flag = CreateObject(FL5B, 16, -37, GetOwner());
  flag -> SetColorDw(color);
}

func Grabbed(clonk, grab)
{
  if (grab) SetAction("SwapFlag", clonk);
}

func Swapping()
{
  var clonk = GetActionTarget();

  var b1 = GetAction(clonk) ne "Push";
  var b2 = GetActionTarget(0, clonk) != this();

  if (b1 || b2) { SetAction("Idle"); return; }

  var bunker = FindObject2(Find_ID(CB5B), Find_Distance(100));
  var newOwner = GetOwner(clonk);
  var newColor = GetTeamColor(GetPlayerTeam(newOwner));

  if (GetPlayerTeam(newOwner) == GetPlayerTeam(GetOwner(bunker))) return;

  if (newColor == GetColorDw(flag)) 
  {   
    if (GetY(flag) == GetY() - 37) // Fahne ist oben
    {
      // Fahne oben -> Bunker eingenommen!
      bunker -> SetOwner(newOwner);
      GameCall("UpdateBunkerMenu");

      var s1 = GetTeamName(GetPlayerTeam(newOwner));
      var s2 = GetPlayerName(newOwner);
      var s3 = GetName(bunker);

      Log("<c ffff00>%ser soldier %s captured the %s!</c>", s1, s2, s3);      
      Sound("Trumpet", 1);
    }
    else
    {
      // eigene Fahne hissen
      SetPosition(GetX(flag), GetY(flag) - 1, flag);
    }
  }
  else
  {
    if (GetY(flag) == GetY()) // Fahne ist unten
    {
      // Fahnen wechseln
      flag -> SetColorDw(newColor);
    }
    else
    {
      // keine Fahne oben -> Bunker gehört keinem Team mehr
      if (GetOwner(bunker) > -1) bunker -> SetOwner(NO_OWNER);
      GameCall("UpdateBunkerMenu");

      // Fahne des Gegners einholen
      SetPosition(GetX(flag), GetY(flag) + 1, flag);
    }
  }
}