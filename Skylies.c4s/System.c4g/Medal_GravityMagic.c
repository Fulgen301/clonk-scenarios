/*-- Neues Script --*/

#strict 2
#appendto GVTY

func FxStopNSpellStart(pTarget, iIndex, iTime)
{
  //BlindEffekt anhängen, falls Meteorit
  if(GetID(pTarget) == METO)
  {
    SetMass(50,pTarget);
    AddEffect("BlindEffect",pTarget,100);
    SetController(GetOwner(this),pTarget);
  }
  return _inherited(...);
}
