#strict 2

//Killverfolgung und Physicals

global func FxFreezeStart(pTarget, iEffectNumber, iTemp, iFromController)
{
  if(iTemp) return;
  RemoveEffect("Hide", pTarget);
  // Toller Sound
  Sound("Crystal2", 0, pTarget);
  // Zeit einstellen
  EffectVar(0, pTarget, iEffectNumber) += 35;
  // ID speichern
  var id = GetID(pTarget);
  if(GetDefHeight(id) > GetDefWidth(id)) EffectVar(1, pTarget, iEffectNumber) = GetDefHeight(id);
  else EffectVar(1, pTarget, iEffectNumber) = GetDefWidth(id);
  // Verursacher speichern
  EffectVar(2, pTarget, iEffectNumber) = iFromController;
  return 1;  
}

global func FxFreezeTimer(pTarget, iEffectNumber, iEffectTime)
{
  if (!EffectVar(10, pTarget, iEffectNumber))
  {
  EffectVar(10, pTarget, iEffectNumber) = true;
  EffectVar(3, pTarget, iEffectNumber) = GetPhysical("Walk", PHYS_Current, pTarget);
  EffectVar(4, pTarget, iEffectNumber) = GetPhysical("Dig", PHYS_Current, pTarget);
  EffectVar(5, pTarget, iEffectNumber) = GetPhysical("Jump", PHYS_Current, pTarget);
  EffectVar(6, pTarget, iEffectNumber) = GetPhysical("Swim", PHYS_Current, pTarget);
  EffectVar(7, pTarget, iEffectNumber) = GetPhysical("Scale", PHYS_Current, pTarget);
  EffectVar(8, pTarget, iEffectNumber) = GetPhysical("Hangle", PHYS_Current, pTarget);
  EffectVar(9, pTarget, iEffectNumber) = GetPhysical("Float", PHYS_Current, pTarget);
  // Physicals herunter setzen
  SetPhysical("Dig"   , GetPhysical("Dig"   , 0, pTarget)*3/4, PHYS_Temporary, pTarget);
  SetPhysical("Walk"  , GetPhysical("Walk"  , 0, pTarget)*3/4, PHYS_Temporary, pTarget);
  SetPhysical("Jump"  , GetPhysical("Jump"  , 0, pTarget)*3/4, PHYS_Temporary, pTarget);
  SetPhysical("Swim"  , GetPhysical("Swim"  , 0, pTarget)*3/4, PHYS_Temporary, pTarget);
  SetPhysical("Scale" , GetPhysical("Scale" , 0, pTarget)*3/4, PHYS_Temporary, pTarget);
  SetPhysical("Hangle", GetPhysical("Hangle", 0, pTarget)*3/4, PHYS_Temporary, pTarget);
  SetPhysical("Float" , GetPhysical("Float" , 0, pTarget)*3/4, PHYS_Temporary, pTarget);
  }
  // In Lava schwimmend? Dann schnell auftauen (nur für Monster und andere nicht brennbare Lebewesen wichtig)
  if(GetMaterialVal("Incindiary", "Material", pTarget->GetMaterial()))
    return -1;
  // Partikeleffekte für den betroffenen
  var id = GetID(pTarget);
  CreateParticle("NoGravSpark",GetX(pTarget)+RandomX(-GetDefWidth(id)/2, GetDefWidth(id)/2),GetY(pTarget)+RandomX(-GetDefHeight(id)/2, GetDefHeight(id)/2),0,RandomX(-2, -4),RandomX(18,28),RGB(10,120,210), pTarget);
  CreateParticle("Freeze",GetX(pTarget),GetY(pTarget),0,0,EffectVar(1, pTarget, iEffectNumber)*5+20,RGB(0,40,80),pTarget);
  // Runterzählen
  EffectVar(0, pTarget, iEffectNumber)-=1;
  if(EffectVar(0, pTarget, iEffectNumber)<=0) return FX_Execute_Kill;
  // Ein bischen tut Einfrieren auch weh
  if(!Random(10))
   DoEnergy(-1, pTarget, false, 0, EffectVar(2, pTarget, iEffectNumber) + 1);
  return FX_OK;
}

global func FxFreezeStop(pTarget, iEffectNumber, iReason, fTemp)
{
  if(fTemp) return;
  // Wenn der Effekt endgültig entfernt wird: Sound!
  Sound("DePressurize", 0, pTarget);
  if (!EffectVar(10, pTarget, iEffectNumber))
    return;
  // Alte Physicals wiederherstellen
  SetPhysical("Walk", EffectVar(3, pTarget, iEffectNumber), PHYS_Current, pTarget);
  SetPhysical("Dig", EffectVar(4, pTarget, iEffectNumber), PHYS_Current, pTarget);
  SetPhysical("Jump", EffectVar(5, pTarget, iEffectNumber), PHYS_Current, pTarget);
  SetPhysical("Swim", EffectVar(6, pTarget, iEffectNumber), PHYS_Current, pTarget);
  SetPhysical("Scale", EffectVar(7, pTarget, iEffectNumber), PHYS_Current, pTarget);
  SetPhysical("Hangle", EffectVar(8, pTarget, iEffectNumber), PHYS_Current, pTarget);
  SetPhysical("Float", EffectVar(9, pTarget, iEffectNumber), PHYS_Current, pTarget);
}