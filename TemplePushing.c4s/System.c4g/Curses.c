/*-- Prevent curse scrolls from vanishing --*/
/*-- Limit lifetime of activated curse */

#strict 2

#appendto CAHE

public func Activate(pCaster,pRealcaster)
{
  var pClonk=pRealcaster;
  if(!pClonk) pClonk=pCaster;
  if (!pClonk) return(1);

  pCasterClonk = pClonk; // Caster speichern, damit es sich unter keinen Umständen selber wählen kann
  // Auswählen wenn möglich
  if (pClonk->~DoSpellSelect(this(), 300, pCaster)) return(1);

  var pTarget;
  // Clonk kann nicht auswählen: nächsten Gegner verfluchen
  while(pTarget=FindObject(0,-300,-300,150,150,OCF_CrewMember,0,0,NoContainer(),pTarget))
      if(SelectorTarget(pTarget))
              return(ActivateTarget(pTarget));

  // ansonsten geht nich
  RemoveObject();
  return(0);
}

public func ActivateTarget(object pCaller, object pTarget)
{
	if (!pTarget)
	{
		if (pCaller) pCaller->OnSelectorAbort();
		return RemoveObject();
	}
	return _inherited(pCaller, pTarget);
}

protected func FxCurseTimer(pClonk, iEffectNumber, iEffectTime)
{
	var rval = _inherited(pClonk, iEffectNumber, iEffectTime);
	if (rval != FX_OK) return rval;

	if (EffectVar(2, pClonk, iEffectNumber) <= 0)
	{
		if (GetActivatedLifeTime() + --EffectVar(2, pClonk, iEffectNumber) <= 0) return FX_Execute_Kill;
	}

	return FX_OK;
}

protected func FxCurseIsActive(pClonk, iEffectNumber)
{
	// Old meaning of effect variable 2: true if still chasing target or false if activated
	// New meaning:
	//  == 1: Still chasing target
	//  <= 0: Was activated and remaining lifetime is GetActivatedLifeTime() + value
	return EffectVar(2, pClonk, iEffectNumber) <= 0;
}

private func GetActivatedLifeTime() { return 720 / 2; }
