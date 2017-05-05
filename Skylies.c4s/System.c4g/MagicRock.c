/*-- Neues Script --*/

#strict 2
#appendto MRCK

public func Activate(object pController)
{
  [$DescGetOut$]
  
  if(!Contents(0,this))
  {
    Sound("Magic1",false,this);
    Exit(this);
    Enter(this, pController);
    if(GetProcedure(pController) == "ATTACH") pController->SetAction("Walk");
    return true;
  }
  
  return _inherited(pController);
}
