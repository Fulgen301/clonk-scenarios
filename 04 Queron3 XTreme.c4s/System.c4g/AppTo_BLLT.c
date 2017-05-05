#strict 2
#appendto BLLT

public func OnSideTravel()
{
  AddEffect("IntNoHit", this, 1, 1, this);
}

protected func InFlight()
{
  if (GetEffect("IntNoHit", this))
  {
    oldX = GetX();
    oldY = GetY();
    return RemoveEffect("IntNoHit", this);
  }
  return _inherited(...);
}