/*-- Objekte --*/

// script v1.9 by miniwipf
#strict 2

global func Scenario()
{
	CreateObject(SBRD); // Scoreboard erstellen (wichtig für g_aPlrData und so..)
	Landscape();
	Objects();
	return 1;
}

global func Landscape()
{
	// Himmel
	SetSkyParallax(0, 70, 80);
	/* Schiefe Flächen */
	// Brunnen
	DrawMaterialQuad("BackWall-Bricks2", 1183, 680, 1206, 680, 1206, 782, 1183, 782, 1);

	/* Turm links aussen */
	// Dach
	DrawMaterialQuad("SmoothWall-Bricks1", 160, 470, 160, 460, 250, 550, 240, 550, 1);
	DrawMaterialQuad("SmoothWall-Bricks1", 130, 490, 120, 490, 150, 460, 150, 470, 1);
	DrawMaterialQuad("SmoothWall-Bricks1", 80, 540, 70, 540, 90, 520, 90, 530, 1);
	DrawMaterialQuad("Wall-Bricks1", 110, 530, 110, 530, 110, 520, 130, 530, 1);
	// Treppen
	DrawMaterialQuad("SmoothWall-Bricks1", 130, 660, 130, 650, 150, 670, 140, 670, 1);
	DrawMaterialQuad("SmoothWall-Bricks1", 150, 790, 150, 780, 190, 820, 180, 820, 1);
	// Zinnen
	DrawMaterialQuad("SmoothWall-Bricks1", 30, 620, 30, 620, 40, 620, 40, 630, 1);
	DrawMaterialQuad("SmoothWall-Bricks1", 220, 630, 230, 620, 240, 620, 220, 640, 1);
	DrawMaterialQuad("SmoothWall-Bricks1", 240, 780, 240, 780, 240, 770, 250, 770, 1);
	// Fahrstuhl
	DrawMaterialQuad("SmoothWall-Bricks1", 40, 630, 40, 610, 45, 610, 45, 630, 1);

	/* Bereich rechts neben dem Wassergraben */
	// Treppen
	DrawMaterialQuad("SmoothWall-Bricks1", 460, 820, 450, 820, 520, 750, 520, 760, 1);
	DrawMaterialQuad("SmoothWall-Bricks1", 450, 680, 450, 670, 500, 720, 490, 720, 1);
	// Zinnen
	DrawMaterialQuad("SmoothWall-Bricks1", 410, 660, 420, 660, 430, 670, 430, 680, 1);

	/* Burg Hauptteil */

	/* Links */
	// Zinnen
	DrawMaterialQuad("SmoothWall-Bricks1", 490, 550, 500, 550, 510, 560, 510, 570, 1);
	// Kammer rechts über Eingang: Schräge am Boden und decke
	DrawMaterialQuad("SmoothWall-Bricks1", 590, 570, 620, 540, 620, 550, 600, 570, 1);
	DrawMaterialQuad("SmoothWall-Bricks2", 570, 550, 570, 540, 600, 510, 610, 510, 1);
	// Schräge am boden darüber ^^
	DrawMaterialQuad("SmoothWall-Bricks1", 560, 530, 600, 490, 600, 500, 570, 530, 1);
	// Linke Wand
	DrawMaterialQuad("SmoothWall-Bricks1", 520, 400, 520, 400, 540, 400, 540, 470, 1);
	// darunter ein kleines Dreieck, damit die wand nicht so dünn aussieht :O
	DrawMaterialQuad("SmoothWall-Bricks1", 540, 460, 540, 460, 540, 450, 550, 460, 1);

    DrawMaterialQuad("BackWall-Bricks2", 640, 420, 690, 420, 690, 430, 640, 430, 1);

	/* Oben */
	// Grosse Treppe nach rechts und decke darüber
	DrawMaterialQuad("SmoothWall-Bricks1", 620, 430, 680, 370, 680, 380, 630, 430, 1);
	DrawMaterialQuad("SmoothWall-Bricks1", 640, 370, 640, 360, 650, 350, 660, 350, 1);
	// Kleinere Treppe, die nach links abzweigt und decke darüber
	DrawMaterialQuad("SmoothWall-Bricks1", 580, 380, 580, 370, 600, 390, 590, 390, 1);
	//DrawMaterialQuad("SmoothWall-Bricks1", 570, 330, 580, 330, 610, 360, 610, 370, 1);
	DrawMaterialQuad("SmoothWall-Bricks1", 580, 340, 590, 340, 610, 360, 610, 370, 1);
	// Nach der grossen Treppe nach rechts kommt die grosse treppe nach links + decke
	DrawMaterialQuad("SmoothWall-Bricks3", 620, 310, 620, 300, 660, 340, 650, 340, 1);
	DrawMaterialQuad("SmoothWall-Bricks2", 660, 300, 670, 300, 690, 320, 690, 330, 1);
	
	/* Mitte */
	
	/* Oben */
	// Kammer über Thronsaal: Aufstieg rechts
	DrawMaterialQuad("SmoothWall-Bricks1", 770, 430, 820, 380, 820, 390, 790, 440, 1);
	// Ausschneiden
	DrawMaterialQuad("BackWall-Bricks2", 770, 420, 780, 400, 820, 440, 790, 440, 1);
	
	/* Rechts */
	// Treppen
	DrawMaterialQuad("SmoothWall-Bricks1", 840, 620, 840, 610, 890, 660, 880, 660, 1);
	DrawMaterialQuad("SmoothWall-Bricks1", 910, 580, 910, 570, 940, 600, 930, 600, 1);
	// Bodenschräge rechts aussen
	DrawMaterialQuad("SmoothWall-Bricks2", 1010, 650, 1020, 640, 1020, 650, 1010, 650, 1);
	// untendran
	DrawMaterialQuad("SmoothWall-Bricks1", 1030, 660, 1030, 660, 1030, 650, 1040, 650, 1);
	
	/* Oben */
	// Kleiner Gang in den Turm: erste Bodenschräge von links
	DrawMaterialQuad("Wall-Bricks1", 880, 360, 900, 340, 900, 350, 890, 360, 1);
	// darüber
	DrawMaterialQuad("Wall-Bricks1", 880, 340, 880, 330, 890, 320, 900, 320, 1);
	// zweite Schräge
	DrawMaterialQuad("Wall-Bricks1", 910, 350, 910, 350, 910, 340, 920, 350, 1);
	// darüber
	DrawMaterialQuad("Wall-Bricks1", 910, 320, 910, 320, 920, 320, 920, 330, 1);
	
	/* Oben mittig */
	// Hinab zum Turmaufgang
	DrawMaterialQuad("Wall-Bricks1", 570, 310, 570, 310, 580, 300, 580, 310, 1);

	/* Linker Turm der Burg */
	// Treppen
	DrawMaterialQuad("SmoothWall-Bricks1", 520, 270, 520, 260, 550, 290, 540, 290, 1);
	// Zinne rechts aussen beim Garten
	DrawMaterialQuad("SmoothWall-Bricks1", 680, 250, 680, 250, 680, 240, 690, 240, 1);
	// Zinnen oben links und rechts
	DrawMaterialQuad("SmoothWall-Bricks1", 450, 160, 460, 160, 470, 170, 470, 180, 1);
	DrawMaterialQuad("SmoothWall-Bricks1", 570, 170, 570, 170, 570, 160, 580, 160, 1);

	/* Rechter Turm der Burg */
	// Treppen
	DrawMaterialQuad("Wall-Bricks1", 920, 460, 920, 460, 930, 450, 930, 460, 1);
	DrawMaterialQuad("Wall-Bricks1", 1010, 390, 1010, 390, 1020, 380, 1020, 390, 1);
	// Tunnelschacht
	DrawMaterialQuad("BackWall-Bricks2", 961, 360, 961, 250, 984, 250, 984, 360, 1);
	// Dach
	DrawMaterialQuad("Wall-Bricks1", 920, 50, 970, 0, 970, 10, 930, 50, 1);
	DrawMaterialQuad("SmoothWall-Bricks1", 1020, 10, 1020, 0, 1090, 70, 1080, 70, 1);
	// Zinnen
	DrawMaterialQuad("SmoothWall-Bricks1", 1040, 350, 1040, 340, 1050, 330, 1060, 330, 1);
	// oben
	DrawMaterialQuad("SmoothWall-Bricks1", 920, 120, 930, 120, 950, 140, 950, 150, 1);
	DrawMaterialQuad("SmoothWall-Bricks1", 1040, 150, 1040, 140, 1060, 120, 1070, 120, 1);
	
	/* Höhle */
	// Unter wasser
	DrawMaterialQuad("SmoothWall-Bricks1", 670, 900, 690, 880, 690, 890, 680, 900, 1);
	// Neben cave
	DrawMaterialQuad("SmoothWall-Bricks1", 880, 930, 910, 900, 910, 910, 890, 930, 1);
	// Fahrstuhlschacht
	DrawMaterialQuad("BackWall-Bricks2", 920, 820, 943, 820, 943, 870, 920, 870, 1);
	// Neben fahrstuhl
	DrawMaterialQuad("SmoothWall-Bricks1", 870, 810, 870, 800, 890, 820, 880, 820, 1);
	// Ober fahrstuhl
	DrawMaterialQuad("SmoothWall-Bricks1", 920, 780, 920, 780, 930, 770, 930, 780, 1);
        //Rechter Fahrstuhl
        DrawMaterialQuad("BackWall-Bricks2", 1184, 680, 1206, 680, 1206, 820, 1184, 820);
	// Grosse schräge rechts von flintwerfer
	DrawMaterialQuad("Wall-Bricks1", 640, 750, 660, 750, 710, 800, 690, 800, 1);
	return 1;
}

