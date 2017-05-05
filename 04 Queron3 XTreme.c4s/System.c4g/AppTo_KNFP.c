#strict 2
#appendto KNFP

//Clonks in Containern erstechen ist nicht

public func Activate(object pClonk)
{
  [$Stab$]
  if(!pClonk->~CanUse(GetID())) return;
  if(GetAction(pClonk) != "Walk") return;
  var aRect = Find_InRect(-30,-10,30,20);
  if(GetDir(pClonk))
    aRect = Find_InRect(0,-10,30,20);
  var pEnemy = FindObject2(Find_OCF(OCF_CrewMember), Find_Layer(GetObjectLayer()), aRect, Find_Hostile(GetOwner(pClonk)), Find_Container(Contained(pClonk)));
  if(!pEnemy)
    return;
  if(GetDir(pEnemy) != GetDir(pClonk)) return;
  pClonk->~DoShow(250);
  ObjectSetAction(pClonk, "Assassasinate", pEnemy);
  return 1;
}

public func ControlThrow(object pObj)
{
  if (!pObj->~CanUse(GetID()) || GetProcedure(pObj) == "PUSH")
    return;
  if (GetEffect("ThrowKnifeCooldown", pObj))
    return true;
  if (GetAction(pObj) != "Walk" && GetAction(pObj) != "Ride" && GetAction(pObj) != "Jump")
    return true;
  AddEffect("ThrowKnifeCooldown", pObj, 1, 35);
  Sound("ThrowKnife");
  pObj->~DoShow(100);
  var knife = GetItem();
  knife->Departure(pObj);
  if (GetAction(pObj) == "Walk")
    ObjectSetAction(pObj, "Throw");
  if (GetAction(pObj) == "Ride")
    ObjectSetAction(pObj, "RideThrow");
  return true;
}