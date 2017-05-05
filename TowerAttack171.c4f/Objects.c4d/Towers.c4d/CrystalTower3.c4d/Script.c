/* Kristallturm */

#strict
#include TWMC

func StrikeDamage(){ return RandomX(5,10);}
func Range(){ return 200;}
func LightningOffset(){ return -45;}
func LightClr(){ return RGB(255,0,0);}

func UpgradeTo()
{
  return false;
}

func UpgradeCost()
{
  return 0;
}

func IsLevel1(){return 0;}
