/* Rückschlag */

#strict 2

public func Activate(pCaster)
{
  //Objekte durchsuchen und das schnellste rausfiltern.
  var pObj;
  var aObjects = FindObjects(Find_OCF(OCF_HitSpeed2),Find_Distance(200),Find_NoContainer());
  
  //Sky Mayhem sucht das Flitzobjekt.
  for(var i=0; i<GetLength(aObjects); i++)
  {
    if(!pObj)
    {
      pObj = aObjects[i];
      continue;
    }
    //Das Objekt ist schneller? Altes rauswerfen
    if(Distance(GetXDir(aObjects[i]),GetYDir(aObjects[i])) > Distance(GetXDir(pObj),GetYDir(pObj)))
      pObj = aObjects[i];
  }

  if(!pObj)
  {
    Sound("Error",false,pCaster);
    Message("$TxtSlow$",pCaster);
    RemoveObject(this);
    return false;
  }
  
  Sound("Magic*");
  for(var i = 0; i < 5; i++)
  {
    CreateParticle("SSpark", 0,0, 1000, RGBa(25,50,250,150));
    CreateParticle("SSpark", Random(6)-3, Random(8)-4, Random(4)-2, Random(4)-2, Random(20)+180, RGB(Random(50),Random(115),Random(255)));
    
    if(pCaster != pObj)
      DrawParticleLine("SSpark", 0, 0, AbsX(GetX(pObj)), AbsY(GetY(pObj)), 20, 100, RGBa(25,25,255,100), RGBa(Random(50),Random(115),Random(255),100),5);
  }

  SetXDir(GetXDir(pObj,GetXDir(pObj)),pObj,1-GetXDir(pObj));
  SetYDir(GetYDir(pObj,GetYDir(pObj)),pObj,1-GetYDir(pObj));

  if(pObj ->~ IsClonk())
    GameCallEx("OnClonkRepercussion",pObj,GetOwner(pObj));

  //Erstmal festhalten, ob das Objekt vor dem Energieabzug gelebt hat.
  var fAlive = GetAlive(pObj);
  DoEnergy(-5,pObj);

  if(!GetAlive(pObj)) SetController(GetOwner(),pObj);

  //Komboobjekte
  var pCombo = FindContents(ASHS,pCaster);
  if(pCombo)
  {
    RemoveObject(pCombo);
    //Allgemeinere Formel ohne if. dir*2-1
    SetXDir(GetXDir(pObj)+(GetDir(pCaster)*100-50),pObj);

    CreateParticle("SSpark", 0,0, 1000, RGBa(25,50,250,150));
    CreateParticle("SSpark", RandomX(-3,3), RandomX(-4,4), RandomX(-2,2), RandomX(-2,2), RandomX(200,180), RGB(Random(50),Random(115),Random(255)));
  }

  pCombo = FindContents(METL,pCaster);
  if(pCombo)
  {
    var pCloud = CreateObject(WRZI,AbsX(GetX(pObj)),AbsY(GetY(pObj)),GetOwner(this));
    if(pCloud)
    {
      pCloud ->~ Start(GetXDir(pObj),GetYDir(pObj));
      RemoveObject(pCombo);
    }
  }

  //Effekt-Calls beim zurückschlagen
  var iEffect = GetEffect("Flight",pObj);
  if(iEffect)
    EffectCall(pObj,iEffect,"Reflection",this,false);

  if(fAlive && (GetID(pObj) == FLYF || GetID(pObj) == DFLH))
  {
    //Fliegender Fisch allgemein.
    var pMedal = FindObject(WF_M);
    if(pMedal)
      Reward(pMedal,GetOwner(this));

    //Ist er durch den Zauber kaputtgegangen? Extra-Medaille!
    if(fAlive && GetID(pObj) == DFLH)
    {
      pMedal = FindObject(FC_M);
      if(pMedal)
        Reward(pMedal,GetOwner(this));
    }
  }

  RemoveObject(this);
  return true;
}

public func GetSpellClass(object pMage) { return(AIR1); }
public func GetSpellCombo(pMage) { return ("555"); } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
