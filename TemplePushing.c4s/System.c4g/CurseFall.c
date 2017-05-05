/*-- Improve falling curse kill tracking --*/

#strict 2
#appendto CFAL

protected func FxCurseFallingStart(pClonk, iEffectNumber, iTemp, iX, iY, pCaller)
{
	EffectVar(6, pClonk, iEffectNumber) = GetController(pCaller);
	return _inherited(pClonk, iEffectNumber, iTemp, iX, iY, pCaller);
}

protected func FxCurseFallingTimer(pClonk, iEffectNumber, iEffectTime)
{
	var rval = FxCurseTimer(pClonk, iEffectNumber, iEffectTime);
	if (rval != FX_OK) return rval;
	if (FxCurseIsActive(pClonk, iEffectNumber))
	{
		var killer = EffectVar(6, pClonk, iEffectNumber);
		// Bei Bedarf stolpern
		if(pClonk->GetContact(0, -1, 8))
		{
			if(GetXDir(pClonk) || GetAction(pClonk) != "Walk" )
			{
				if(WildcardMatch(GetAction(pClonk), "*Magic") || WildcardMatch(GetAction(pClonk), "*Cast"))
				{
					// Bei Magie-Aktion nicht so häufig stören
					if(!Random(120)) { ObjectSetAction(pClonk, "FlatUp"); SetXDir(0, pClonk); SetKiller(killer, pClonk); }
				}
				else
				{
					if(!Random(60)) { ObjectSetAction(pClonk, "KneelDown"); SetXDir(0, pClonk); SetKiller(killer, pClonk); }
					if(!Random(60)) { ObjectSetAction(pClonk, "FlatUp"); SetXDir(0, pClonk); SetKiller(killer, pClonk); }
				}
			}
		}
		// In Flug nur Tumble
		else
		{
			if(!Random(50)) { ObjectSetAction(pClonk, "Tumble"); SetKiller(killer, pClonk); }
		}
	}
	return FX_OK;
}
