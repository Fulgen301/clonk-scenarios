/*--- Bausatz ---*/

#strict 2

#appendto CNKT

public func Activate(pClonk)
{ 
  [$TxtCreateconstructionsi$]
  // Clonk anhalten
  SetComDir(COMD_Stop, pClonk);
  var j;
  // Menü erzeugen und mit Bauplänen des Spielers füllen
  CreateMenu(CXCN, pClonk, this, C4MN_Extra_Value, "$TxtNoconstructionplansa$");
  var idType; var i = 1;
  while(idType = GetDefinition(i++, C4D_Structure))
    if(idType->~CanBeBuild(pClonk))
      if(idType->~IsLevel1())
      {
        AddMenuItem("$TxtConstructions$", "CreateConstructionSite", idType, pClonk, 0, pClonk);
        j++;
      }
  SetMenuSize(j,4,pClonk);
  var idType2;
  i=1;
  while(idType = GetDefinition(i++, C4D_Structure))
    if(idType->~CanBeBuild(pClonk))
      if(idType->~IsLevel1())
      {
        if(idType2=idType->~UpgradeTo())
          AddMenuItem("$TxtConstructions$", "CreateConstructionSite", idType2, pClonk, 0, pClonk);
        else
          AddMenuItem("", "", NONE, pClonk);
      }
      
  i=1;
  while(idType = GetDefinition(i++, C4D_Structure))
    if(idType->~CanBeBuild(pClonk))
      if(idType->~IsLevel1())
      {
        if(idType->~UpgradeTo())
        {
          if((idType2=idType->~UpgradeTo()->~UpgradeTo())&&((!idType2->~NeedToBeResearched())||GetPlrKnowledge(GetOwner(pClonk),idType2)))
            AddMenuItem("$TxtConstructions$", "CreateConstructionSite", idType2, pClonk, 0, pClonk);
          else
            AddMenuItem("", "", NONE, pClonk);
        }
        else
          AddMenuItem("", "", NONE, pClonk);
      }
      
  i=1; var k;
  while(idType = GetDefinition(i++, C4D_Structure))
    if(idType->~CanBeBuild(pClonk))
      if(idType->~IsSpecialBuilding())
      {
        AddMenuItem("$TxtConstructions$", "CreateConstructionSite", idType, pClonk, 0, pClonk);
        k++;
      }
      
  while(k++<j)
    AddMenuItem("", "", NONE, pClonk);

  /*i=1;
  while(idType = GetDefinition(i++, C4D_Structure()))
    if(idType->~CanBeBuild(pClonk))
      if(idType->~IsLevel1())
      {
        if(idType->~UpgradeTo())
        {
          if(idType->~UpgradeTo()->~UpgradeTo())
          {
            if(idType2=idType->~UpgradeTo()->~UpgradeTo()->~UpgradeTo())
              AddMenuItem("$TxtConstructions$", "CreateConstructionSite", idType2, pClonk, 0, pClonk);
            else
              AddMenuItem("", "", NONE, pClonk);
          }
          else
            AddMenuItem("", "", NONE, pClonk);
        }
        else
          AddMenuItem("", "", NONE, pClonk);
      }*/
      
  var upTo,def;
  for(var obj in FindObjects(Find_Or(Find_AtPoint(),Find_AtPoint(0,-10)),Find_Category(C4D_Structure),Find_Or(Find_Allied(GetOwner(pClonk)),Find_Not(Find_OCF(OCF_Fullcon))),Find_Not(Find_ID(ELEC))))
  { 
    AddMenuItem("%s abreißen", "DestructBld", GetID(obj), pClonk, 1, obj,0,128);
    if(GetCon(obj)>=100)
      if(upTo=obj->~UpgradeTo())
      {
	if(upTo->~NeedToBeResearched())
	  if(!GetPlrKnowledge(GetOwner(pClonk),upTo))
	    continue;
        def = TransformObject(GetID(obj),upTo);
        AddMenuItem(Format("%s zu %s upgraden",GetName(obj),GetName(0,upTo)), "UpgradeBld", upTo, pClonk, 1, obj, 0, 4+128, def,obj->~UpgradeCost());
        RemoveObject(def);
      }
  }
  return(1);
}

public func UpgradeBld(idDef,pBuild,bRight,iValue)
{
  var iPlr=GetOwner(Contained());
  if(GetWealth(iPlr) < iValue)
  {
    PlayerMessage(iPlr,"$NotEnoughMoney$",this);
    return(1);
  }
  pBuild->ChangeDef(pBuild->~UpgradeTo());
  pBuild->DoCon(-50);
  pBuild->Schedule("DoCon(1)",3,50);
  pBuild->~OnUpgrade();
  for(var i = 1; i <= 20; i++)
  {
    if(Stuck(pBuild))
      SetPosition(GetX(pBuild),GetY(pBuild)-1,pBuild);
    else
      break;
  }
  DoWealth(iPlr,-iValue);
}

public func DestructBld(idDef,pBuild)
{
  pBuild->Schedule("DoCon(-1)",3,200);
}

func TransformObject(idDef,idDefTo)
{
  var def = CreateObject(TIM1, 0,0, -1);
  
  SetGraphics("",def,idDefTo,2,GFXOV_MODE_Picture);
  SetObjDrawTransform(1000, 0, 5000, 0, 1000, 0, def, 2);
  
  SetGraphics("",def,FXL1,1,GFXOV_MODE_Picture);
  SetObjDrawTransform(1000, 0, 0, 0, 1000, 0, def, 1);
  SetClrModulation(RGBa(255,32,32,80),def,1);
  
  return def;
}

protected func CreateConstructionSite(idType, pClonk)
{
  // Nur wenn der Clonk steht und sich im Freien befindet
  if (GetAction(Contained()) != "Walk") return(0);
  if (Contained(Contained())) return(0);
  
  // Besitzer setzen f�r CreateConstruction
  SetOwner(GetOwner(Contained()));
  
  // Pruefen, ob das Gebaeude hier gebaut werden kann
  if (idType->~RejectConstruction(0, 10, Contained()) ) return(0);
  
  if(g_iMode!=TWRATK_MODE_Survival)
    if(GetPlayerTeam(GetOwner(Contained()))==1)
    {
      if(GetX(Contained())>LandscapeWidth()*3/5)
        return PlayerMessage(GetOwner(),"<c ff0000>Hier darfst du nichts bauen.</c>",this);
    }
    else
    {
      if(GetX(Contained())<LandscapeWidth()*2/5)
        return PlayerMessage(GetOwner(),"<c ff0000>Hier darfst du nichts bauen.</c>",this);
    }
      
  if(GetWealth(GetOwner(pClonk)) < GetValue(0,idType))
  {
    PlayerMessage(GetOwner(pClonk),"$NotEnoughMoney$",this); 
    return(1);
  }
  // Baustelle erschaffen
  var pSite;
  if (!(pSite = CreateConstruction(idType, 0, 10, GetOwner(), 1, 1,1))) return(0);
  pSite->SetPlrViewRange(200);
  //pSite->Schedule("DoCon(1)",1,30);
  DoWealth(GetOwner(pClonk),-GetValue(0,idType));
  // Meldung
  Message("$TxtConstructions$", Contained(), GetName(pSite));
  // Sound
  Sound("Cash",1,0,0,GetOwner()+1);
  SetCommand(Contained(),"Build",pSite);
  return(1);
}

public func CreateConstr(pObj,idDef)
{
  return CreateConstructionSite(idDef, pObj);
}

/* Produkteigenschaften */

public func IsAnvilProduct() { return(1); }
