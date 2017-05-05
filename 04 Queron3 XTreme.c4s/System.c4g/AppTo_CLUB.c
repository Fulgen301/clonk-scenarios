#strict 2
#appendto CLUB

//Contained-Hack-Fix

public func Activate(pClonk)
{
  [$UseClub$]
  if(!pClonk->~CanUse(GetID())) return;
  if(GetAction(pClonk) != "Walk") return;
  var aRect = Find_InRect(-30,-10,30,20);
  if(GetDir(pClonk))
    aRect = Find_InRect(0,-10,30,20);
  var pEnemy = FindObject2(Find_OCF(OCF_CrewMember), Find_Layer(GetObjectLayer()), aRect, Find_Hostile(GetOwner(pClonk)), Find_Container(Contained(pClonk)));
  if(!pEnemy) return;
  if(GetDir(pEnemy) != GetDir(pClonk)) return;
  pClonk->~DoShow(250);
  ObjectSetAction(pClonk, "Stun", pEnemy);
  return 1;
}