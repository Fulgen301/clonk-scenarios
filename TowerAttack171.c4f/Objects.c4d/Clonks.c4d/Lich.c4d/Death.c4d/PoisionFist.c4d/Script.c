/* Giftfaust */

#strict

/* Aufruf */

public func Activate(object caster, object real_caster)
{
  if(real_caster) caster = real_caster;
  
  if(GetEffect("PoisionFistPSpell",caster))
    EffectCall(caster,GetEffect("PoisionFistPSpell",caster),"IncTime");
  else
    AddEffect("PoisionFistPSpell",caster,20,2,0,GetID());
  
  RemoveObject();
  return(true);
}

protected func FxPoisionFistPSpellStart(pTarget, iEffectNumber, fTmp)
{
  if(fTmp) return();
  EffectVar(0,pTarget,iEffectNumber)=(30*60*3)/2;
  PlayerMessage(GetOwner(pTarget), "$Activate$", pTarget);
  return(1);
}

protected func FxPoisionFistPSpellTimer(pTarget,iEffectNumber,iEffectTime)
{
  if(iEffectTime > EffectVar(0,pTarget,iEffectNumber)) return(-1);
 
  // Schlägt der Clonk gerade zu?
  if(GetAction(pTarget) eq "Punch")
  {
   // Das Ende vom Schlag abwarten
    if(GetPhase(pTarget)>=7)
    {
      var pObject=GetActionTarget(0,pTarget);
      // Gifteffekt anhängen, bzw verlängern
      if(!GetEffect("BulletPoision",pObject))
      {
        AddEffect("BulletPoision",pObject,20,3,0,PBLT,GetOwner());
        if(GetEffect("BulletPoision",pObject))
          EffectVar(2,pObject,GetEffect("BulletPoision",pObject))=100;
      }
      else
        EffectVar(2,pObject,GetEffect("BulletPoision",pObject))+=100;
      pTarget->CreateParticle("PSpark",0,0,0,0,100,RGB(0,255,0));
    }
  }
 
  return(1);
}

protected func FxPoisionFistPSpellIncTime(pTarget,iEffectNumber)
{
  EffectVar(0,pTarget,iEffectNumber)+=(30*60*3)/2;
 
  return(1);
}

protected func FxPoisionFistPSpellStop(pTarget, iNumber, iReason, fTmp)
{
  if(fTmp) return();
  if(GetAlive(pTarget))
  { 
    for(var cnt=0;cnt<15;cnt++)
    CreateParticle("PSpark",GetX(pTarget),GetY(pTarget),RandomX(-5,5),-10,250,RGB(10,50,10));
  }
}

protected func FxPoisionFistPSpellInfo() { return("{{PIFT}} $SpellInfo$"); }

/* Zaubercombo */

public func GetSpellStaff(object pMage) { return(SMOD); }
public func GetSpellStaffCombo(pMage) { return ("63"); } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
