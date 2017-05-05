/*-- Heimat ist überall! --*/

#strict 2
#appendto EC69

private func AI_Home()
{  
/*  // X-Richtung reicht fürs Home
  if (Abs(GetX() - ai_iHomeX) > 5) if (!ai_pHome)
    {
    // Magier kann sich auch warpen
    if (AI_DoMagic(EH69)) { AI_SetCommand("None"); return(true); }
    AI_SetCommand("MoveTo", 0, ai_iHomeX, ai_iHomeY);
    return(AI_ExecMovement());
    }
  // Container
  if (Contained() != ai_pHome)
    {
    if (ai_pHome)
      {
      if (!(GetOCF(ai_pHome) & OCF_Entrance)) { ai_pHome=0; return(true);} 
      if (!WildcardMatch(GetAction(), "Ride*") || GetActionTarget() != ai_pHome)
        {
        AI_SetCommand("Enter", ai_pHome);
        return(AI_ExecMovement());
        }
      }
    else
      {
      AI_SetCommand("Exit");
      return(true);
      }
    }
  // @ Home
  if (GetProcedure() eq "WALK") SetDir(ai_iHomeDir);
  // Wenig Energie: Heilung
  if (GetEnergy() < 15) if (AI_Heal()) return(true);*/
  // KI-Clonks regenerieren auch so (laaangsam)
  if (!Random(50)) DoEnergy(1);
  // Erstmal alles stoppen
  //SetCommand(0, "None"); SetComDir(COMD_Stop);
  // Clonkspezifische Aktion
  if (OnAIIdle()) return(true);
  // Tjo. Nix zu tun.
  return(true);
}
