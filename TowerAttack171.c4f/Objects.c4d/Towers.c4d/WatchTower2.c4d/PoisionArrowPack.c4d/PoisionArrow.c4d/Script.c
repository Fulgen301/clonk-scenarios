/*-- Giftpfeil --*/

#strict

#include ARRW

public func HitTarget(pObject)
{
  if(!_inherited(pObject))return(0);
  // Gifteffekt anhängen, bzw verlängern
  if(!GetEffect("BulletPoision",pObject))
    AddEffect("BulletPoision",pObject,20,3,0,PBLT,GetOwner());
  else
    EffectVar(2,pObject,GetEffect("BulletPoision",pObject))+=300;
  return(1);
}

/* Pfeileigenschaften */
public func PackTo() { return(PARP); }
public func ArrowStrength() { return(2+Random(2)); }
public func ArrowTumbleRandom() { return(3); }
