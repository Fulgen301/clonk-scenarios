/*-- Neues Script --*/

#strict
#appendto CLNK

public func Never()
{
  return false;
}

public func ContextConstruction(pCaller)
{
  [ERROR|Condition=Never]
  Message("FUCK YOU",this());
  return(1);
}
