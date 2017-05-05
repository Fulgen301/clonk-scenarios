/*-- Increase distance to caster to avoid autokills --*/
/*-- Prevent Fire Ball from being held indefinitely --*/

#appendto FIRB
#strict 2

func FxFireballFlightTimer(pTarget, iEffectNumber, iEffectTime)
{
	var iSize=EffectVar(0, pTarget, iEffectNumber);
	var iMaxSize=EffectVar(1, pTarget, iEffectNumber);
	var iAngle=EffectVar(2, pTarget, iEffectNumber);
	var iLaunchFree=EffectVar(3, pTarget, iEffectNumber);
	var pCaster = EffectVar(4, pTarget, iEffectNumber);
	var iSizeBoost=EffectVar(5, pTarget, iEffectNumber);
	if(iSize<=0) return(RemoveObject());
	if(GBackLiquid()) return(RemoveObject());
	// Effekt
	for( var i=4; i>0; --i)
	{
		CreateParticle("Fire",  RandomX(-iSize/50,iSize/50), RandomX(-iSize/50,iSize/50), RandomX(-2,2)+GetXDir()/2, RandomX(-2,2)+GetYDir()/2, iSize*60/100+Random(15), RGBa(Random(255),0,0,90));
		CreateParticle("Fire2", RandomX(-iSize/50,iSize/50), RandomX(-iSize/50,iSize/50), RandomX(-2,2)+GetXDir()/2, RandomX(-2,2)+GetYDir()/2, iSize+Random(15));
	}
	// Ausrichtung nach Caster
	if (!iLaunchFree && pCaster)
	{
		if(iEffectTime > 180)
		{
			var aimer = LocalN("pAimer", pCaster) || LocalN("pAimer", LocalN("pAimingClonk", pCaster));
			if(aimer)
			{
				aimer->ControlThrow();
			}
			return Hit();
		}
		else
		{
			var x=GetX(pCaster)+Sin(iAngle, 25), y=GetY(pCaster)-Cos(iAngle, 25);
			if (GetX()!=x || GetY()!=y)
			{
			DrawParticleLine("Fire", x-GetX(), y-GetY(), 0, 0, 5, 40, 16777215, 16777215, 0);
				SetPosition(x, y);
			}
		}
	}
	// Noch nicht voll aufgeladen?
	if (iSize < iMaxSize)
	{
		for( var i=5; i>0; --i)
		{
			var iR, iD;
			var iX=Sin(iR=Random(360), iD=RandomX(iSize/10,iSize/5));
			var iY=Cos(iR, iD);
			CreateParticle("Fire", iX, iY, -iX/3, -iY/3, Random(25), RGBa(Random(255),0,0,90));
			CreateParticle("Fire2", iX, iY, -iX/3, -iY/3, Random(35));
		}
		// Vergrößern
		EffectVar(0, pTarget, iEffectNumber) = ++iSize;
		// Nichts weiter während des Wachsens
		return(1);
	}
	// Abschuss noch nicht freigegeben?
	if (!iLaunchFree) return(1);
	// Maximale Laufzeit
	if(iEffectTime-iLaunchFree>550) return(RemoveObject());
	// Geschwindigkeit anpassen
	SetXDir(Sin(iAngle, FIRB_Speed));
	SetYDir(-Cos(iAngle, FIRB_Speed));
	// Suche nach brennbaren Zielen
	var pObj;
	while(pObj=FindObject(0, 0, 1, 0, 0, OCF_Inflammable, 0, 0, NoContainer(), pObj))
	{
		if(GBackLiquid(GetX(pObj), GetY(pObj))) continue;
		if(GetOCF(pObj) & OCF_CrewMember) if (GetAlive(pObj)) return(Hit());
		if(iSizeBoost || !Random(3)) Incinerate(pObj);
	}
	// Zielen auf CrewMember - klappt wegen Winkelüberlauf schlecht gerade nach unten (was solls...)
	var iMinAngleDiff = 360, iTargetAngle = iAngle;
	while (pObj = FindObject(0, Sin(iAngle, FIRB_AimSearchRange)-FIRB_AimSearchRange/2, -Cos(iAngle, FIRB_AimSearchRange)-FIRB_AimSearchRange/2, FIRB_AimSearchRange, FIRB_AimSearchRange, OCF_CrewMember, 0,0, NoContainer(), pObj))
	{
		if (!GetAlive(pObj)) continue;
		var iThisTargetAngle = Angle(GetX(), GetY(), GetX(pObj), GetY(pObj));
		if (iThisTargetAngle > 180) iThisTargetAngle -= 360;
		if (Abs(iThisTargetAngle - iAngle) < iMinAngleDiff)
		{
			iMinAngleDiff = Abs(iThisTargetAngle - iAngle);
			iTargetAngle = iThisTargetAngle;
		}
	}
	EffectVar(2, pTarget, iEffectNumber) = BoundBy(iTargetAngle, iAngle-FIRB_AimDirAdjust, iAngle+FIRB_AimDirAdjust);
	// OK; weiter existieren
	return(1);
}