global func Objects()
{
	// Der König
	var clonk = PlaceAnimal(KING);
	clonk -> SetPosition(870, 280);
	clonk -> SetColor(Random(12));
	PrepareShop(clonk, [FLNT,2, SFLN,2, TFLN,2, STFN,1, ARPD,1]);

	// Gelehrter
	clonk = PlaceAnimal(SCLK);
	clonk -> SetPosition(176, 600);
	clonk -> SetColor(Random(12));
	PrepareShop(clonk, [PMAN,3, PHEA,1, SCRL,7, BOOK,3]);

	// Ritter
	clonk = PlaceAnimal(KNIG);
	clonk -> SetPosition(660, 660);
	CreateContents(SHIE, clonk) -> Activate(clonk);
	clonk -> SetColor(Random(12));
	PrepareShop(clonk, [SPER,1, AXE1,1, SWOR,1, SHIE,1, SCMT,1, SHI2,1, MUSK,1, BLTP,2, SBLP,1, PBLP,1, CRBW,1, BOTP,1, NBTP,1, SBTP,1, BOW1,1, ARWP,2, FARP,1, XARP,1]);

	// Flintwerfer füllen und aktivieren
	var flt = FindObject2(Find_ID(_FLT), Find_AtPoint(600, 955));
	flt -> CreateContents(FLNT,, 20);
	flt -> CreateContents(SFLN,, 10);
	flt -> CreateContents(EFLN,, 5);
	flt -> CreateContents(TFLN,, 10);
	flt -> CreateContents(STFN,, 5);
	flt -> SetPower(10, 10);
	flt -> SwitchOn();
	
	// Turmgeschütz aktivieren
	var cannon = CreateObject(CTW5);
	FindObject(RFCH) -> ConnectCannon(cannon);
	cannon -> SetR(40);

	// Eine königliches Buch
	FindObject2(Find_ID(BOOK), Find_AtPoint(885, 279)) -> SetSpells();
	
	// Ofen frisches Holz nachlegen
	FindObject2(Find_ID(STOV), Find_AtPoint(750, 510)) -> CreateContents(WOOD,, 3);

	// Kisten füllen
	for (var chest in FindObjects(Find_ID(CHST)))
		AddEffect("RefillChest", chest, 100, 35*15, chest);

	// Manche Dinge können nicht kaputtgehen
	for (var obj in FindObjects(Find_Or(Find_ID(CHST), Find_ID(PPW1), Find_ID(PPT1), Find_ID(PRFC), Find_ID(PPT2), Find_ID(PPTL), Find_ID(PPW3), Find_ID(CPTE), Find_ID(ELEV), Find_ID(ELEC))))
		AddEffect("IntInvulnerable", obj, 500);
		
	// Zelt ist komisch
	var tent = FindObject2(Find_ID(TENT));
	tent -> SetObjectLayer(tent);

	// Dekoration platzieren
	CreateObject(_DCO,, 1, -1);
	return 1;
}

