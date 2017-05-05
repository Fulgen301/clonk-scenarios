#strict 2

func Activate(object pCaster, object pRealcaster)
{
	if(!pRealcaster)
	{
		pRealcaster = pCaster;
	}

	if(pRealcaster->~DoSpellAim(this, pCaster))
	{
		return 1;
	}

	var angle = 90 * (GetDir(pRealcaster)* 2 - 1);
	ActivateAngle(pRealcaster, angle);
	Sound("Magic", 0, pCaster);
	RemoveObject();
	return 1;
}

public func ActivateAngle(object pCaller, int iAngle)
{
	for(var i = 0; i < 3; ++i)
	{
		CreateObject(ICNA, AbsX(GetX(pCaller) + Sin(iAngle, 13)), AbsY(GetY(pCaller) - Cos(iAngle, 13)), GetOwner(pCaller))->Activate(pCaller, iAngle + (i - 1) * 5);
	}

	RemoveObject();
	return 1;
} 

public func HoldAimer(pCaller)
{
	return true;
}

/* Zaubercombo */

public func GetSpellClass(object pMage) { return WATR; }
public func GetSpellCombo(pMage) { return "444"; }
