/*-- Explosiver roter Stein --*/

// script v1.0 by miniwipf
#strict 2
#include BRCK

protected func Damage()
{
  if (GetDamage() < 30) return;
  Split2Components();
  var s = GetDefWidth();
	for (var i=0; i < 10; i++)
  	CreateParticle("Dust", RandomX(-s/2, s/2), RandomX(-s/2, s/2), RandomX(-2, 2), RandomX(-2, 2), 5*RandomX(10, 40));
  // Bamm!
  CreateObject(SFLN,, 2) -> Hit();
  return 1;
}