global func PrepareShop(object pClonk, array aWares)
{
	// Dem Händler kann man nix antun
	pClonk -> SetObjectLayer(pClonk);
	pClonk -> SetCategory(C4D_StaticBack);
	AddEffect("IntInvulnerable", pClonk, 500,, pClonk);
	// Shop erzeugen
	var shop = CreateObject(STRE);
	shop -> SetMenuClonk(pClonk);
	shop -> SetShopItems(aWares);
	return 1;
}

global func SetShopItems(array aItems, object pShop)
{
	if (!pShop && this) pShop = this;
	var order = [];
	for (var i; i < GetLength(aItems); i+=2) {
		pShop -> AddItems(aItems[i], aItems[i+1]);
		order[GetLength(order)] = aItems[i];
	}
	// Angebot sortieren
	pShop -> SetOrder(order);
	return 1;
}

global func CreateChestContent(object pChest)
{
	var nr = ObjectNumber(pChest);
	// Spezialitems
	var obj;
	if (nr == 119) { // Es sollte immer ein Tarnzauber bereitliegen
		obj = FindObject2(Find_ID(SCRL), Find_Container(pChest));
		if (!obj || LocalN("idSpell", obj) != CMFG) {
			obj = CreateContents(SCRL, pChest);
			obj  -> SetSpell(CMFG);
			return 1;
		}
	}
	// Sonst eher zufällig
	var ID = RndChestID(pChest);
	obj = CreateContents(ID, pChest);
	// Schriftrollen und Zauberbücher mit Zaubern belegen
	if (ID == SCRL || ID == BOOK) obj -> SetSpells();
	return 1;
}

