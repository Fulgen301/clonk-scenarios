/*-- Höhle --*/

// script v1.0 by miniwipf
#strict 2

local _aTargets;

protected func Initialize()
{
	_aTargets = [];
	// Eingang immer offen
	SetEntrance(1);
	return 1;
}

public func ContainedUp(object pClonk)
{
  [$TxtWalkTrough$|Image=CAVE]
  // Zu einem zufälligen Ausgang versetzen
  if (!GetLength(_aTargets)) return 1;
  var target = _aTargets[Random(GetLength(_aTargets))];
  Enter(target, pClonk);
  // Raus mit dir du Angsthase
  target -> Exit(pClonk,, GetDefBottom()-GetY());
  return 1;
}

public func AddWayOut(object pObj)
{
	// Wenn nicht schon gesetzt
	if (FindArrayEntry(pObj, _aTargets) >= 0) return;
	AddArrayEntry(pObj, _aTargets, -1);
	return 1;
}

public func RemoveWayOut(object pObj)
{
	var pos = FindArrayEntry(pObj, _aTargets);
	if (pos < 0) return;
	RemoveArrayEntry(pos, _aTargets);
	return 1;
}

public func SetAllCavesAsWayOut()
{
	for (var cave in FindObjects(Find_ID(CAVE), Find_Exclude(this)))
		AddWayOut(cave);
	return 1;
}
