/*-- Granitschlag --*/

#strict 2

public func Activate(pCaster)
{
	var xSpeed;
	var ySpeed;
	
	if(ObjectCount(RMGS))
	{
		xSpeed=GetXDir(pCaster,1)+10-20*(GetDir(pCaster)==DIR_Left);
		ySpeed=GetYDir(pCaster,1)-5;
	}
	else
	{
		xSpeed=10-20*(GetDir(pCaster)==DIR_Left);
		ySpeed=-5;
	}
	Exit(CreateContents(GRBL,pCaster),+5-10*GetDir(pCaster),-5,50,xSpeed,ySpeed,50);
	
	RemoveObject();
	CreateParticle("PSpark", GetX(pCaster)-GetX(), GetY(pCaster)-GetY(), 0, 0, 250);
	CreateParticle("PSpark", GetX(pCaster)-GetX()-10, GetY(pCaster)-GetY()+5, 0, 0, 150);
	CreateParticle("PSpark", GetX(pCaster)-GetX()+10, GetY(pCaster)-GetY()+5, 0, 0, 150);
	Sound("Blast3");
	return(1);
}

public func GetSpellClass(object pMage) { return(EART); }
public func GetSpellCombo(pMage) { return ("232"); } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
