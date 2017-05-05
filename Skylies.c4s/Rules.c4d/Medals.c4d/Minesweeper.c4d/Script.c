/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 0;}
func MedalIndex() {return 12;}

local aCount;

func Initialize()
{
  aCount = [];
  return true;
}

func ArtefactActivation(object pCaller)
{
  var iPlr = GetOwner(pCaller);
  aCount[iPlr]++;
  
  if(aCount[iPlr] >= 20)
    Reward(this,iPlr);
  
  return true;
}
