/* Luftklaue */

#strict 2

func Activate(pCaster,pRealcaster) {
  var pClonk;
  if(pRealcaster) pClonk=pRealcaster;
  else pClonk=pCaster;

 // Nicht im Geb�ude zaubern
  if(Contained(pClonk))
  {
    Sound("Error");
    PlayerMessage(GetOwner(pClonk), "$must_be_in_free$", pClonk);
    RemoveObject();
    return 0;
  }

  // Zielen wenn m�glich
   if (pClonk->~DoSpellAim(this(), pCaster)) return 1;
  
  // Sonst einfach ungezielt loslassen
  var angle=-90;
  if(GetDir(pClonk) == DIR_Right) angle=90;
  ActivateAngle(pClonk,angle);
  
  return;
}

// Aktivierung nach Zielen (iAngle: -90=links; 0=oben; +90=rechts)
public func ActivateAngle(object pCaller, int iAngle)
{
  // Klaue erzeugen und losschicken
  CreateObject(AFTF,AbsX(GetX(pCaller))+Cos(iAngle-90,10),AbsY(GetY(pCaller))+Sin(iAngle-90,10)+19,GetOwner(pCaller))->Activate(pCaller,iAngle);

  // Objekt l�schen
	RemoveObject();
	return 1;
}

public func IsBattlemageSpell() { return true; }

/* Zaubercombo */

public func GetSpellStaff(object pMage) { return SMAR; }
public func GetSpellStaffCombo(pMage) { return ("44"); } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
