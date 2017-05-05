/*-- Turm --*/

#strict
#include BTW1

//func StrikeDamage(){ return RandomX(3,5);}
func MinRange(){ return 100;}
func Range(){ return 500;}
func ArrowID(){ return PARW;}
func ArrowPower(){ return 110;}
func ArrowOutYOff(){ return -46;}

func UpgradeTo()
{
  return BTW3;
}

func UpgradeCost()
{
  return 550;
}

func IsLevel1(){return 0;}
