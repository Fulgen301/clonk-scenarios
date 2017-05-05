/*-- Adjust sun location --*/

#strict

#appendto SONE

private func BerechneSonneY() 
{
  	var ZeitObjekt = FindObject(TIME);
	if(!ZeitObjekt)
		SonneY = 30;
		
	else return _inherited();
}

protected func TuWasBraves()
{
	// Bei vorhandenem Lenseflare (mit integrierter Sonne) kann dieses Objekt gelöscht werden
	if(ObjectCount(LENS))
	{
		RemoveObject(this());
		return();
	}
	// Hat es seinen Besitzer verloren? :(
	if((!GetPlayerName(GetOwner())) || GetOwner()==-1)
	{
		RemoveObject(this()); 
		return();
	}
	// Sonnenposition anpassen
	BerechneSonne();
	SetPosition(SonneX,SonneY);
}