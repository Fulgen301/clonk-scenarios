/* Magieturm */

#strict
//#include BSC1

local pLastSphere;

func Initialize()
{
  SetGraphics("");
}

func Attack()
{
  if(GetCon()<100)
    return 0;
    
  if(!pLastSphere)
    pLastSphere=CreateObject(MGSE,0,-40,GetOwner());
}

func CanBeBuild(pClonk)
{
  //if(GetID(pClonk)==MAGE)
    return true;
}

func UpgradeTo()
{
  return BTWB;
}

func UpgradeCost()
{
  return 190;
}

protected func Incineration()
{
  SetGraphics("Dmg");
}

func NoAIBuild()
{
  return Random(3)==0;
}

func IsLevel1(){return 1;}
