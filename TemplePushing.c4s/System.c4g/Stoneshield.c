/*-- Only show selector if targets are available and recolour particles by team --*/
#strict 2
#appendto MSSH

func Activate(pCaster,pRealcaster)
{
	var pClonk=pRealcaster;
	if(!pClonk) pClonk=pCaster;

	var pCombo;
	// Stein verlängert die Wirkungsdauer
	if (pCombo = FindContents(ROCK, pCaster))
	{
		fRock = true;
		RemoveObject(pCombo);
	}

	// Auswählen wenn möglich
	var comDir = pClonk->GetComDir();
	var selector;
	if ((selector = pClonk->~DoSpellSelect(this,300,pCaster)) && (selector->CountTargets() > 1 || !SelectorTarget(pClonk))) return 1;
	if (selector)
	{
		pCaster->SpellSucceeded(GetID(), pClonk);
		RemoveObject(selector);
	}
	pClonk->SetComDir(comDir);

	// Clonk kann nicht auswählen: Clonk bekommst selbst ein Schild
	if (SelectorTarget(pClonk))
		return(ActivateTarget(pClonk, pClonk));

	// ansonsten geth nich
	RemoveObject();
	return(0);
}

func FxStoneShieldPSpellTimer(pClonk, iEffectNumber, iEffectTime)
{
  // Keine St舐ke mehr, weg damit
  if(!EffectVar(0,pClonk,iEffectNumber)) return(-1);
  // Effekt!
  if (!Random(3)) CastParticles("PSpark", 1, 10, GetX(pClonk), GetY(pClonk)+4, 50, 80, GetPlrColorDw(GetOwner(pClonk)), GetPlrColorDw(GetOwner(pClonk)), pClonk);
  return(1);
}