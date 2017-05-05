#strict 2
#appendto PBLT

//Killverfolgung und blubb

private func HitTarget(pObject)
{
  Sound("BulletHit*");
  
  var iOwner = GetOwner(this);
  // Gifteffekt anh�ngen
  if (!GetEffect("BulletPoision", pObject))
    AddEffect("BulletPoision", pObject, 20, 3, 0, GetID(), iOwner);
  else
    EffectVar(2, pObject, GetEffect("BulletPoision", pObject)) += 60;

  // Schaden machen und schleudern
  DoEnergy(-BulletStrength(), pObject, false, 0, iOwner + 1);
  if(Random(4))
    Fling(pObject, GetXDir()/80, GetYDir()/80-2);
  
  // Fertig
  RemoveObject();
}

protected func FxBulletPoisionStart(pTarget,iEffectNumber,temp,val1)
{
  // Bei tempor�ren Aufrufen nichts machen
  if(temp) return;
  // Zeit setzen
  EffectVar(0,pTarget,iEffectNumber)=val1;
  EffectVar(2,pTarget,iEffectNumber)=60;
  // Giftpartikel
  CreateParticle("PoisionSpark",GetX(pTarget),GetY(pTarget)-15,0,-1,70,RGB(255,255,255),pTarget);
  return 1;
}

protected func FxBulletPoisionTimer(pTarget,iEffectNumber,iEffectTime)
{
  // Im Wasser auswaschbar
  if(InLiquid(pTarget))return -1;
 
  // Ab und zu den Partikeleffekt erneuern
  if(iEffectTime%(3*(39/3))==0)
    CreateParticle("PoisionSpark",GetX(pTarget),GetY(pTarget)-15,0,0,70,RGB(255,255,255),pTarget);

  // Mit der Zeit verschwinden
  if(iEffectTime-EffectVar(2,pTarget,iEffectNumber)>200-Random(50))return -1;
 
  // In bestimmten Zeitr�umen Schaden machen
  if(iEffectTime%(3*6)==0)
  {
    DoEnergy(-1, pTarget, false, 0, EffectVar(0, pTarget, iEffectNumber) + 1);
  }
 
  return 1;
}