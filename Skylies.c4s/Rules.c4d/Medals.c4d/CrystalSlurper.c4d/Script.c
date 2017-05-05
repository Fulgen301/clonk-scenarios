/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 0;}
func MedalIndex() {return 16;}

local aCrystalCount;

func Initialize()
{
  aCrystalCount = [];
  return true;
}

func OnCrystalConvert(object pClonk)
{
  var player= GetOwner(pClonk);
  if(player != NO_OWNER)
  {
    aCrystalCount[player]++;

    if(aCrystalCount[player] >= 15)
      Reward(this,player);
  }
  return true;
}
