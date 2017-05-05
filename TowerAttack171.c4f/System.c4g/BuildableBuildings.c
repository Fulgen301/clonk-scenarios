/*-- Geb�ude --*/

#strict
#appendto WTWR
#appendto WZKP
#appendto CHPL
#appendto ALTR
#appendto CLST
#appendto RSRC

func CanBeBuild(pClonk)
{
  if(GetID()==CHPL||GetID()==ALTR)
    return pClonk->~IsKnight();
  if(GetID()==WTWR||GetID()==WZKP)
    return pClonk->~IsMagiclonk();
  if(GetID()==CLST||GetID()==RSRC)
    return true;
}

func NoAIBuild()
{
  return true;
}

func IsSpecialBuilding()
{
  return true;
}
