/*-- Kommandos an nahe Einheiten --*/

#strict
#appendto CLNK

func IsCursor()
{
  return GetCursor(GetOwner())==this();
}

func HasFollowers()
{
  if(!IsCursor()) return 0;
  return FindObject2(Find_Owner(GetOwner()),Find_Func("HasMode",TWRATK_Cmd_Follow,this));
}

func HasDefenders()
{
  if(!IsCursor()) return 0;
  return FindObject2(Find_Distance(150),Find_Owner(GetOwner()),Find_Func("HasMode",TWRATK_Cmd_Defend));
}

func ContextFollow() {
  [Befehl zum Folgen geben( nahe Einheiten)|Image=COSY:3|Condition=IsCursor]
  for(var pObj in FindObjects(Find_Distance(130),Find_Owner(GetOwner()),Find_Func("IsBulkArmyPart")))
    pObj->SetAIMode(TWRATK_Cmd_Follow,this);
  var dummy=CreateObject(TIM1,0,0,GetOwner());
  dummy->SetVisibility(VIS_Owner() | VIS_Allies());
  for(var iAngle=0; iAngle<360; iAngle+=10)
    CreateParticle("NoGravSpark",Sin(iAngle,130),-Cos(iAngle,130),Sin(iAngle,-20),-Cos(iAngle,-20),50,RGB(153,0,255),dummy);
  for(iAngle=0; iAngle<360; iAngle+=15)
    CreateParticle("PSpark",Sin(iAngle,130),-Cos(iAngle,130),0,0,50,RGB(153,0,255),dummy);
  PlayerMessage(GetOwner(),"<c 9900ff>Mir folgen nun %d Einheiten</c>",this,ObjectCount2(Find_Owner(GetOwner()),Find_Func("HasMode",TWRATK_Cmd_Follow)));
  dummy->Schedule("RemoveObject()",350);
  return(1);
}

func ContextDefense() {
  [Befehl zum Stellung halten geben( nahe Einheiten)|Image=COSY:1|Condition=IsCursor]
  for(var pObj in FindObjects(Find_Distance(130),Find_Owner(GetOwner()),Find_Func("IsBulkArmyPart")))
    pObj->SetAIMode(TWRATK_Cmd_Defend);
  var dummy=CreateObject(TIM1,0,0,GetOwner());
  dummy->SetVisibility(VIS_Owner() | VIS_Allies());
  for(var iAngle=0; iAngle<360; iAngle+=10)
    CreateParticle("NoGravSpark",Sin(iAngle,130),-Cos(iAngle,130),0,5,50,RGB(0,0,255),dummy);
  for(var iAngle=0; iAngle<360; iAngle+=15)
    CreateParticle("PSpark",Sin(iAngle,130),-Cos(iAngle,130),0,0,50,RGB(255,255,255),dummy);
  dummy->Schedule("RemoveObject()",350);
  return(1);
}

func ContextGetOutFight() {
  [Aktionen abbrechen|Image=COSY:4|Condition=HasFollowers]
  for(var pObj in FindObjects(Find_Owner(GetOwner()),Find_Func("IsBulkArmyPart"),Find_Func("HasMode",TWRATK_Cmd_Follow)))
  {
    SetCommand(pObj,"MoveTo",this());
    pObj->SetAction("Walk");
    
    if(GetAction(pObj)S="Fight")
      if(Random(2))
        AddCommand(pObj,"Jump");
  }
  return(1);
}

/*func ContextBrake() {
  [Pause einlegen|Image=BRED|Condition=HasFollowers]
  ContextGetOutFight();
  for(var pObj in FindObjects(Find_Owner(GetOwner()),Find_Func("IsBulkArmyPart"),Find_Func("HasMode",TWRATK_Cmd_Follow)))
    if(GetAction(pObj)ne"Pray")pObj->SetAction("Pray");
  return(1);
}*/

func ContextRemoveFollow() {
  [Truppen "loslassen"|Image=COSY:2|Condition=HasFollowers]
  var dummy=CreateObject(TIM1,0,0,GetOwner());
  dummy->SetVisibility(VIS_Owner() | VIS_Allies());
  for(var iAngle=0; iAngle<360; iAngle+=10)
    CreateParticle("NoGravSpark",0,0,Sin(iAngle,40),-Cos(iAngle,40),50,RGB(153,0,255),dummy);
  for(iAngle=0; iAngle<360; iAngle+=15)
    CreateParticle("PSpark",Sin(iAngle,130),-Cos(iAngle,130),0,0,50,RGB(153,0,255),dummy);
  dummy->Schedule("RemoveObject()",350);
  for(var pObj in FindObjects(Find_Owner(GetOwner()),Find_Func("IsBulkArmyPart"),Find_Func("HasMode",TWRATK_Cmd_Follow,this)))
    pObj->SetAIMode(0);
  return(1);
}

func ContextRemoveDefense() {
  [Truppen sollen die Stellung verlassen|Image=COSY|Condition=HasDefenders]
  var dummy=CreateObject(TIM1,0,0,GetOwner());
  dummy->SetVisibility(VIS_Owner() | VIS_Allies());
  for(var iAngle=0; iAngle<360; iAngle+=10)
    CreateParticle("NoGravSpark",Sin(iAngle,130),-Cos(iAngle,130),0,-Cos(iAngle,30),50,RGB(0,0,255),dummy);
  for(var iAngle=0; iAngle<360; iAngle+=15)
    CreateParticle("PSpark",Sin(iAngle,130),-Cos(iAngle,130),Sin(iAngle,30),0,50,RGB(255,255,255),dummy);
  dummy->Schedule("RemoveObject()",350);
  for(var pObj in FindObjects(Find_Distance(150),Find_Owner(GetOwner()),Find_Func("IsBulkArmyPart"),Find_Func("HasMode",TWRATK_Cmd_Defend)))
    pObj->SetAIMode(0);
  return(1);
}

func ContextTroopHelp() {
  [TruppenInfo|Image=CXIN|Condition=HasFollowers]
  var pArmie=FindObjects(Find_Owner(GetOwner()),Find_Func("HasMode",TWRATK_Cmd_Follow));
  var szString=Format("%d Soldaten",GetLength(pArmie));
  var iMaxH,iCurH;
  var aDefs,aCount;
  for(var obj in pArmie)
  {
    iMaxH+=GetPhysical("Energy", 0, obj)/1000;
    iCurH+=GetEnergy(obj);
  }
  szString=Format("%s|<c %x>%d/%d</c> Energie",szString,RGB(255-iCurH*200/iMaxH,iCurH*255/iMaxH,0),iCurH,iMaxH);
  MessageWindow(szString, GetOwner());
  return(1);
}
