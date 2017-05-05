
#strict
#appendto SF5B

local Relaunchs;
local Kills;

func ContextAntiStuck()
{
[Anti Stuck|Image=STUC]
FindObject(STUC)->Activate(GetOwner());
}


//Damit man nicht zu viele Clonks im Spieler hat

protected func Death(int iKilledBy)
{
  // Info-Broadcasts für sterbende Clonks
  GameCallEx("OnClonkDeath", this(), iKilledBy);
  
  // Der Broadcast könnte seltsame Dinge gemacht haben: Clonk ist noch tot?
  if (GetAlive()) return();
  
  // den Beutel fallenlassen
  if(GetAlchemBag()) GetAlchemBag()->~Loose();

  Sound("Die");
  DeathAnnounce();
  // Letztes Mannschaftsmitglied tot: Script benachrichtigen
  
   if (!GetCrew(GetOwner()))
   GameCall("RelaunchPlayer",GetOwner(),this(),Relaunchs, iKilledBy, Kills);
  return(1);
}
