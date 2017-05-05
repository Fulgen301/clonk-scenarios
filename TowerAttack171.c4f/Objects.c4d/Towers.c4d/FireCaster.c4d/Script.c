/*-- Feuerfalle --*/

#strict
#include WDTP

func Fire()
{
  // Zauberobjekt erschaffen und aktivieren
  CreateObject(FBRT,0,0,-1)->FBRT::Activate(this(),55,0,12,RandomX(-10,10)-90,0,0,false);
}

func FireDelay(){ return 350;/*10s*/}

func IsLevel1(){return 0;}

func UpgradeTo()
{
  return false;
}

func UpgradeCost()
{
  return 0;
}
