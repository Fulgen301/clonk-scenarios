#strict 2
#appendto CRBW

//Tjo, Wallhack is gone

public func Fire()
{
  var pClonk = Contained();
  // Kein Träger?
  if(!pClonk) return 0;
  // Im Gebäude?
  if (pClonk->Contained()) { pClonk->~StopAiming(); return(0); }
  // Unvollständig?
  if (~GetOCF() & OCF_Fullcon) return 0;
  // Noch beim Nachladen
  if (GetAction() == "Reload") return 0;
  // Pfeil vom Träger holen
  var pArrow = pClonk->~GetBolt(idBolt);
  if (!pArrow) 
  {
    // andere Munition?
    ControlSpecial(Contained());
    pArrow = pClonk->~GetBolt(idBolt);
    // wohl doch nicht :-(
    if (!pArrow) 
      return 0;
  }
  // Beim Träger ggf. Bogen wieder auswählen
  ShiftContents(pClonk, 0, CRBW);
  // Austrittsgeschwindigkeit ermitteln
  var iOutX, iOutY, iOutR, iOutXDir, iOutYDir, iOutRDir;
  var iDir = GetDir(pClonk); if(!iDir) iDir = -1;
  GetCrossbowOut(this, iAngle, 0, iOutX, iOutY, iOutR, iOutXDir, iOutYDir, iOutRDir);
  iOutXDir *= iDir; iOutX *= iDir; iOutR *= iDir;
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(Contained()), pArrow);
  // Pfeil abfeuern
  Exit(pArrow, iOutX,iOutY,iOutR, 0,0,iOutRDir );
  SetXDir(iOutXDir, pArrow); SetYDir(iOutYDir, pArrow);
  pArrow->~Launch(pClonk);
  //Schützen kurzzeitig nicht treffen
  AddEffect("IntHitProtection", pArrow, 1, 5, pArrow, 0, Contained());
  // Sicht verfolgen
  if (GetPlrView(GetController(pClonk)) != 2)
    SetPlrView(GetController(pClonk), pArrow);
  // Sound
  Sound("Crossbow*");
  // Nachladen
  SetAction("Reload");
  pClonk->~LoadCrossbow();
  if(!pArrow->~IsSilent())
    pClonk->~DoShow(200);
  ActualizePhase(pClonk);
  // Munitionscheck
  if(!CheckMunitionID(idBolt))
  {
    // Leer? Dann andere Munition
    ControlSpecial(Contained());
  }
  // Fertig!
  return 1;
}

public func GetCrossbowOut(pBow, iAngle, fDeviate, &iOutX, &iOutY, &iOutR, &iOutXDir, &iOutYDir, &iOutRDir) 
{
  // Austrittsgeschwindigkeit ermitteln 
  iOutXDir = Sin(iAngle, iPower);
  iOutYDir = -Cos(iAngle, iPower);
  // Pfeildrehung 
  iOutR = iAngle; 
  if(iAngle > 0) iOutRDir = 3; else iOutRDir = -3;
  // Fertig 
  return 1;
} 