/*-- Fakellicht --*/

#strict

#appendto TORC

protected func Initialize()
{
  SetAction("Burning");
  CreateLight(200, RGBa(255,200,155,65), this, true, -11);
}
