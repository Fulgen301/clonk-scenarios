/*-- Adjust damage of Freeze --*/

#strict

#appendto FREZ


global func FxFreezeTimer(pTarget, iEffectNumber, iEffectTime)
{
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
  var dmg=EffectVar(4, pTarget, iEffectNumber);
  var r=2;
  if(dmg) r=1;
  
  if(!Random(r)) {
   var d=RandomX(1200,dmg);
   EffectVar(4, pTarget, iEffectNumber)=BoundBy(dmg-d, 0, 0xffffff);
   // Damit der richtige Spieler den Schaden verursacht
   var pFrom = GetCursor(EffectVar(2, pTarget, iEffectNumber));
   if(pFrom)
     pFrom->DoEnergy(-d*2,pTarget, true);
   else
     DoEnergy(-d*2, pTarget, true);
  }
  return FX_OK;
}