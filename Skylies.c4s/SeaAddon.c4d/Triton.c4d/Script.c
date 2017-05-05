/*-- Tritonmuschel --*/

#strict

protected func Initialize()
{
  SetEntrance(1);
}

public func Damage() {
if(GetDamage() > 65) {
 CastObjects(ROCK,5,50);
 RemoveObject (this(),true);
 }
}