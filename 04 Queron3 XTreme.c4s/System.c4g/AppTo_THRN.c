#strict 2
#appendto THRN

//So ein Thron lässt sich kaputten.

protected func Initialize()
{
  Update();
}

private func GetOccupant()
{
  return FindObject2(Find_Container(this), Find_OCF(OCF_CrewMember));
}

private func Update()
{
  var obj = GetOccupant();
  if (obj)
  {
    if (GetAction() != "Occupied")
      SetAction("Occupied");
  }
  else
    if (GetAction() != "Empty")
      SetAction("Empty");
}

protected func ActivateEntrance(object pObj)
{
  if (Contained(pObj) == this)
    return OnExit(pObj);
  else
    if (!Contained(pObj))
      if (GetOCF(pObj) & OCF_CrewMember)
        return OnEntrance(pObj);
}

private func OnEntrance(object pObj)
{
  if (GetOccupant())
  {
    OnExit(pObj);
    FinishCommand(pObj);
    return;
  }
  Enter(this, pObj);
  Sound("ThroneEnter");
  SetOwner(GetOwner(pObj));
  SetColorDw(GetColorDw(pObj));
  Update();
}

private func OnExit(object pObj)
{
  if (!pObj)
    return;
  Exit(pObj);
  SetPosition(GetX(), GetY() + GetDefOffset(GetID(pObj), 1) - GetDefOffset(GetID(), 1), pObj);
  SetDir(GetDir(), pObj);
  Update();
  return true;
}

/* Ausrichtung */
  
protected func ControlRight()
{
  Sound("Lever1");
  SetDir(DIR_Right);
  return true;
}

protected func ControlLeft()
{
  Sound("Lever1");
  SetDir(DIR_Left);
  return true;
}

/* Schaden */

protected func Damage(int iChange, int iPlr)
{
  SetController(iPlr);
  if (GetDamage() < MaxDamage())
    return;
  while (Contents())
    Exit(Contents(), 0, 0, Random(360), RandomX(-3, 3), RandomX(-3, 3), RandomX(-3, 3));
  Split2Components();
}

private func MaxDamage()
{
  return 130;
}