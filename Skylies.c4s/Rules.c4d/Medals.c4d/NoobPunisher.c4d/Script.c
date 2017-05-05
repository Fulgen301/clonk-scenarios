/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 0;}
func MedalIndex() {return 30;}

local aNoobkills;

func Initialize()
{
  aNoobkills = [];
  return true;
}

func OnClonkDeath(object pClonk, int iKiller)
{
  if(GetOwner(pClonk) == NO_OWNER || iKiller == NO_OWNER) return false;
  if(GetOwner(pClonk) == iKiller) return false;
  
  if(IsPro(iKiller,GetOwner(pClonk)))
    aNoobkills[iKiller]++;
    
  if(aNoobkills[iKiller] >= 6)
    Reward(this,iKiller);
  return true;  
}
