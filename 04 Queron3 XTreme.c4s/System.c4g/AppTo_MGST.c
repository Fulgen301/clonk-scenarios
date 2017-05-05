/* Magiestab */

// Zauberenergie lädt schneller nach

#strict 2
#appendto MGST

protected func Timer()
{
  var pCursor = GetCursor(GetOwner(pTarget));
  if(pCursor == pTarget || GetActionTarget(0, pCursor) == pTarget)
    SetVisibility(VIS_Owner);
  else SetVisibility(VIS_None);
  if (fFixedSymbol) return;
  SetPosition(20 + 40*Min(ContentsCount(0, pTarget), 1), -25);
  if (!(iTime % 7))
    if (FindObject(STES))
      DoMagicEnergy(MagicEnergyAdd(), pTarget);
  SetDTRotation(iTime++, Abs(Sin(iTime, 200)) + 800, Abs(Sin(iTime, 200)) + 800, 0, 1);
  SetDTRotation(-iTime, Abs(Sin(90-iTime, 200)) + 800, Abs(Sin(90-iTime, 200)) + 800, 0, 2);
}

public func MagicEnergyAdd() { return 1; }
