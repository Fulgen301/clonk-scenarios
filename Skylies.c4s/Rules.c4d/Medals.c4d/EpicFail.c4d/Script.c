/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 0;}
func MedalIndex() {return 21;}

func RelaunchPlayer(int iPlr)
{
  if(ScriptCounter() <= 500)
    Reward(this,iPlr);
  return true;
}
