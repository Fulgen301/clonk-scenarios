/*-- Misteriöser Kopf --*/

// Script v2.0 by Miniwipf
#strict 2

// Damit er Objekt ausspuckt müssen diese sich im Inhalt befinden

// Local
local _iMinP, _iMaxP; 


/* ENGINE */

protected func Initialize()
{
  // Normalerweise ausgeschaltet
  SwitchOff();
  // SolidMask setzen
  UpdateTransferZone();
  return 1;
}

protected func Throw()
{
	// Nix zum schiessen
	if (!Contents()) return 1;
	// Sound
	Sound("Throw");
	// Flint rausspucken
	var p = RandomX(_iMinP, _iMaxP);
	var r = GetR()-90;
	var dir = GetDir();
	var obj = Contents(Random(ContentsCount()));
	Exit(obj, GetVertex(dir, 0), GetVertex(dir, 1),, Sin(r + 180*dir, p), -Cos(r + 180*dir, p));
	// Partikeleffekt
	AddEffect("FlintEffect", obj, 120, 1, this,, p*5);
	return 1;
}

protected func CheckEntrance()
{
	// Doch nur in einem gewissen Bereich aufnehmen
	var dir = GetDir();
	for (var obj in FindObjects(Find_Distance(11, GetVertex(dir, 0), GetVertex(dir, 1)), Find_Category(C4D_Object), Find_Not(Find_ID(MRCK)), Find_Not(Find_ID(CITB)))) // Getarnte Magier (MRCK) sind nicht so lecker
		if (!GetEffect("FlintEffect", obj))
			Enter(this, obj);
	return 1;
}

/* PUBLIC */

// Optionen

public func SwitchOn()
{
	// Sound
	Sound("SwitchOn");
  SetAction("On");
}

public func SwitchOff()
{
  SetAction("Off");
}

public func SetPower(int iMinP, int iMaxP)
{
	_iMinP = iMinP;
	_iMaxP = iMaxP;
	return 1;
}

// überladen

public func SetDir()
{
	var r = inherited(Par(0), Par(1), Par(2), Par(3), Par(4), Par(5), Par(6), Par(7), Par(8), Par(9));
	UpdateTransferZone();
	return r;
}

protected func UpdateTransferZone()
{
  return SetSolidMask(GetDir()*20, 52, 20, 52);
}

/* EFFEKTE */

public func FxFlintEffectStart(object pTarget, int iNr, int iTemp, int iMaxLifeTime)
{
	if (iTemp) return;
	EffectVar(0, pTarget, iNr) = iMaxLifeTime;
	return 1;
}

public func FxFlintEffectTimer(object pTarget, int iNr, int iTime)
{
	// Partikeleffekt
	var s;
	for (var i=Random(5); i; i--) {
		s = 20+Random(41);
		CreateParticle("PxSpark", AbsX(GetX(pTarget))+RandomX(-3, 3), AbsY(GetY(pTarget))+RandomX(-3, 3),,, s, RGBa(255, Random(100), s*4, 128));
	}
	CreateParticle("PxSpark", AbsX(GetX(pTarget)), AbsY(GetY(pTarget)),,, 5*5, RGBa(255, 155, 0, 128));
  
	// Jemand hat den Flint gefangen?
	if (Contained(pTarget)) return -1;

	// Zeit abgelaufen
	if (EffectVar(0, pTarget, iNr)-iTime <= 0) return -1;
}
