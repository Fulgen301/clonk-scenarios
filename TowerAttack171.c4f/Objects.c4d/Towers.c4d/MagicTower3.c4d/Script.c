/* Kristallturm */

#strict
#include BTWA

func Attack()
{
  if(GetCon()<100)
    return 0;
    
  if(!GetLength(pLastSphere))
    pLastSphere=[];
  if(!pLastSphere[0])
  {
    pLastSphere[0]=CreateObject(MGSE,0,-50,GetOwner());
    pLastSphere[0]->~Set(200,250,3,50);
  }
  if(!pLastSphere[1])
  {
    pLastSphere[1]=CreateObject(MGSE,0,-75,GetOwner());
    pLastSphere[1]->~Set(200,250,3,50);
  }
}

func OnUpgrade()
{
  if(pLastSphere)
    if(!GetLength(pLastSphere))
    {
      RemoveObject(pLastSphere);
      pLastSphere=[];
    }
  return 0;
}

func UpgradeTo()
{
  return 0;
}

func UpgradeCost()
{
  return 0;
}

func NeedToBeResearched()
{
  return true;
}

func IsLevel1(){return 0;}
