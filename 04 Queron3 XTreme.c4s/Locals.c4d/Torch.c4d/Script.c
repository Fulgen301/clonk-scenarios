/*-- Fackel --*/

// script v1.0 by miniwipf
#strict 2

/* MINISCRIPT */

protected func Initialize()
{
	return SetAction("Off");
}

protected func Activate(object pCaller)
{
	ControlDigDouble(pCaller);
	return this; // für Burgteile wichtig
}

protected func ControlDigDouble(object pClonk)
{
  if (GetAction() == "On") return Extinguish();
  return Enkindle();
}

// Action
protected func Effect()
{
	CreateParticle("Fire2", RandomX(-2, 2), RandomX(-5, -10), RandomX(-2, 2), RandomX(-5, -10), 5*RandomX(5, 20));
	return 1;
}

private func StructureCheck()
{
  if(!FindCastlePart(1, 1)) RemoveObject();
}

// Um die Fackel zu entzünden oder zu löschen

public func Enkindle()
{
	Sound("Fuse");
  return SetAction("On");
}

public func Extinguish()
{
	Sound("Pshshsh");
  return SetAction("Off");
}

public func CastleChange() { return StructureCheck(); }