global func RndChestID(object pChest)
{//GOLD, ORE1, ROCK, CRYS, PFIS, METL
//BRMR, TSWD
	// Spezialkisten
	var IDs, nr = ObjectNumber(pChest);
	if (nr == 128) 	// Neben der Burgbäckerei
		IDs = [[FLNT, AXE1], [TFLN, FBMP, AXE1, CLUB, SPER, DOGH], [FLOU, WDWB, COAL, PWIP, PHEA], [ARWP, BOTP, BLTP, STFN, SFLN]];
	else if (nr == 120) // Hier legen die Gelehrten und Weisen ihre magischen Sachen ab
		IDs = [[SCRL, PMAN], [BOOK, SCRL, PHEA, PFIR, FLNT], [BOOK, PWIP, PSTO, PMON, TFLN], [LFAM, ARWP, BOTP, BLTP, STFN, SFLN], [SCKZ]];
	else if (nr == 127) // Kiste in rechts unten in der Kristallöhle
		IDs = [[CRYS, FLNT, SCRL], [HLGN, SCRL, BOOK, SFLN, TFLN, STFN, PHEA], [BHLG, BOOK, PIMM, SPHR, LFAM], [BRMR, TSWD], [SCKZ]];
	else if (nr == 119) // Geheimgang in der Burg
		IDs = [[SCRL, PMAN, PHEA, FLNT, SFLN], [SCRL, BOOK, STFN, SBTP, XARP], [ARPD, PWIP, PFIR, PMON, FARP, PBLP], [LFAM, ARMR, TSWD], [BRMR]];
	// default
	else IDs = [[FLNT, SFLN, TFLN, ARWP], [STFN, FARP, PFIR, PHEA, PMAN, PSTO, SCRL], [BOTP, BLTP, SBLP, XARP, KNFP, SPER, PMON, PWIP, BOOK], [FBMP, ARPD, NBTP, PBLP, SCMT, SHI2, BOW1, MUSK, AXE1, _BMR], [SBTP, CRBW, HOOK, ARMR, SHIE, SWOR, CLUB]];	
	
        //Unbenötigtes entfernen
        for (var array in IDs)
          CheckItems(array);
        
        // Seltener als selten :D
	if (!Random(32))
		return IDs[4][Random(GetLength(IDs[4]))];
	// Selten
	if (!Random(12))
		return IDs[3][Random(GetLength(IDs[3]))];
	// Normal
	if (!Random(6))
		return IDs[2][Random(GetLength(IDs[2]))];
	// Oft
	if (!Random(3))
		return IDs[1][Random(GetLength(IDs[1]))];
	// default
	return IDs[0][Random(GetLength(IDs[0]))];
}

