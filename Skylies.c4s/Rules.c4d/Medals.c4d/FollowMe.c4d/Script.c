/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 0;}
func MedalIndex() {return 6;}

func RelaunchPlayer(int iPlr)
{
  if(GetEffectCount("Eliminated",this))
    Reward(this,iPlr);
  AddEffect("Eliminated",this,100,38*5);
  return true;
}
