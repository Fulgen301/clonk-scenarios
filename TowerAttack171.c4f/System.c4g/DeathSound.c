#appendto CLNK

protected func Death(int iKilledBy)
{
  // Info-Broadcasts für sterbende Clonks
  GameCallEx("OnClonkDeath", this(), iKilledBy);
  
  // Der Broadcast könnte seltsame Dinge gemacht haben: Clonk ist noch tot?
  if (GetAlive()) return();
  
  // den Beutel fallenlassen
  if(GetAlchemBag()) GetAlchemBag()->~Loose();

  Sound("Die*.ogg");
  DeathAnnounce();
  // Letztes Mannschaftsmitglied tot: Script benachrichtigen
  if (!GetCrew(GetOwner()))
    GameCallEx("RelaunchPlayer",GetOwner());
  return(1);
} 
