/*-- Gegenstand herbeizaubern --*/

#strict 2

public func Activate(pCaster,pRealcaster)
{
  //Blacklist. Hierhin kommen Noobs, Kiddies, Spammer, Leaver, Errorwerfer...
  var aBlacklist = [CL5P,CRYS,SNWB,FBRL,GSHL,MSHL,RSHL,BSHL,SSHL,VSHL,ARRW,FARW,XARW];

  //Ein gut bestücktes ID-Array
  var aDefs = [];
  for(var i=0; GetDefinition(i); i++)
  {
    var idDef = GetDefinition(i);
    if(GetDefCoreVal("Collectible","DefCore",idDef))
      if(!PartOf(idDef,aBlacklist))
        aDefs[GetLength(aDefs)] = idDef;
  }

  //Doch nicht gut bestückt? Du bist doof :(
  if(!GetLength(aDefs))
  {
    Sound("CommandFailure1");
    RemoveObject(this);
    Message("$Nothing$",pCaster);
    return false;
  }

  Sound("Magic1",false,pCaster);

  var iCount = 1;
  var pCombo = FindContents(LNKT,pCaster);
  if(pCombo)
  {
    iCount = 3 + Random(2);
    RemoveObject(pCombo);
  }

  var szMessage = "", szImage = "";  
  for(var i=0; i<iCount; i++)
  {
    idDef = aDefs[Random(GetLength(aDefs))];
    //DOOF -> Log("%i",idDef);
    var pObj = CreateObject(idDef,0,0,GetOwner(this));
    SetPosition(GetX(this),GetY(this)+ 8,pObj);
    if(GetCategory(pCaster) & C4D_Structure)
      Enter(pCaster,pObj);

    if(!i)
    {
      szMessage = Format("%s",GetName(0,idDef));
      szImage = Format("{{%v}}",idDef);
    }
    else
    {
      szMessage = Format("%s|%s",szMessage,GetName(0,idDef));
      szImage = Format("%s {{%v}}",szImage,idDef);
    }

    pObj ->~ CreatedByMagic(pCaster);
  }
  Message(Format("<c 99ffffff>%s</c>|%s",szImage,szMessage),pCaster);
  RemoveObject(this);
  return true;
}

public func GetSpellClass(object pMage) { return(EART); }
public func GetSpellCombo(pMage) { return ("422"); } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
