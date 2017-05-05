/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 0;}
func MedalIndex() {return 24;}

local aFishKills;

func Initialize()
{
  aFishKills = [];
  return true;
}

func OnFishDeath(object pFish,int iKiller)
{
  if(iKiller != NO_OWNER)
  {
    aFishKills[iKiller]++;
    
    if(aFishKills[iKiller] >= 6)
      Reward(this,iKiller);
  }
  return true;
}
