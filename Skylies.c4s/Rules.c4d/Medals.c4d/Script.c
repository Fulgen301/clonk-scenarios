/*--Medaillenabfrage --*/

//Original aus Stippelhöhlen

#strict 2

static const szMedalEntry = "SKYM_Medals";
static const iLastEntry = 1;

func Initialize()
{
  //Alle Medaillen erstellen
  var i, idDef;
  while(idDef = GetDefinition(i++))
    if (idDef->~IsMedal())
      CreateObject(idDef, 0, 0, NO_OWNER);
  AddMsgBoardCmd("resetmedals","ResetMedals(%player%)");
  return true;
}

func Activate(int iPlr)
{
  var pCursor = GetCursor(iPlr);
  if (!pCursor)
    return false;

  CreateMenu(GetID(), pCursor, 0, 0, "$Medals$:", 0, C4MN_Style_Context);
  
  //Medaillen aufzählen
  for(var i=0; i <= iLastEntry; i++)
  {
    var iData = GetPlrExtraData(iPlr, Format("%s%d",szMedalEntry,i));
    if (!iData) continue;

    for(var medal in FindObjects(Find_Medal()))
      if(iData & (1 << medal->~MedalIndex()))
        if(i == medal->~MedalEntry())
          AddMenuItem(GetName(medal), "MedalInfo", GetID(medal), pCursor, 0, pCursor, GetDesc(medal));
  }
  AddMenuItem("<c 88ffffff>$PostMedal$</c>", "MedalPost", TIM1, pCursor, 0, pCursor);
  return true;
}

func MedalInfo(id idMedal, object pClonk)
{
  var szCaption = GetName(0,idMedal);
  var szText = GetDesc(0,idMedal);
  if(!idMedal || !pClonk || !CreateMenu(idMedal,pClonk,pClonk,0,GetName(0,idMedal),0,C4MN_Style_Info))
    return false;
  AddMenuItem(szCaption,"",idMedal,pClonk,0,0,szText);
  return true;
}

func MedalPost(id idMedal, object pClonk)
{
  var aPosts = $Posts$;
  var iMedalCount = MedalCount(GetOwner(pClonk));
  var szText = Format(aPosts[BoundBy(iMedalCount/5,0,4)],GetTaggedPlayerName(GetOwner(pClonk)));

  Log("<System> %s: %s",szText, ListMedals(GetOwner(pClonk)));
  return true;
}

/* Externe Funkitonen */

global func Reward(object pMedal, int iPlr)
{
  if (!GetPlayerName(iPlr) || !pMedal || !pMedal->~IsMedal())
    return false;
    
  //Hat schon?
  var szEntry = Format("%s%d",szMedalEntry, pMedal->~MedalEntry());  
  if (GetPlrExtraData(iPlr, szEntry) & (1 << pMedal->~MedalIndex()))
  {
    //Bescheid sagen, dass der Spieler sich für die Medaille qualifiziert hat.
    GameCallEx("OnMedalQualification",pMedal,iPlr);
    return false;
  }
  
  //Bescheid sagen, dass der Spieler die Medaille bekommen hat.
  GameCallEx("OnMedalReward",pMedal,iPlr);
  pMedal ->~ OnReward(iPlr);
  SetPlrExtraData(iPlr, szEntry, GetPlrExtraData(iPlr, szEntry) | (1 << pMedal->~MedalIndex()));
  //Springende Nachricht über dem Clonk
  ExtraMessage(GetName(pMedal),GetID(pMedal),RGB(250,190,8),GetCursor(iPlr));
  //Ehemals ExtraLog(), Externes Log oben in der Ecke
  ShowMessage(Format("{{%i}} $Reward$",GetID(pMedal),GetTaggedPlayerName(iPlr),GetName(pMedal)));
  Sound("GetMedal",false,GetCursor(iPlr),100,iPlr);
  return true;
}

global func ResetMedals(int iPlr)
{
  for(var i=0; i <= iLastEntry; i++)
    SetPlrExtraData(iPlr,Format("%s%d",szMedalEntry,i),0);
  Sound("Ding",true,0,100,iPlr);
  ShowMessage(Format("{{MD0D:1}} $ResetMessage$",GetTaggedPlayerName(iPlr)));
  return true;
}

global func SetArray(array &aArray, int iLength)
{
  if(!aArray || GetType(aArray) != C4V_Array)
  {
    if(iLength) aArray = CreateArray(iLength);
    else aArray = [];
  }
  return aArray;
}

global func Find_Medal() {return Find_Func("IsMedal");}

global func ListMedals(int iPlr)
{
  var szResult = "";

  var aMedals = [];
  for(var j=0, idObj; idObj = GetDefinition(j); j++)
    if(idObj ->~ IsMedal())
      aMedals[GetLength(aMedals)] = idObj;

  for(var i=0; i <= iLastEntry; i++)
  {
    var iData = GetPlrExtraData(iPlr,Format("%s%d",szMedalEntry,i));

    for(var j=0; j<GetLength(aMedals); j++)
      if(iData & (1 << aMedals[j]->~MedalIndex()))
        if(i == aMedals[j]->~MedalEntry())
          szResult = Format("%s {{%i}}",szResult,aMedals[j]);
  }
  
  if(!GetLength(szResult)) szResult = "<i>$Nothing$!</i>";
  return szResult;
}

global func MedalCount(int iPlr)
{
  var iCount = 0;
  
  for(var i=0; i <= iLastEntry; i++)
  {    
    var iData = GetPlrExtraData(iPlr,Format("%s%d",szMedalEntry,i));
    for(var j=0; j < 31; j++)
      if(iData & (1<<j))
        iCount++;
  }  
  return iCount;
}

//Experimentell, ich brauche es zum debuggen. Ingame löst das ein Chaos aus :P
global func RewardAll(int iPlr)
{
  for(var medal in FindObjects(Find_Medal()))
    Reward(medal,iPlr);
  return true;
}
