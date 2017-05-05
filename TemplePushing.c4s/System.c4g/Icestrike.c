/*-- Make Ice Strike compatible with scrolls and Aimer --*/

#strict 2

#appendto MICS

func Activate(pCaller, pRealcaller)
{
	var pClonk;
	if(pRealcaller) pClonk=pRealcaller;
	else pClonk=pCaller;

	// Effekt prüfen
	var iResult;
	if (iResult = CheckEffect("IcestrikeNSpell", 0, 125)) return(iResult!=-1 && RemoveObject());

	// Zauber
	Sound("Magic*");
	var iX, iY;
	iX=AbsX(GetX(pCaller)-25+50*GetDir(pCaller));
	iY=AbsY(GetY(pCaller));
	pBall=CreateObject(ICEB, AbsX(GetX(pCaller)-25+50*GetDir(pCaller)), AbsY(GetY(pCaller)), GetOwner(pCaller));
	pBall->SetCaster(pCaller);

	// Zielen wenn möglich
	if (pClonk->~DoSpellAim(this(), pCaller)) return(1);
	return(1);
}

// Aktivierung nach Zielen (iAngle: -90=links; 0=oben; +90=rechts)
public func ActivateAngle(object pCaller, int iAngle)
{
	// Eisball freigeben (wenn noch existent)
	if (pBall) pBall->SetAngle(iAngle);
	
	// Objekt löschen
	return(RemoveObject());
}