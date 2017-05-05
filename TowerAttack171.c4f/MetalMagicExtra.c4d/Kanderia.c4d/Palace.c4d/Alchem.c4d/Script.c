/*-- Burg-Alchemieraum --*/

#strict 2

#include DOOR // T�rsteuerung
#include CHEM // Chemiefabrik
#include PPW2 // Burgteilfunktion

/* Burgbauteil */

public func CastlePartWidth() { return (80); }
public func CastlePartHeight() { return (74); }
public func CastlePartTop() { return (-13); }
public func CastlePartBasement() { return BSC3; }

protected func Initialize()
{
  // Bei Fertigstellung an anderen Teilen ausrichten
  CastlePartAdjust();
  // In den Hintergrund versetzen
  SetCategory(C4D_StaticBack );
  // Objekte im Umkreis ihre �berpr�fungen durchf�hren lassen
  CastlePartInitialize();
}

/* Forschung */

public func GetResearchBase() { return PPW2; }

/* Herstellungsprozess */

private func BuildProcess()
{
  if(!Random(8) ) return Sound("Fire");
  if(!Random(6) ) return Sound("Build*");
  if(!Random(2) ) Sound("Alchem*");
  if(!Random(8) ) Smoke(16, 19, 4 + Random(5) );
  if(!Random(7) ) Smoke(26, 19, 4 + Random(5) );
}

/* T�rsteuerung */

private func SoundOpenDoor()
{
  Sound("Curtain");
}
  
private func SoundCloseDoor()
{
  Sound("Curtain");
}
