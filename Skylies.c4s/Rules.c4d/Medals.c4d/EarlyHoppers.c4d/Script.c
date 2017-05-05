/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 1;}
func MedalIndex() {return 3;}

func Buttercake(object pButterfly, int iKiller)
{
  if(iKiller != NO_OWNER)
    Reward(this,iKiller);
  return true;
}
