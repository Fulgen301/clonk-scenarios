/*-- Blackout kill tracking and colour modulation by team --*/

#appendto MBOT
#strict 2

public func Activate(object pCaster, object pRealcaster) {
	// Effekte!
	Sound("Magic*", 0, this(), 70);
	var iRange=100;
	var iDuration = 37;
	var iAng, iX, iY, iRng;
	// Kombo: Stein verlängert Dauer
	var pComboObj;
	if (pComboObj = FindContents(ROCK, pCaster))
	{
		iDuration *= 2;
		RemoveObject(pComboObj);
	}
	// Kombo: Fisch und Kohle vergrößert Radius
	pComboObj = FindContents(FISH, pCaster);
	if (!pComboObj) pComboObj = FindContents(DFSH, pCaster);
	if (!pComboObj) pComboObj = FindContents(COAL, pCaster);
	if (pComboObj)
	{
		if (GetAlive(pComboObj))
			iRange *= 3;
		else
			iRange *= 2;
		RemoveObject(pComboObj);
	}
	for(var i=iRange/2; i>0; --i)
	{
		iAng=Random(360);
		iRng=Random(iRange/2);
		iX=Sin(iAng, iRng);
		iY=Cos(iAng, iRng);
		CreateParticle("Feather", iX, iY, RandomX(-5,5), -3, 50+Random(25), GetPlrColorDw(GetOwner(pCaster)));
	}
	var pClonk,pVictim;
	if(!(pClonk=pRealcaster)) pClonk=pCaster;
	// alle Clonks im näheren Umkreis prüfen
	while(pVictim=FindObject(0,-iRange/2,-iRange/2,iRange,iRange,OCF_CrewMember,0,0,NoContainer(),pVictim))
		// die Opfer sind feindliche Clonks oder alle Clonks außer dem Zauberer selbst wenn NoTeamMagic aktiviert ist
		if((Hostile(GetOwner(pVictim),GetOwner(pClonk)) || ObjectCount(NTMG)) && pClonk!=pVictim)
		{
			// wirkt länger bei heruntergekämpften Clonks
			AddEffect("SleepNSpell",pVictim,123,25,0,GetID(),iDuration*((115-GetEnergy(pVictim)*100000/GetPhysical("Energy",0, pVictim))/5));
			SetKiller(GetController(pClonk), pVictim);
		}
		return(1);
}
