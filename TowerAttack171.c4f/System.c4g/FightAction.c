/*-- Mehr M glichkeiten beim Kampf --*/

#strict
#appendto CLNK

protected func ControlThrow()
{
  //if(Contents())
    if(WildcardMatch(GetAction(),"*Fight*"))
      if(!WildcardMatch(GetAction(),"*Throw*"))
      {
        SetAction("Walk",0,0,true);
        if(_inherited())
          return 1;
        return 0;
      }
}

protected func ControlDownDouble()
{
  if(_inherited())
    return 1;
  if(WildcardMatch(GetAction(),"*Fight*"))
    SetAction("Walk",0,0,true);
  return 0;
}

protected func ControlUpDouble()
{
  if(_inherited())
    return 1;
  if(WildcardMatch(GetAction(),"*Fight*"))
  {
    SetAction("Walk",0,0,true);
    Jump();
  }
  return 0;
}

public func ReadyToMagic(a,b,c,d)
{
  if (GetProcedure() S= "FIGHT") return(true);
  return(_inherited(a,b,c,d));
}
