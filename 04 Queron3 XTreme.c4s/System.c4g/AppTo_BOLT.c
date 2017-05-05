#strict 2
#appendto BOLT

public func OnSideTravel()
{
  AddEffect("IntNoHit", this, 1, 1, this);
}

protected func InFlight()
{
  if (GetEffect("IntNoHit", this))
  {
    iOldX = GetX();
    iOldY = GetY();
    return RemoveEffect("IntNoHit", this);
  }
  return _inherited(...);
}

protected func FxIntHitProtectionStart(pTarget, iEffect, iTemp, pObj)
{
  if(!iTemp)
    EffectVar(0, pTarget, iEffect) = pObj;
}

protected func FindTarget()
{
  var obj, pProtect = EffectVar(0, this, GetEffect("IntHitProtection", this));
 
  var x = GetX()-iOldX;
  var y = GetY()-iOldY;

  var obj;
  var length = Abs(x/4);
  if(Abs(GetXDir()) < Abs(GetYDir())) length = Abs(y/4);

  var cX,cY;
  for(var cnt=length;cnt;cnt--)
  {
    cX=-x*cnt/length;
    cY=-y*cnt/length;
//    CreateParticle("NoGravSpark", cX, cY, 0, 0, 20, RGB(255));
    if(obj=FindObject2(Find_AtPoint(cX,cY),Find_NoContainer(),Find_Layer(GetObjectLayer()),Find_OCF(OCF_Alive, OCF_Living), Find_Exclude(pProtect)))
      return obj;
  
    // Osterei!
    var flnt;
    if(flnt = FindObject2(Find_AtPoint(cX,cY),Find_Layer(GetObjectLayer()),Find_NoContainer(), Find_Exclude(pProtect)))
      if(flnt->~ExplodeSize())
        if(ActIdle(flnt))
        { flnt->Hit(); Hit(); }
  }
 
  iOldX=GetX();
  iOldY=GetY();
 
  return 0;
}