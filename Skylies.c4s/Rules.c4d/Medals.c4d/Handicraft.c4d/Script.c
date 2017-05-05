/*-- Medaille --*/

#strict 2

/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 1;}
func MedalIndex() {return 5;}

local aAnvilWorks;

func Initialize()
{
  aAnvilWorks = [];
  return true;
}

func OnAnvilWork(int iPlr)
{
  if(iPlr != NO_OWNER)
  {
    aAnvilWorks[iPlr]++;
    if(aAnvilWorks[iPlr] >= 20)
      Reward(this,iPlr);
  }
  return true;
}