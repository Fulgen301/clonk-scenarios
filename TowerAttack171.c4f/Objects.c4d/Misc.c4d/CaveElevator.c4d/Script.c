/*-- Fahrstuhl --*/

#strict

#include ELEV

private func BasementID() { return(0); }
private func BasementWidth() { return(0); }

public func RemoveCase()
{
  // Komplett, aber kein Fahrstuhlkorb: reduzieren für Wiederaufbau/Reparatur
  if (GetCon() == 100) { SetAction("Lift"); DoCon(-1); }
  return(1);
}
