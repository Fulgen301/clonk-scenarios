/*-- Fahrstuhl --*/

#strict
#appendto ELEC

func Initialize()
{
  AutoMode=true;
  AddEffect("NoBurning", this, 200, 0,this);
  _inherited();
}

protected func UpdateTransferZone()
{
  return(1);
}

public func IsInPermanentMode()
{
  return(false);
}
  
public func IsNotInPermanentMode()
{
  return(false);
}
