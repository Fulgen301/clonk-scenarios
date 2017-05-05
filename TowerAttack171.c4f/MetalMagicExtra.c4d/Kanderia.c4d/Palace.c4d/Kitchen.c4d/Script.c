/*-- Burg-K�che --*/

#strict 2

#include PPW2 // Burgteilfunktion
#include DOOR // Tuersteuerung

/* Initialisierung */

protected func Initialize()
{
  // Objekte im Umkreis ihre �berpr�fungen durchf�hren lassen
  _inherited();
  // Topf und Feuerstelle erzeugen
  CreateObject(CLD4, -19, 35,GetOwner() ); //->SetKitchen(this );
  CreateObject(STV2, -17, 37,GetOwner() ); //->SetKitchen(this );
}

/* Inhalt von Loren �bernehmen (KEIN TimerCall) */

protected func Collection2(pObj)
{
  if(pObj->~IsLorry() )
    GrabContents(pObj);
}

/* T�rsteuerung */

private func SoundOpenDoor()
{
  Sound("GateOpen");
}

private func SoundCloseDoor()
{
  Sound("GateClose");
}

/* Ausrichtung von Burgbauteilen */

public func CastlePartWidth() { return (80); } 
public func CastlePartHeight() { return (74); }
public func CastlePartTop() { return (-13); }
public func CastlePartBasement() { return BSC3; }

/* Status */

public func IsKitchen() { return 1; }

/* Forschung */

public func GetResearchBase() { return PPW2; }

/* T�rsteuerung */

private func SoundOpenDoor()
{
  Sound("Curtain");
}
  
private func SoundCloseDoor()
{
  Sound("Curtain");
}

