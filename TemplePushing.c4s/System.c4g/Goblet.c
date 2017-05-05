/*-- Add unique Goblet mechanics --*/

#strict 2

#appendto GBLT

local energyLeft;

public func Initialize()
{
	energyLeft = 100;
	return _inherited();
}

/* If a clonk holds the goblet and it has more than 50% energy left, a bad effect is removed (if present).
 * If less than 50% energy is left or no negative effects are present, the clonk gets healed. */
private func FillCheck()
{
	var ret = _inherited();

	if (iTimer >= 5)
	{
		var clonk = Contained();
		if (clonk && clonk->GetOCF() & OCF_CrewMember)
		{
			// Remove bad effect if present
			if (energyLeft >= 50 && RemoveBadEffect(clonk))
			{
				energyLeft -= 50;
			}
			else // Transfer 10 energy points from goblet to clonk
			{
				var maxEnergy = clonk->GetPhysical("Energy") / 1000;
				var doEnergy = Min(maxEnergy - clonk->GetEnergy(), Min(10, energyLeft));
				clonk->DoEnergy(doEnergy);
				energyLeft -= doEnergy;
			}

			if (energyLeft == 0) SetEmpty();
		}
		iTimer = 0;
	}
	return ret;
}

private func RemoveBadEffect(object clonk)
{
	// Unfreeze clonk if frozen
	if (Frozen(clonk))
	{
		Unfreeze(clonk);
		return true;
	}

	// Extinguish clonk if on fire
	if (clonk->OnFire())
	{
		clonk->Extinguish();
		return true;
	}

	// Remove a curse if at least one is present
	if (RemoveAnyEffect("*Curse*", clonk, "!CAHE->FxCurseIsActive")) return true;

	// Remove plague effect if present
	if (RemoveAnyEffect("Poison", clonk)) return true;

	// Remove a negative spell if at least one is present
	if (RemoveAnyEffect("*NSpell", clonk)) return true;

	// Fail if there is no bad effect to remove
	return false;
}

private func RemoveAnyEffect(string name, object target, string checkCall)
{
	// Create an array of effect numbers matching name and target
	var effectNumbers = [];
	for (var i = 0; i < GetEffectCount(name, target); ++i)
	{
		var effectNumber = GetEffect(name, target, i);
		if (effectNumber == 0) break;
		if (checkCall && eval(Format("%s(Object(%d), %d)", checkCall, ObjectNumber(target), effectNumber))) continue;
		effectNumbers[GetLength(effectNumbers)] = effectNumber;
	}

	// Fail if no effects were found
	if (GetLength(effectNumbers) == 0) return false;

	// Randomly select an effect to remove
	RemoveEffect(0, target, effectNumbers[Random(GetLength(effectNumbers))]);

	return true; // Success
}
