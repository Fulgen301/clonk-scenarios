/*-- Suizid --*/

#strict

protected func Activate(iPlr)
{
  Log("$MsgSuicide$", GetPlayerName(iPlr));
  DoEnergy(-GetEnergy(GetCursor(iPlr)), GetCursor(iPlr));
  return(1);
}
