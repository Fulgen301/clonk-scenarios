/*-- Windfalle --*/

#strict
#include ICTP

func Fire()
{
  // Zauberobjekt erschaffen und aktivieren
  var pSpell = CreateObject(ABLA,0,0,GetOwner());
  if (!pSpell) return; // Zauber fehlgeschlagen
  pSpell->~Activate(this);
  Message("",this);
  return true;
}

func FireDelay(){ return 175;/*5s*/}

func DoSpellAim(pSpell)
{
  pSpell->~ActivateAngle(this, RandomX(-10,10));
  Message("",this);
  return 1;
}

func IsLevel1(){return 1;}

func UpgradeTo()
{
  return ICTP;
}

func UpgradeCost()
{
  return 55;
}
