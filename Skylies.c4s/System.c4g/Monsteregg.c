/*-- Monstereier --*/

#strict
#appendto MEGG
#appendto FMEG

//Warum Veränderung? Wir brauchen den Owner vom Monster.
private func DoBreak()
{
  if(!ActIdle()) return false;
  if(GBackSolid()) return false;
  Sound("EggBreak");
  SetAction("Break");

  var idMon = MONS;
  if(GetID(this) == FMEG) idMon = FMNS;
  var pMonster = CreateConstruction(idMon,0,0,-1,40);

  SetOwner(GetController(this),pMonster);
  pMonster->Birth();
  return true;
}
