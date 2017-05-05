/*-- Prevent caster from setting himself on fire --*/
#strict 2
#appendto FBRT

local pTarget;

func Activate(pTrg,iTime,iXPos,iYPos,iAngle,iAngleDir,int iExtraSpeed, bool fDeadly) {
	iLifetime=iTime;			// Zeit bis das Ding gelöscht wird
	iX=iXPos;				// Von der Mitte abweichende Position (X)
	iY=iYPos;				// Von der Mitte abweichende Position (Y)
	iSpeed = FBRT_BaseSpeed + iExtraSpeed;// Geschwindigkeit: Basisgeschwindigkeit + Zusatz
	SetR(iAngle);
	SetRDir(iAngleDir);			// Rotationsgeschwindigkeit
	SetAction("Exist",pTrg);		// Objekt an dass es pseudo-attached wird
	fLethal = fDeadly;
	pTarget = pTrg;
}

protected func InflameTimer()
{
	DoCon(+20);
	// In Material, was Feuer löscht (Wasser): löschen
	if(GetMaterialVal("Extinguisher","Material",GetMaterial(0,0)))
	{
		Smoke(0, 0, 24);
		return RemoveObject();
	}
	// Zeug anzünden
	var obj;
	while (obj = FindObject(0, 0,1, 0,0, OCF_Inflammable, 0,0, NoContainer(), obj))
		if (!OnFire(obj) && obj != pTarget) if (!Random(GetDefContactIncinerate(GetID(obj))))
			Incinerate(obj);
}

func Timer() { // alle 4 Frames
	var iXDir,iYDir,iAngle;
	var pActTarget = GetActionTarget();
	// Kein Feuer-Spucker: löschen
	if(!pActTarget) return(RemoveObject());
	// Magischer Feuerspucker muss die ganze Zeit zaubern
	var iMLength=GetActMapVal("Length",GetAction(pActTarget),GetID(pActTarget));
	if(GetActMapVal("Name","Magic",GetID(pActTarget))) {
		// z.B. während des Zauberns durch einen Stein getroffen
		if(!DoesMagic(pActTarget)) return(RemoveObject());
		// Zauberaktion für das zaubernde Objekt: Es wird angenommen, dass diese
		// in einem Raum von etwa 2/6 bis 5/6 der Zauberaktion spielt
		if(GetPhase(pActTarget) >= iMLength*5/6) SetPhase(iMLength*2/6,pActTarget);
	}

	// In Material, was Feuer löscht (Wasser): löschen
	if(GetMaterialVal("Extinguisher","Material",GetMaterial(0,0)))
	{
		Sound("Pshshsh");
		return RemoveObject();
	}
	// löschen
	if(GetActTime()>iLifetime) return(RemoveObject());

	// Pseudo-Attach
	SetPosition(GetX(pActTarget),GetY(pActTarget));

	// Größe+Drehung des Zielobjektes in die Position einbeziehen
	var iX2 = (Cos(GetR(pActTarget), iX*GetCon(pActTarget)) - Sin(GetR(pActTarget), iY*GetCon(pActTarget)))/100;
	var iY2 = (Sin(GetR(pActTarget), iX*GetCon(pActTarget)) + Cos(GetR(pActTarget), iY*GetCon(pActTarget)))/100;

	// Optionales Vertex-Attachment am Trägerobjekt (überschreibt vorhergehende Ausrichtungsfunktionen)
	if (fVertexAttach)
	{
		iX2 = pActTarget->GetVertex(iAttachVertex, 0);
		iY2 = pActTarget->GetVertex(iAttachVertex, 1);
	}

	for(var i=iSpeed/60+1; i>0 ;--i) {

		iAngle=RandomX(-12,+12);

		// Winkel usw berechnen
		if(!Random(3)) iAngle=RandomX(-12,+12);
		iXDir=Sin(GetR()+iAngle,iSpeed) + GetXDir(GetActionTarget());
		iYDir=-Cos(GetR()+iAngle,iSpeed) + GetYDir(GetActionTarget());

		// Effekt
		CreateParticle("DBFire",iX2,iY2,iXDir,iYDir,RandomX(50,100),RGB(255,255,255));

		// Anzünd-Objekte in die Richtung verschießen
		var inflamer = CreateObject(FBRT,
								 iX2+Sin(GetR()+iAngle,10),
								 iY2-Cos(GetR()+iAngle,18),
								 GetOwner());
		LocalN("pTarget", inflamer) = pTarget;
		inflamer->ActivateInflamer(iXDir, iYDir, fLethal);
	}
}

func QueryOwnCatchBlow(object target)
{
	if (target == pTarget) return true;
	else return _inherited(target, ...);
}

func QueryIncinerateObject(object target)
{
	if (target == pTarget) return true;
	else return _inherited(target, ...);
}
