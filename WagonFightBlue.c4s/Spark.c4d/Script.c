/* Funken */

#strict

protected func CreateSpark()
{
	// Immer je links und rechts einen Spark erschaffen, die sich an der Mittelachse spiegeln
	// Über den Burgen seltener
	var y = Position();
	var x = Random(Random(LandscapeWidth() / 2 - 25));
	CreateObject(GetID(), LandscapeWidth() / 2 + x - GetX(), y, -1);
	CreateObject(GetID(), LandscapeWidth() / 2 - x - GetX(), y, -1);
	return 1;
}

public func Position()
{
	var y;
	var i = Random(8);
	if (!i)
		y = 0;
	if (!--i)
		y = 50;
	if (!--i)
		y = 100;
	if (!--i)
		y = 150;
	if (!--i)
		y = 200;
	if (!--i)
		y = 250;
	if (!--i)
		y = 300;
	if (!--i)
		y = 350;
	return y;
}


protected func Initialize() {
	return SetAction("Fall");
}
protected func Hit() {
	return SetAction("Sparkle");
}
protected func Removal() {
	return RemoveObject();
}

protected func CastObject()
{
	var y = 0;
	if (GetY() > 130)
		y = 1;
	if (GetY() > 250)
		y = 2;
	var fIsInMiddle = Abs(GetX() - LandscapeWidth() / 2) < LandscapeWidth() / 6;
	var ID = RndObjectID(fIsInMiddle, y);
	if (ID == SCRL) {
    var rand = Random(4);
    var magic;
    if (rand == 0)
    	magic = CDIR;
    else if (rand == 1)
    	magic = SWGN;
    else if (rand == 2)
    	magic = WGNS;
	else
    	magic = MMTR;
    CreateObject(ID, 0, 0, -1)->SetMagic(magic);
		Sound("Boing");
		return 1;
	}
	if (ID == XARP) {
		CreateObject(ID, 0, 0, -1)->DoPackCount(-5);
		Sound("Boing");
		return 1;
	}
	if (ID == CATA) {
		CreateObject(ID, 0, 0, -1)->CreateContents(SFLN, 0, 2);
		Sound("Boing");
		return 1;
	}
	if (ID == XBOW) {
		CreateObject(ID, 0, 0, -1)->CreateContents(ARWP, 0, 1);
		Sound("Boing");
		return 1;
	}
	CreateObject(ID, 0, 0, -1);
	Sound("Boing");
	return 1;
}

protected func RndObjectID(fMiddle, y)
{
	var r = Random(100);
	if (!--r)
		return FARP;
	// Seltene Objekte
	r = Random(80);
	if (!--r)
		if (y == 2)
			return BRED;
		else {
			r++;
		}
	if (!--r)
		return SPER;
	// Mittlere Häufigkeit
	if (fMiddle) {
		r = Random(14);
		if (!--r)
			return MONS;
		if (!--r)
			return GUNP;
		if (!--r)
			return AXE1;
		if (!--r)
			return WBRL;
		if (!Random(24))
			return CATA;
		if (!Random(30))
			return XBOW;
	}
	// Normale Objekte
	r = Random(13);
	if (!r)
		return FLNT;
	if (!--r)
		return SFLN;
	if (!--r)
		if (y)
			return COKI;
		else 
			r++;
	if (!--r)
		return STFN;
	if (!--r)
		return FBMP;
	if (!--r)
		return BOW1;
	if (!--r)
		return ARWP;
	if (!--r)
		return SWOR;
	if (!--r)
		return SCRL;
	if (!--r)
		return SHIE;
	if (!--r)
		return SFLN;
	if (!--r && fMiddle)
		return XARP;
	return TFLN;
}

protected func Sparkle()
{
	CreateParticle("PSpark", 0, 0, 0, 0, 200, RGB(50, 50, 255), this(), 1);
}
