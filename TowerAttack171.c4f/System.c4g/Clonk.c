/*-- Bauen mit Maus --*/

#strict 2
#appendto CLNK

protected func ControlCommand(szCommand, pTarget, iTx, iTy, pTarget2, Data) 
{ 
  // Kommando Construct in Bauen mit Geld umwandeln. 
  if (szCommand == "Construct") 
  { 
    // nichts tuen
    return 1; 
  }
  // Sonst nicht abfangen 
  return _inherited(szCommand, pTarget, iTx, iTy, pTarget2, Data) ; 
} 
