/* Clonk*/

// Clonks k�nnen mehr Objekte aufnehmen

// script v.10 by miniwipf
#strict 2
#appendto CLNK

// Aufnahmelimit vergr�ssern
public func MaxContentsCount()
{
	if (GetID() == CLNK) return 2;
	if (GetID() == ACLK) return 2;
	//if (GetID() == MAGE) return 2;
	else return inherited();
}

//Inventarwechsel auch f�r Clonks

protected func ControlSpecial()
{
  //Nur f�r Clonk und Aqua, der Rest hat schon bzw behandelt selbst (Kombo unso)
  if (GetID() == CLNK || GetID() == ACLK)
    return ShiftContents(0, 0, 0, true);
  return _inherited(...);
}