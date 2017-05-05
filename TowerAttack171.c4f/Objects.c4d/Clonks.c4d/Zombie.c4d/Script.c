/*-- Der Zombie --*/

#strict

#include CLNK

public func MaxContentsCount() { return(0); }

protected func Death(int iKilledBy)
{
  // Info-Broadcasts für sterbende Clonks
  GameCallEx("OnClonkDeath", this, iKilledBy);
  
  // Der Broadcast könnte seltsame Dinge gemacht haben: Clonk ist noch tot?
  if (GetAlive()) return();
  
  // den Beutel fallenlassen
  if(GetAlchemBag()) GetAlchemBag()->~Loose();

  // Eigener Sound :)
  Sound("Rip");
  // Und eigene Deathmessage
  Message("Noch ein toter Zombie",this);
  
  // Letztes Mannschaftsmitglied tot: Script benachrichtigen
  if (!GetCrew(GetOwner()))
    GameCallEx("RelaunchPlayer",GetOwner());
  return(1);
}
