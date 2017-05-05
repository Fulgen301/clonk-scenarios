/*-- Neues Script --*/

#strict
#appendto PRST

func FxGodTimer(pTarget, iNumber, iTime)
{
  if(EffectVar(0, pTarget, iNumber))
    EffectVar(0, pTarget, iNumber)--;

  if(!Random(150))
    if(GetEnergy()<GetKarmaEnergy(GetOwner()))
    {
      DoEnergy(1);
      if(!Random(4)) DoKarmaEnergy(-1, GetOwner());
      CreateParticle("PSpark",RandomX(-7,7),RandomX(-7,7),0,-1,15,RGB(255,255,10),this(),Random(2));
    }

  if(!EffectVar(0, pTarget, iNumber))
    if(GetProcedure()S="FIGHT")
      if(!Random(800-GetKarmaEnergy(GetOwner())*2) && GetActionTarget())
        if(GetEnergy()<GetEnergy(GetActionTarget()))
        {
          DoLightningEffect(GetActionTarget());
          DoEnergy(-10-Random(5), GetActionTarget());
          DoKarmaEnergy(-5, GetOwner());
          EffectVar(0, pTarget, iNumber)=(150-GetKarmaEnergy(GetOwner()))*10;
        }
}

func FxGodDamage(pTarget, iNumber, iDmgEngy, iCause)
{
  if(iDmgEngy>0) return(iDmgEngy);
  if(EffectVar(0, pTarget, iNumber)) return();
  if(!Random(6) && -iDmgEngy/1000>=GetEnergy())
    if(GetKarmaEnergy(GetOwner())>(iDmgEngy/500))
    {
      iDmgEngy = -GetEnergy()*1000 + 1000;
      for(var i=0; i<360; i+=30)
        CreateParticle("NoGravSpark", 0,0,-Sin(i, 5)+RandomX(-2,2),Cos(i,20)+RandomX(-2,2), 50, RGB(155,130,0), this(), 1);
      EffectVar(0, pTarget, iNumber) = 36*10;
    }
  return(iDmgEngy);
}
