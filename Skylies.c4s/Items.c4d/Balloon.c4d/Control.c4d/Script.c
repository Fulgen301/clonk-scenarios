/*-- Removal Tool --*/

#strict
local toRem;

func Initialize()
{
  return(1);
}

func SetToRem(pToRem)
{
  toRem = pToRem;
}

func Activate(pCaller)
{
  SetPlrView(GetOwner(pCaller), toRem);
  CreateMenu(GetID(), pCaller, , C4MN_Extra_None, "Zerstören?", , C4MN_Style_Normal, false);
  AddMenuItem("Zerstören!", "Boom", BLND, pCaller, 0, 0, "Soll der Ballon zerstört werden und das verbundene Objekt abgeworfen?", 0, this(), pCaller);
}

func Boom()
{
  SetPlrView(GetOwner(Contained()),LocalN("MyToy",toRem));
  toRem->DoHit();
  this()->RemoveObject();
  return(1);
}

func Timer()
{
  if(!toRem) RemoveObject();
  return(1);
}