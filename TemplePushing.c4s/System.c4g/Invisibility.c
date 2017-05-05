/*-- Shorten Invisibilty duration --*/

#strict 2

#appendto MINV

public func Activate(object pCaster, object pCaster2)
{
	// Zauberer ermitteln
	if (pCaster2) pCaster = pCaster2;
	// Magie kann man hoeren, ganz klar ;)
	Sound("Magic*");
	// Zauberer unsichtbar machen (20sec)
	AddEffect("InvisPSpell", pCaster, 200, 720, 0, GetID());
	// Fertig - das Zauberobjekt wird nun nicht mehr gebraucht
	RemoveObject();
	return 1;
}

protected func FxInvisPSpellAdd(object pTarget, int iEffectNumber, string szNewEffect, int iNewTimer)
{
	// Effekt aufrechnen: Rest vom alten Timer ermitteln
	var iOldTimer = GetEffect(0, pTarget, iEffectNumber, 3) - GetEffect(0, pTarget, iEffectNumber, 6);
	// Diesen Effekt mit neuem Timer weiterführen
	ChangeEffect(0, pTarget, iEffectNumber, szNewEffect, iOldTimer + 360);
	// Fertig
	return(1);
}
