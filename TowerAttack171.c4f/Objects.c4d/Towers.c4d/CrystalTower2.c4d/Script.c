/* Kristallturm */

#strict
#include TWMC

func StrikeDamage(){ return RandomX(4,7);}
func Range(){ return 150;}
func LightningOffset(){ return -40;}
func LightClr(){ return RGB(127,0,255);}

func UpgradeTo()
{
  return TWM3;
}

func UpgradeCost()
{
  return 110;
}

func IsLevel1(){return 0;}
