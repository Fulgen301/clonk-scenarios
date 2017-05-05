/* Clonk*/

// Clonks können mehr Objekte aufnehmen

// script v.10 by miniwipf
#strict 2
#appendto CLNK

// Aufnahmelimit vergrössern
public func MaxContentsCount()
{
	if (GetID() == CLNK) return 2;
	if (GetID() == ACLK) return 2;
	//if (GetID() == MAGE) return 2;
	else return inherited();
}

//Inventarwechsel auch für Clonks

protected func ControlSpecial()
{
  //Nur für Clonk und Aqua, der Rest hat schon bzw behandelt selbst (Kombo unso)
  if (GetID() == CLNK || GetID() == ACLK)
    return ShiftContents(0, 0, 0, true);
  return _inherited(...);
}