global func SetSpells(object pScroll)
{
	if (!pScroll && this) pScroll = this;
	// Bei der Schriftrolle können den Zauber einfach so draufdrucken
	if (GetID(pScroll) == SCRL)
		pScroll -> SetSpell(RndSpellID(pScroll));
	// Auf dem Buch hingegen wollen wir die Zauber schön nebeneinander und möglichst zentral ablegen
	else if (GetID(pScroll) == BOOK) {
		for (var i=RandomX(2, 5), n, b; i; i--) {
			if (n == 0) b = 2;
			if (n == 1) b = 1;
			if (n == 2) b = 3;
			if (n == 3) b = 0;
			if (n == 4) b = 4;
			pScroll -> SetSpell(RndSpellID(pScroll), b);
			++n;
		}
	}
	else return;
	// Fertig belegt
	return 1;
}

global func RndSpellID(object pScroll)
{
	var IDs = [[ABLA, MGBW, WOLI, CMFG, EXTG, MBRG, MFFW], [ELX1, MDBT, MSSH, MFRB, MGRP, MARK, FRFS, MGHL, MLGT], [ELX2, MBLS, MFWL, GGHG, MINV], [MBOT, FHSK, MFWV]];
	// Sehr selten
	if (!Random(15))
		return IDs[3][Random(GetLength(IDs[3]))];
	// Selten
	if (!Random(10))
		return IDs[2][Random(GetLength(IDs[2]))];
	// Normal
	if (!Random(5))
		return IDs[1][Random(GetLength(IDs[1]))];
	// default
	return IDs[0][Random(GetLength(IDs[0]))];
}

/* Kiste nachfüllen */

// RefillChest

global func FxRefillChestStart(object pTarget, int iNr, int iTemp)
{
	if (iTemp) return;
	// ~ 10 Inhalte
	for (var i=RandomX(8, 12); i; i--) EffectCall(pTarget, iNr, "Refill");
	return 1;
}

global func FxRefillChestTimer(object pTarget, int iNr)
{
	if (Random(3)) return; // Damit nicht alle Kisten gleichzeitig nachfüllen
	// Weniger als 10 Inhalte -> Nachfüllen
	if (ContentsCount() < 8) {
		AddEffect("PtRefillChest", pTarget, 75, 1, pTarget);
		EffectCall(pTarget, iNr, "Refill");
	}
	return 1;
}

global func FxRefillChestRefill(object pTarget, int iNr)
{
	// + einen zufälligen Inhalt
	CreateChestContent(pTarget);
	return 1;
}


// PtRefillChest

global func FxPtRefillChestStart(object pTarget, int iNr, int iTemp)
{
	if (iTemp) return;
	// Kiste aufmachen
	pTarget -> Open();
	if (GetAction(pTarget) != "Opening") return -1; // Muss wohl abgeschlossen sein
	return 1;
}

global func FxPtRefillChestTimer(object pTarget, int iNr, int iTime)
{
	// Partikel
	var s;
	for (var i=RandomX(1, 3); i; i--) {
		s = 20+Random(41);
		CreateParticle("PSpark", RandomX(-5, 5),,, -RandomX(5, 10), s, RGBa(255, RandomX(100, 255), s*4, 128), pTarget);
	}
	if (iTime%2) CreateParticle("NoGravSpark",,,,, 5*60, RGBa(200, RandomX(200, 255), 255, 240), pTarget, 1);
	// Kiste schliesst automatisch :/
	if (GetAction(pTarget) != "Opening") return -1;
	return 1;
}

// IntInvulnerable

global func FxIntInvulnerableDamage(object pTarget, int iNr, int iDmg, int iCause)
{
	// Unverwundbar
	return 0;
}
