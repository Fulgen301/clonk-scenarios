/*-- Neues Script --*/

#strict 2
#appendto CHEM

protected func Collection(object pObject)
{
  if(GetID(pObject)->~ExplodeSize())
    AddEffect("ChemPlantImminentDestruction", pObject, 1, 108, this, CHEM, GetController(pObject));

  return inherited(...);
}

func FxChemPlantImminentDestructionStop(object pTarget, int iEffectNumber, int iCause) 
{
  if(GetID(Contained(pTarget)) != CHEM) return false;
  if(ContentsCount(GUNP,Contained(pTarget))*30 + ContentsCount(GBRL,Contained(pTarget))*50 >= 100)
  {
    var pMedal = FindObject(H1_M);
    if(pMedal)
      Reward(pMedal,GetController(pTarget));
  }
  return true;
}
