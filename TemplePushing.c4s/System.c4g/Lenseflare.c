/* Adjust Lenseflare effect */

#strict

#appendto LENS

protected func TuWasBraves()
{
	// Hat es seinen Besitzer verloren? :(
	if((!GetPlayerName(GetOwner())) || GetOwner()==-1)
	{
		for(var i=0; i<MIJON(); ++i)
			RemoveObject(Local(i));
		RemoveObject(this()); 
		return();
	}
	// Sonnenposition anpassen
	BerechneSonne();
	SetPosition(SonneX,SonneY);
	// unskalierten Vektor ermitteln
	var VektorX=GibVektorX(GetOwner());
	var VektorY=GibVektorY(GetOwner());
	var VektorDist=GibVektorDist(GetOwner());
	// Die Modulation ist für alle Flares gleich
	var FarbModulation = RGBa(GibFarbMod(),GibFarbMod(),GibFarbMod(),GibAlphaMod(VektorDist));
	// Genauso auch die Abstandsangabe
	var Abstaende = 1000-BoundBy((3000-VektorDist*10)/3,0,1000);  // Promilleangabe 0 = nahe, 1000 = weit weg; 300 Pixel sind dabei "weit weg"
	var AbstaendeAbsolut = (50*Abstaende)/10; // Wieviele 1/100 Pixel zwischen den einzelnen Lenseflares sind
	// Ist unsere liebe Sonne überhaupt sichtbar (also Tag + unverdeckt)
	var SonneSichtbar = IsDay() && (!GBackSemiSolid(0,0));
	// Tagsüber die Sonne einblenden
	if(IsDay())
	{
		SetVisibility (VIS_Owner());
	}
	else
	{
		SetVisibility (VIS_None());
	}
	// Alle Lenseflares durchgehen
	for(var i=0; i<MIJON(); ++i)
	{
		if(SonneSichtbar)
		{
			// Tags sichtbar
			SetVisibility (VIS_Owner(), Local(i));
			SetClrModulation(FarbModulation,Local(i));
			var LensDist = (i*AbstaendeAbsolut)/100;
			SetPosition(GibLensPosX(LensDist,VektorX,VektorDist), GibLensPosY(LensDist,VektorY,VektorDist),Local(i));
		}
		else
			// Nachts unsichtbar ODER bei verdeckter Sonne
			SetVisibility (VIS_None(), Local(i));
	}
	return; // Gamma-Aenderung deaktiviert fuer Tempelschubsen
	// Sofern der Spieler alleine ist
	if(GetPlayerCount()==1)
		if(IsDay())
		{
			var Gelbstich = BoundBy((500-VektorDist)/5,0,100); // Prozentangabe 0 = weit weg, 100 = nahe; 500 Pixel sind dabei "weit weg"
			SetGamma (RGB(000+(30*Gelbstich)/100,000+(30*Gelbstich)/100,000),
					  RGB(128+(60*Gelbstich)/100,128+(60*Gelbstich)/100,128), 
					  RGB(255,255,255), GammaRampe_Lenseflare());
		}
}