/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 0;}
func MedalIndex() {return 22;}

func MedalFulfil()
{
  for(var i=0; i < GetPlayerCount(); i++)
    if(aHardcore[GetPlayerByIndex(i)] == 2 && FindObject(HCOR))
      Reward(this,GetPlayerByIndex(i));
  return true;
}
