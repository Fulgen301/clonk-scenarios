/* Kristallturm */

#strict
#include BTWA

func OnUpgrade()
{
  if(pLastSphere)
    RemoveObject(pLastSphere);
  return 0;
}

func Attack()
{
  if(GetCon()<100)
    return 0;
    
  if(!pLastSphere)
  {
    pLastSphere=CreateObject(MGSE,0,-50,GetOwner());
    pLastSphere->~Set(60,160,2,35);
  }
}

func UpgradeTo()
{
  return BTWC;
}

func UpgradeCost()
{
  return 300;
}

func IsLevel1(){return 0;}
