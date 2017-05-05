/*-- Grosser grauer Stein --*/

// script v1.0 by Miniwipf
#strict

/* MINISCRIPT */

protected func Initialize()
{
  SetAction("Remain");
  var phase = Random(GetActMapVal("Length", "Remain", GetID()));
  SetPhase(phase);
  var s = GetDefWidth();
  SetSolidMask(phase*s, 0, s, s);
  return 1;
}

protected func Damage()
{
  if (GetDamage() < 50) return;
  Split2Components();
  var s = GetDefWidth();
	for (var i=0; i < 10; i++)
  	CreateParticle("Dust", RandomX(-s/2, s/2), RandomX(-s/2, s/2), RandomX(-2, 2), RandomX(-2, 2), 5*RandomX(10, 40));
  return 1;
}
