/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 1;}
func MedalIndex() {return 2;}

local aMagics;

func Initialize()
{
  aMagics = [];
  return true;
}

func OnRevaluation(object pClonk)
{
  var iPlr = GetOwner(pClonk);
  if(iPlr == NO_OWNER) return false;
  aMagics[iPlr]++;
  
  if(aMagics[iPlr] >= 3)
    Reward(this,iPlr);
  return true;
}
