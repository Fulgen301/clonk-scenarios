/*-- Optimize Gravity spell --*/

#strict 2
#appendto GVTY

func FxFloatPSpellTimer(pClonk, iEffectNumber, iEffectTime)
{
	if(!EffectVar(0,pClonk,iEffectNumber)) return -1;
	if(!EffectVar(1,pClonk,iEffectNumber)) return -1;
	EffectVar(0,pClonk,iEffectNumber)--;

	var iSearchRadius = GetRange();
	var pObj;
	CreateParticle("WhiteAura",GetX(pClonk),GetY(pClonk), RandomX(-1,1), RandomX(-1,1), 12*iSearchRadius,GetPlrColorDw(GetOwner(pClonk)), pClonk);
	var i=2;
	while(i--)
	{
		var angle = RandomX(-180, 180);
		CreateParticle("PSpark",GetX(pClonk)+Sin(angle, iSearchRadius),GetY(pClonk)-Cos(angle, iSearchRadius),
									 -Sin(angle, iSearchRadius/3),Cos(angle, iSearchRadius/3),RandomX(50,70),
									 RGBa(150,155,80, 75),pClonk);
	}
	CastParticles("PSpark", 3, iSearchRadius/3, GetX(pClonk), GetY(pClonk)+8, 50, 70, RGBa(150,155,80, 75), RGBa(150,155,80, 75), pClonk);

	// Find objects and stop them
	for(var obj in FindObjects(Find_Distance(iSearchRadius, GetX(pClonk), GetY(pClonk)), Find_Not(Find_Func("IgnoreFloatSpell")), Find_Not(Find_OCF(OCF_CrewMember)), Find_Not(Find_Effect("StopNSpell")), Find_NoContainer())) EffectVar(1,pClonk,iEffectNumber)->~DoStop(obj, pClonk);

		return 1;
}

func FxStopNSpellTimer(pTarget, iNumber, iEffectTime)
{
	if(iEffectTime>600) return -1;

	SetXDir(0,pTarget);
	SetYDir(-2 * GetGravity(),pTarget,1000);

	if (!FindObject2(Find_ID(GVTY), Find_Distance(GetRange(), GetX(pTarget), GetY(pTarget)))) return -1;
}

func DoStop(object pObj, object pCaller)
{
	if(GetEffect("StopNSpell", pObj)) return;
	pObj->~MagicStop(pCaller);
	AddEffect("StopNSpell", pObj, 200, 1, 0, GVTY);

	return 0;
}

func FxFloatPSpellStart(pClonk, iEffectNumber, iTemp)
{
	if(iTemp) return;
	var ret = _inherited(pClonk, iEffectNumber, iTemp, ...);
	EffectVar(0,pClonk,iEffectNumber) = 360;
	return ret;
}

private func FxFloatPSpellAdd(object pTarget, int iNumber)
{
	// Effekt übernehmen
	EffectVar(0, pTarget, iNumber) += 180;
}
