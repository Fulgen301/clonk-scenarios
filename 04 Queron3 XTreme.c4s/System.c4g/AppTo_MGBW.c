#strict 2
#appendto MGBW

public func ActivateAngle(object pCaller, int iAngle, fOneShot)
  {
  // Austrittsgeschwindigkeit ermitteln
  var iOutX, iOutY, iOutR, iOutXDir, iOutYDir, iOutRDir;
 
  var pArrow; 
  
  // Damit der gleich erstellte Pfeil nicht versucht sich zu packen
  AddEffect("IntNoPacking", pCaller, 1);
  
  // Damit nicht trotzdem ein Pfeil zurueckerstattet wird
  if(idArrow)
  if(GetEffect("KeepArrow",this))
   EffectCall(this(),GetEffect("KeepArrow",this),"Remove");
  
  // Wenn keine Pfeil ID da ist, dann machen wir einen Magiepfeil
  if(!idArrow)
  {
      // Der Pfeil
      pArrow = CreateContents(ARRW, pCaller);      
      SetClrModulation(RGBa(128,128,255,0), pArrow);
      SetObjectBlitMode(1, pArrow); // Durchscheinend
      AddEffect("IntArrowVanish",pArrow,1,3,0,GetID()); // Verschwindet wieder
      SetMass(1, pArrow); // Bischen leichter
  }
  else pArrow = CreateContents(idArrow, pCaller); // Sonst einfach passenden Pfeil erstellen
  
  // Packeffekt wieder entfernen
  RemoveEffect("IntNoPacking", pCaller);
  
  // Zufallsabweichung
  var iDeviation = 5;
  iAngle += Random(iDeviation * 2 + 1) - iDeviation;
  // Austrittsgeschwindigkeit ermitteln 
  iOutXDir = Sin(iAngle, 65);
  iOutYDir = -Cos(iAngle, 65);
  // Austrittsposition... 
  iOutX = Sin(iAngle, 25 * GetCon() / 100);
  iOutY = -Cos(iAngle, 25 * GetCon() / 100); 
  // Pfeildrehung 
  iOutR = iAngle; 
  if(iAngle > 0) iOutRDir = 3; else iOutRDir = -3;
  
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(pCaller), pArrow);
  // Pfeil abfeuern
  Exit(pArrow,AbsX(GetX(pCaller) + iOutX),AbsY(GetY(pCaller) + iOutY),iOutR, 0,0,iOutRDir );
  SetXDir(iOutXDir, pArrow);
  SetYDir(iOutYDir, pArrow);
  pArrow->~Launch();
  // Sound
  Sound("Bow");
  // Nachladen (Nur wenn von einem CrewMember gezielt wurde, also nicht bei Artefakt)
  if(!fOneShot && (GetOCF(pCaller) & OCF_CrewMember))
  {
    AddEffect("NextShot", pCaller, 1, 16, 0, GetID());
    AddEffect("IntReload",pCaller,1,21,0,GetID(), iAngle);
  }
  // Objekt löschen
  RemoveObject();
  return 1;
  }

protected func FxNextShotTimer(object pTarget)
{
  if (pTarget)
    pTarget->~DoMagic(MGBW);
  return -1;
}