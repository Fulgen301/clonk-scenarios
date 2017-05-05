#strict 2
#appendto TKNF

public func OnSideTravel()
{
  AddEffect("IntNoHit", this, 1, 1, this);
}

protected func InFlight()
{
  if (GetEffect("IntNoHit", this))
  {
    iOldX = GetX();
    iOldY = GetY();
    return RemoveEffect("IntNoHit", this);
  }
  return _inherited(...);
}