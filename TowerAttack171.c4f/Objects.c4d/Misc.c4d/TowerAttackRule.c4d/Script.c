/*-- TowerAttack --*/

#strict 2

static g_aArmyCount,g_aArmyAllowed,g_aArmyMode,g_aLiveAmount,g_aStrength,g_fSinglePlayer,g_fStarted;

static g_Armys;

static g_Deads;

static g_iMode,g_iDiffi,g_iGameSpeed,g_filledTeams;

static g_iGamePhase;

static g_iLevel,g_iSurvivalPlayer,g_iToStart;

static const TWRATK_ArmySize=35;
static const TWRATK_Live=15;

static const TWRATK_MODE_VS=0;
static const TWRATK_MODE_Survival=1;
static const TWRATK_MODE_VSTime=2;

static const TWRATK_DIFF_VeryEasy=-1;
static const TWRATK_DIFF_Easy=0;
static const TWRATK_DIFF_Normal=1;
static const TWRATK_DIFF_Hard=2;
static const TWRATK_DIFF_Extreme=3;
static const TWRATK_DIFF_Nightmare=5;

static const TWRATK_SPEED_Slow=0;
static const TWRATK_SPEED_Normal=1;
static const TWRATK_SPEED_Fast=2;
static const TWRATK_SPEED_ExtraFast=5;

static const SURV_BSP_ExtraFast=1;
static const SURV_BSP_FireResist=2;
static const SURV_BSP_MegaHeros=3;
static const SURV_BSP_ToMany=4;
static const SURV_BSP_Stableness=5;
static const SURV_BSP_ExtremeDestruction=6;
static const SURV_BSP_Max=6;

func Activate(iPlr)
{
  if(!GetLeague())
    if(!g_fStarted)
    {
      //return SetMode(TWRATK_MODE_VS,iPlr);
      if(iPlr==GetPlayerByIndex(0,C4PT_User))
      {
	RemoveAll(MELE);
        CreateMenu(GetID(),GetCursor(iPlr),0,C4MN_Extra_Info,"Spielmodus",0,C4MN_Style_Normal,0,TWAK);
        AddMenuItem("VS-Modus",Format("SetMode(%d,%d)",TWRATK_MODE_VS       ,iPlr)  ,MELE,GetCursor(iPlr),0,0,"Gegen Spieler");
        if(g_filledTeams<3)
          AddMenuItem("Survival",Format("SetMode(%d,%d)",TWRATK_MODE_Survival ,iPlr)  ,MNTK,GetCursor(iPlr),0,0,"Unendliche Wellen von Gegnern");
	AddMenuItem("Zeitkampf",Format("SetMode(%d,%d)",TWRATK_MODE_VSTime,iPlr)    ,MLGT,GetCursor(iPlr),0,0,"Gegen Spieler :: Die Aufbauzeit ist zeitlich eingeschränkt");
        SetMenuSize(3,1,GetCursor(iPlr));
        return 1;
      }
    }
  return MessageWindow(GetDesc(), iPlr);
}

func SetMode(iMode,iPlr)
{
  g_iMode=iMode;
  if(iMode==TWRATK_MODE_VS)
  {
    Log("VS-Modus");
    RemoveAll(MELE);
    CreateObject(MELE,0,0,-1);
    CreateMenu(GetID(),GetCursor(iPlr),0,C4MN_Extra_Info,"Spielgeschwindigkeit",0,C4MN_Style_Normal,0,TWAK);
    AddMenuItem("Langes Spiel",Format("(g_iGameSpeed=%d)+Log(\"Langes Spiel\")",TWRATK_SPEED_Slow),SNKE,GetCursor(iPlr),0,0,"Viele Leben und kein Zeitfaktor bei der Truppenstärke");
    AddMenuItem("Normales Spiel",Format("(g_iGameSpeed=%d)+Log(\"Normales Spiel\")",TWRATK_SPEED_Normal),CLNK,GetCursor(iPlr),0,0,"Normale Leben und ein kleiner Zeitfaktor bei der Truppenstärke");
    AddMenuItem("Schnelles Spiel",Format("(g_iGameSpeed=%d)+Log(\"Schnelles Spiel\")",TWRATK_SPEED_Fast),ZAP1,GetCursor(iPlr),0,0,"Wenige Leben und ein merkbarer Zeitfaktor bei der Truppenstärke");
    AddMenuItem("Extraschnelles Spiel",Format("(g_iGameSpeed=%d)+Log(\"Extraschnelles Spiel\")",TWRATK_SPEED_ExtraFast),BIRD,GetCursor(iPlr),0,0,"Sehr wenige Leben und ein hoher Zeitfaktor bei der Truppenstärke");
    SetMenuSize(4,1,GetCursor(iPlr));
    SelectMenuItem(1,GetCursor(iPlr));
  }
  else if(iMode==TWRATK_MODE_Survival)
  {
    Log("Survival-Modus");
    CreateMenu(GetID(),GetCursor(iPlr),0,C4MN_Extra_Info,"Schwierigkeitsgrad",0,C4MN_Style_Normal,0,TWAK);
    AddMenuItem("Sehr leicht",Format("(g_iDiffi=%d)+Log(\"Sehr leicht\")",TWRATK_DIFF_VeryEasy),TWAK,GetCursor(iPlr),0,0,"Viele Leben und wenige schwache Truppen",2,1);
    AddMenuItem("Leicht",Format("(g_iDiffi=%d)+Log(\"Leicht\")",TWRATK_DIFF_Easy),WIPF,GetCursor(iPlr),0,0,"Normale Leben und wenige Truppen");
    AddMenuItem("Normal",Format("(g_iDiffi=%d)+Log(\"Normal\")",TWRATK_DIFF_Normal),TWAK,GetCursor(iPlr),0,0,"Normale Leben und viele Truppen",2,2);
    AddMenuItem("Schwer",Format("(g_iDiffi=%d)+Log(\"Schwer\")",TWRATK_DIFF_Hard),TWAK,GetCursor(iPlr),0,0,"Wenige Leben und viele Truppen",2,3);
    AddMenuItem("Extreme",Format("(g_iDiffi=%d)+Log(\"Extreme\")",TWRATK_DIFF_Extreme),TWAK,GetCursor(iPlr),0,0,"Sehr wenige Leben und viele starke Truppen",2,4);
    AddMenuItem("Albtraum",Format("(g_iDiffi=%d)+Log(\"Albtraum\")",TWRATK_DIFF_Nightmare),TWAK,GetCursor(iPlr),0,0,"Zu wenig Leben und zu viele starke Truppen",2,5);
    SetMenuSize(6,1,GetCursor(iPlr));
    SelectMenuItem(2,GetCursor(iPlr));
  }
  else if(TWRATK_MODE_VSTime)
  {
    Log("Zeitkampf-Modus");
  }
}

protected func Initialize()
{
  g_aArmyMode=[0,TWRATK_Cmd_Attack,TWRATK_Cmd_Attack];
  g_aArmyCount=[0,0,0];
  g_aArmyAllowed=[0,TWRATK_ArmySize,TWRATK_ArmySize];
  g_aLiveAmount=[0,TWRATK_Live,TWRATK_Live];
  g_aStrength=[0,0,0];
  g_Armys=[[]];
  
  if(!IsNetwork())
  {
    AddMsgBoardCmd("AddBloodAI","CreateScriptPlayer(\"%sAI\",RGB(200,107,107),1)");
    AddMsgBoardCmd("AddBoneAI","CreateScriptPlayer(\"%sAI\",RGB(107,200,107),2)");
    AddMsgBoardCmd("AddAI","CreateScriptPlayer(\"%sAI\")");
  }
  
  CreateObject(CLK_,0,0,-1)->Set(70,RGB(55,55,55),RGB(255,255,255),"TowerAttack");
  
  /* Highscores verteilen */
  var iHigh,sHigh;
  iHigh=0; sHigh=GetPlayerName(GetPlayerByIndex(0,C4PT_User));
  for(var i = 0; i < GetPlayerCount(C4PT_User); i++)
  {
    if(GetPlrExtraData(GetPlayerByIndex(i,C4PT_User),"TA_High")>iHigh)
    {
      iHigh=GetPlrExtraData(GetPlayerByIndex(i,C4PT_User),"TA_High");
      sHigh=GetPlrExtraData(GetPlayerByIndex(i,C4PT_User),"TA_HighS");
    }
  }
  if(iHigh)
    if(!g_fSinglePlayer)
      for(i = 0; i < GetPlayerCount(C4PT_User); i++)
      {
        iHigh=SetPlrExtraData(GetPlayerByIndex(i,C4PT_User),"TA_High",iHigh);
        sHigh=SetPlrExtraData(GetPlayerByIndex(i,C4PT_User),"TA_HighS",sHigh);
      }

}

public func TimeUp()
{
  g_fStarted=true;
  for(var obj in FindObjects(Find_OCF(OCF_CrewMember)))
    if(GetMenu(obj)==TWAK)
      CloseMenu(obj);
  if(g_iMode==TWRATK_MODE_VS)
  {
    g_aLiveAmount=[0,(TWRATK_Live*2)/(g_iGameSpeed+1),(TWRATK_Live*2)/(g_iGameSpeed+1)];
    AddEffect("GiveMeMoney",0,50,70,this);
    AddEffect("ArmyCreator",0,150,450,this);
    Log("<c ffff00>Die Vorbereitungszeit ist nun vorbei</c>");
  }
  else if(g_iMode==TWRATK_MODE_Survival)
  {
    g_aLiveAmount[g_filledTeams]=BoundBy(TWRATK_Live*2-g_iDiffi*5,5,TWRATK_Live*3);
    g_aLiveAmount[2-!(g_filledTeams-1)]=1;
    AddEffect("IntSurvivalMode",0,10,175,0,TWAK);
    CreateScriptPlayer("SurvivalAI",RGB(32,32,32),2-!(g_filledTeams-1),CSPF_NoScenarioInit|CSPF_NoEliminationCheck,TWAK);
    for(var i = 0; i < GetPlayerCount(C4PT_User); i++)
    {
      CreateArmy(GetPlayerByIndex(i),200);
      g_aArmyMode[GetPlayerByIndex(i)]=TWRATK_Cmd_Defend;
    }
  }
  else
  {
    if(g_iGamePhase==0)
    {
      g_fStarted=false;
      CreateObject(CLK_,0,0,-1)->Set(60*15,RGB(85,85,85),RGB(255,255,255),"TowerAttack");
      g_iGamePhase=1;
      Log("<c ffff00>15 Minuten Vorbereitungszeit!</c>");
      AddEffect("GiveMeMoney",0,50,10,this);
    }
    else if(g_iGamePhase==1)
    {
      RemoveEffect("GiveMeMoney");
      g_iGamePhase=2;
      Log("<c ffff00>Fight!</c>");
      AddEffect("ArmyCreator",0,150,250,this);
      RemoveAll(CNKT);
    }
  }
  CheckScoreboard();
}

public func FxIntSurvivalModeTimer()
{
  if(g_aArmyCount[2-!(g_filledTeams-1)]||g_iToStart>0)//FindObject2(Find_Func("IsAI"),Find_Eval("GetPlayerTeam(GetOwner())!=g_filledTeams"))
  {
    if(g_iToStart>0)
    {
      CreateArmy(g_iSurvivalPlayer-1,150+40*g_iLevel,RandomColor());
      g_iToStart-=150+40*g_iLevel;
    }
    return 0;
  }
  else
  {
    // Geld geben
    for(var i = 0; i < GetPlayerCount(C4PT_User); i++)
    {
      DoWealth(GetPlayerByIndex(i),150+g_iLevel*20);
      CreateArmy(GetPlayerByIndex(i),100);
    }
    g_iLevel++;
    g_aLiveAmount[2-!(g_filledTeams-1)]=g_iLevel;
    SetScoreboardData(2-!(g_filledTeams-1),ScoreboardCol(CPT2),Format("%d",g_aLiveAmount[2-!(g_filledTeams-1)]),g_aLiveAmount[2-!(g_filledTeams-1)]);
    g_aStrength[2-!(g_filledTeams-1)]+=g_iDiffi;
    //g_iLevelSpecial=0;
    /*if(g_iLevel%10==0)
    {
      g_iLevelSpecial=RandomX(1,SURV_BossSpecialMax);
    }
    else*/
      Log("<c ff0000>L</c><c ff3333>e</c><c ff8888>v</c><c ffbbbb>e</c><c ffffff>l</c> <c ff0000>%d</c>! +%d Gold",g_iLevel,150+g_iLevel*20);
    Sound("Ding");
    var iAmount=150+(50+15*g_iDiffi)*GetPlayerCount(C4PT_User)+(g_iLevel*(20+g_iDiffi*4)+5*g_iLevel*g_iLevel*(g_iDiffi+1+GetPlayerCount(C4PT_User)*2));
    g_aArmyAllowed[2-!(g_filledTeams-1)]=iAmount/15;
    g_iToStart=iAmount;
  }
}

global func CreateArmy(iPlr,iAmount,Clr)
{
  var idDef;
  var fNoBulk;
  var idDefs=[];
  var idDefs2=[CLNK,CLNK,ACLK,ACLK,_THF,_THF,_ZMB,_ZMB,SKLT,SKLT,_SKN,_SKN,KNIG,KNIG,KAND,KAND,JCLK,PRST,BGNT,BTRL,ASAS,PLDN,MCLK,SCLK,MAGE,MYST,_SSR,LICH,KING];
  var pClonk;
  idDefs[GetLength(idDefs)]=idDefs2[Random(GetLength(idDefs2))];
  while(Random(3)||GetLength(idDefs)<=3)
    idDefs[GetLength(idDefs)]=idDefs2[Random(GetLength(idDefs2))];
  while(iAmount>0)
  {
    idDef=idDefs[Random(GetLength(idDefs))];
    if(!idDef)
      return Log("CreateArmyError :: No Definitions! (%v)",idDefs);
    if(idDef->~IsMagiclonk())
      idDef=idDefs[Random(GetLength(idDefs))];
    if((!Random(3)&&Random(iAmount)>300))
      fNoBulk=true;
    iAmount-=GetValue(0,idDef)/2+(fNoBulk*GetValue(0,idDef));
    if(iAmount<0)
      break;
    pClonk=CreateObject(idDef,GameCall("GetCrapStartPosition",GetPlayerTeam(iPlr)),GameCall("GetCrapStartPosition",GetPlayerTeam(iPlr),1),iPlr);
    if(!pClonk) continue;
    if(Random(iAmount)>200)
    {
      pClonk->~SetDestroyerAI(fNoBulk);
      iAmount-=25;
    }
    else if((idDef->~IsKnight()||idDef->~IsKanderian())&&(Random(iAmount)>200)&&(!Random(5)))
    {
      pClonk->~SetBowAI(fNoBulk);
      iAmount-=25;
    }
    else if(idDef->~IsMagiclonk())
    {
      pClonk->~SetMagicanAI(fNoBulk);
      iAmount-=45;
    }
    else if(idDef->~IsPaladin())
    {
      pClonk->~SetPalaAI(fNoBulk);
      iAmount-=25;
    }
    else
      pClonk->~SetBulkAI(fNoBulk);
    // Call für M&M Crewmembers wegen Kirche
    pClonk->~ChangedTo();
    AddEffect("IntBulkArmyPart",pClonk,2);
    if(Clr)
      SetColorDw(Clr,pClonk);
    
    // Zusätzliche Effekte für höhere Stufen
    if(!Random(3))
    if(fNoBulk)
    {
      // Gral des Schmerzes
      if(Random(iAmount)>500)
      {
        AddEffect("PainGrail",pClonk,20,3,0,CPCH);
        iAmount-=25;
      }
      // Blutdornen
      if(Random(iAmount)>500)
      {
        AddEffect("BloodThorns",pClonk,20,3,0,CPCH);
        iAmount-=25;
      }
      // Kampffeuer
      if(Random(iAmount)>500)
      {
        AddEffect("FightF1re",pClonk,20,2,0,CPCH);
        iAmount-=25;
      }
      // Racheblitze
      if(Random(iAmount)>500)
      {
        AddEffect("RevengeLightning",pClonk,20,2,0,CPCH);
        iAmount-=25;
      }
    }
    // Segen
    if(!Random(3))
    if(Random(iAmount)>400)
    {
      AddEffect("HeavensBoon",pClonk,20,2,0,CPCH);
      iAmount-=10;
    }
  }
  return 1;
}

protected func InitializePlayer(int iPlr, int iX, int iY, object pBase, int iTeam)
{
  if(GetPlayerType(iPlr)==C4PT_User)
  {
    ScheduleCall(this,"OpenChooseMenu",1,1,iPlr);
    if(iPlr==GetPlayerByIndex()) ScriptGo(true);
  }
  else
  {
    var rand=Random(5);
    while(true)
    {
      if(!Random(ObjectCount2(Find_ID(MAGE),Find_Eval("GetHiRank(GetOwner())==this"))))
        if(!rand--){
          ScheduleCall(this,"ChooseMagic",1,1,iPlr);break;}

      if(!Random(ObjectCount2(Find_ID(PLDN),Find_Eval("GetHiRank(GetOwner())==this"))))
        if(!rand--){
          ScheduleCall(this,"ChooseKnight",1,1,iPlr);break;}

      if(!Random(ObjectCount2(Find_ID(LICH),Find_Eval("GetHiRank(GetOwner())==this"))))
        if(!rand--){
          ScheduleCall(this,"ChooseNecro",1,1,iPlr);break;}

      if(!Random(ObjectCount2(Find_ID(ASAS),Find_Eval("GetHiRank(GetOwner())==this"))))
        if(!rand--){
          ScheduleCall(this,"ChooseAssass",1,1,iPlr);break;}

      if(!Random(ObjectCount2(Find_ID(MYST),Find_Eval("GetHiRank(GetOwner())==this"))))
        if(!rand--){
          ScheduleCall(this,"ChooseKandis",1,1,iPlr);break;}

      rand=Random(5);
    }
    AddEffect("AIPlayer",0,1,35,0,0,iPlr);
  }
  // Scoreboard
  SetScoreboardData(iTeam,SBRD_Caption,GetTeamName(iTeam),55);
  SetScoreboardData(iTeam,ScoreboardCol(CPT2),Format("%d",g_aLiveAmount[iTeam]),g_aLiveAmount[iTeam]);
  CheckScoreboard();
  SortScoreboard(ScoreboardCol(CPT2),1);

  g_aArmyMode[iPlr]=TWRATK_Cmd_Attack;
  if(FrameCounter()<350)
    g_filledTeams=SetBit(g_filledTeams,iTeam,1);

  SetFoW(false,iPlr);
}

public func InitializeScriptPlayer(iPlr)
{
  g_aArmyMode[iPlr]=TWRATK_Cmd_Attack;
  return g_iSurvivalPlayer=iPlr+1;
}

global func CheckAIJoin()
{
  if(g_iMode!=TWRATK_MODE_Survival)
  if(GetPlayerCount()<2)
  {
    CreateObject(MELE,0,0,-1);
    g_fSinglePlayer=true;
    Log("Einzelspielermodus :: KI-Spielerbeitritt");
    if(GetPlayerTeam(GetPlayerByIndex())!=2)
    {
      CreateScriptPlayer("KI Nr.1",RGB(200,127,127),2);
      CreateScriptPlayer("KI Nr.2",RGB(187,127,127),2);
    }
    else
    {
      CreateScriptPlayer("KI Nr.1",RGB(127,200,127),1);
      CreateScriptPlayer("KI Nr.2",RGB(127,187,127),1);
    }
  }
}

protected func RemovePlayer(int iPlr)
{
  var iPlr=-1;
  for(var i = 0; i < GetPlayerCount(C4PT_User); i++)
  {
    if(GetPlayerTeam(iPlr)==GetPlayerTeam(GetPlayerByIndex(i,C4PT_User)))
      iPlr=GetPlayerByIndex(i,C4PT_User);
  }
  for(var pObj in FindObjects(Find_Owner(iPlr)))
  {
    if(iPlr>-1)
      SetOwner(iPlr,pObj);
    else
      RemoveObject(pObj);
  }
  Schedule("CheckScoreboard()",5);
}

public func OpenChooseMenu(iPlr)
{
  CreateMenu(CLNK,GetCursor(iPlr),0,0,"ERROR");
  AddMenuItem("Magie",Format("ChooseMagic(%d)",iPlr),MAGE,GetCursor(iPlr));
  AddMenuItem("Kirche",Format("ChooseKnight(%d)",iPlr),PLDN,GetCursor(iPlr));
  AddMenuItem("Nekromantie",Format("ChooseNecro(%d)",iPlr),LICH,GetCursor(iPlr));
  AddMenuItem("Dunkelheit",Format("ChooseAssass(%d)",iPlr),ASAS,GetCursor(iPlr));
  AddMenuItem("Kanderia",Format("ChooseKandis(%d)",iPlr),MYST,GetCursor(iPlr));
  //AddMenuItem("Zufall",Format("ChooseRandom(%d)",iPlr),SY88,GetCursor(iPlr));
}

protected func HeroStats(pClonk)
{
  SetPhysical("Energy", GetPhysical("Energy", PHYS_Permanent, pClonk)*2, PHYS_Temporary, pClonk);
  SetPhysical("Fight", GetPhysical("Fight", PHYS_Permanent, pClonk)*2, PHYS_Temporary, pClonk);
  DoEnergy(100,pClonk);
  while(DoMagicEnergy(1,pClonk));
  CreateContents(CNKT,pClonk);
  // Call für M&M Crewmembers wegen Kirche
  pClonk->~ChangedTo();
  // Relaunch-Effekt
  if(!GetEffect("Relaunch",pClonk))
    AddEffect("Relaunch",pClonk,100,0,pClonk);
  // Menü öffnen wenn erster Spieler
  if(GetOwner(pClonk)==GetPlayerByIndex(0,C4PT_User))
    this->Activate(GetOwner(pClonk));
}

protected func ChooseMagic(iPlr)
{
  var pCursor=GetCursor(iPlr);
  if(!pCursor)  pCursor=GetCrew(iPlr);
  if(!pCursor){ pCursor=CreateObject(CLNK,0,0,iPlr); MakeCrewMember(pCursor,iPlr);}
  var pMage = CreateObject(MAGE,0,0,iPlr);
  MakeCrewMember(pMage,iPlr);
  pCursor->~Redefine(MAGE);
  GrabObjectInfo(pMage,pCursor);
  RemoveObject(pMage);
  SetCursor(iPlr,pCursor);
  pCursor->CreateContents(SCKZ);
  g_Armys[iPlr]=[[CLNK,4],[JCLK,3],[BGNT,3]];
  if(GetPlayerType(iPlr)==C4PT_Script)
    GetCursor(iPlr)->SetAI();
  CheckScoreboard();
  MMSetPlayerChurch(iPlr,-1);
  HeroStats(pCursor);
}

protected func ChooseKnight(iPlr)
{
  var pCursor=GetCursor(iPlr);
  var pMage = CreateObject(PLDN,0,0,iPlr);
  MakeCrewMember(pMage,iPlr);
  GetCursor(iPlr)->~Redefine(PLDN);
  GrabObjectInfo(pMage,GetCursor(iPlr));
  RemoveObject(pMage);
  SetCursor(iPlr,pCursor);
  //GetCursor(iPlr)->CreateContents(TSWD);
  GetCursor(iPlr)->CreateContents(SWOR);
  GetCursor(iPlr)->CreateContents(MUSK);
  GetCursor(iPlr)->CreateContents(BLTP);
  GetCursor(iPlr)->CreateContents(SHIE)->Activate(GetCursor(iPlr));
  g_Armys[iPlr]=[[CLNK,4],[KNIG,2],[PRST,3]];
  if(GetPlayerType(iPlr)==C4PT_Script)
  {
    GetCursor(iPlr)->SetAI();
    MMSetPlayerChurch(iPlr,RandomX(1,2));
  }
  CheckScoreboard();
  HeroStats(pCursor);
}

protected func ChooseNecro(iPlr)
{
  var pCursor=GetCursor(iPlr);
  var pMage = CreateObject(LICH,0,0,iPlr);
  MakeCrewMember(pMage,iPlr);
  GetCursor(iPlr)->~Redefine(LICH);
  GrabObjectInfo(pMage,GetCursor(iPlr));
  RemoveObject(pMage);
  SetCursor(iPlr,pCursor);
  GetCursor(iPlr)->CreateContents(SMOD);
  g_Armys[iPlr]=[[_ZMB,4],[SKLT,3],[_SKN,2]];
  if(GetPlayerType(iPlr)==C4PT_Script)
    GetCursor(iPlr)->SetAI();
  CheckScoreboard();
  MMSetPlayerChurch(iPlr,-1);
  HeroStats(pCursor);
}

protected func ChooseAssass(iPlr)
{
  var pCursor=GetCursor(iPlr);
  var pMage = CreateObject(ASAS,0,0,iPlr);
  MakeCrewMember(pMage,iPlr);
  GetCursor(iPlr)->~Redefine(ASAS);
  GrabObjectInfo(pMage,GetCursor(iPlr));
  RemoveObject(pMage);
  SetCursor(iPlr,pCursor);
  GetCursor(iPlr)->CreateContents(CRBW);
  GetCursor(iPlr)->CreateContents(BOTP);
  GetCursor(iPlr)->CreateContents(NBTP);
  GetCursor(iPlr)->CreateContents(KNFP);
  g_Armys[iPlr]=[[_ZMB,2],[_THF,6],[BTRL,1]];
  if(GetPlayerType(iPlr)==C4PT_Script)
    GetCursor(iPlr)->SetAI();
  CheckScoreboard();
  MMSetPlayerChurch(iPlr,-1);
  HeroStats(pCursor);
}

protected func ChooseKandis(iPlr)
{
  var pCursor=GetCursor(iPlr);
  var pMage = CreateObject(MYST,0,0,iPlr);
  MakeCrewMember(pMage,iPlr);
  GetCursor(iPlr)->~Redefine(MYST);
  GrabObjectInfo(pMage,GetCursor(iPlr));
  RemoveObject(pMage);
  SetCursor(iPlr,pCursor);
  GetCursor(iPlr)->CreateContents([ROCK,FMEG,ZAPN,FBMP][Random(5)]);
  GetCursor(iPlr)->CreateContents([SHEL,STFN,TFLN,GUNP][Random(5)]);
  g_Armys[iPlr]=[[KAND,3],[CLNK,4],[BGNT,1]];
  CheckScoreboard();
  MMSetPlayerChurch(iPlr,-1);
  HeroStats(pCursor);
}

protected func MenuQueryCancel()
{
  return(1);
}

func OnClonkDeath(pClonk)
{
  g_Deads++;
  var iKilledBy=GetKiller(pClonk);
  if(GetOwner(pClonk)<0)
    return 0;
  if(iKilledBy==GetOwner(pClonk))
    return 0;
  var iReward=BoundBy(10-(GetWealth(iKilledBy)/200),2,5);
  if(g_iMode==TWRATK_MODE_Survival)
  {
    iReward=0;
    if(!Random(5))
      iReward=1;
  }
  if(iReward<1) return 0;
  if(iKilledBy>-1)
    if(iKilledBy!=GetOwner(pClonk))
      if(iReward>0)
        DoWealth(iKilledBy,iReward);
  // Den Verbündeten auch etwas geben
  for(var i = 0; i < GetPlayerCount(); i++)
    if(!Hostile(GetPlayerByIndex(i),iKilledBy))
    {
      iReward=5-(GetWealth(GetPlayerByIndex(i))/100);
      if(iReward>0)
        DoWealth(GetPlayerByIndex(i),iReward);
    }
  return 1;
}

func OnGoalsFulfilled()
{
  var iHigh,sHigh;
  iHigh=g_Deads; sHigh=GetPlayerName(GetPlayerByIndex(0,C4PT_User)); var fNewRecord=true;
  for(var i = 0; i < GetPlayerCount(C4PT_User); i++)
  {
    if(GetPlrExtraData(GetPlayerByIndex(i,C4PT_User),"TA_High")>iHigh)
    {
      iHigh=GetPlrExtraData(GetPlayerByIndex(i,C4PT_User),"TA_High");
      sHigh=GetPlrExtraData(GetPlayerByIndex(i,C4PT_User),"TA_HighS");
      fNewRecord=false;
    }
    if(fNewRecord)
      if(i>0)
        sHigh=Format("%s&%s",sHigh,GetPlayerName(GetPlayerByIndex(i,C4PT_User)));
  }
  Log("Insgesamt <c ffff00>%d</c> Tote!!!11einself (Rekord: %d(von %s))",g_Deads,iHigh,sHigh);
  if(!g_fSinglePlayer)
    for(i = 0; i < GetPlayerCount(C4PT_User); i++)
    {
      iHigh=SetPlrExtraData(GetPlayerByIndex(i,C4PT_User),"TA_High",iHigh);
      sHigh=SetPlrExtraData(GetPlayerByIndex(i,C4PT_User),"TA_HighS",sHigh);
    }
}

global func TWRATKChangeLP(iTeam,iAmount)
{
  if(iTeam<1)
    return 0;
  if(iTeam>2)
    return 0;
  if(g_iMode==TWRATK_MODE_Survival)
    if(iTeam==2-!(g_filledTeams-1))
      return 0;
  var i;
  // Kleiner Effekt
  if(iAmount<0)
  {
    for(i = 0; i < GetPlayerCount(); i++)
      if(GetPlayerTeam(GetPlayerByIndex(i))==iTeam)
      {
        Sound("CommandFailure1",true,0,100,GetPlayerByIndex(i)+1);
        Sound("DeEnergize",true,0,100,GetPlayerByIndex(i)+1);
      }
  }
  var temp=g_aLiveAmount[iTeam];
  g_aLiveAmount[iTeam]=BoundBy(g_aLiveAmount[iTeam]+iAmount,0,200);
  // Letztes Leben verbraucht :: Alle Spieler des Teams löschen
  if(g_aLiveAmount[iTeam]==0)
    for(i = 0; i < GetPlayerCount(); i++)
      if(GetPlayerTeam(GetPlayerByIndex(i))==iTeam)
        EliminatePlayer(GetPlayerByIndex(i));
  SetScoreboardData(iTeam,ScoreboardCol(CPT2),Format("%d",g_aLiveAmount[iTeam]),g_aLiveAmount[iTeam]);
  SortScoreboard(ScoreboardCol(CPT2),1);
  return g_aLiveAmount[iTeam]!=temp;
}

global func CheckScoreboard()
{
  var iPlr,iTeam;
  // Titel
  SetScoreboardData(SBRD_Caption, SBRD_Caption,        "TowerAttack",             SBRD_Caption);
  SetScoreboardData(SBRD_Caption, ScoreboardCol(CPT2), "<c ff5555>{{MFFW}}</c>",  ScoreboardCol(CPT2));
  SetScoreboardData(SBRD_Caption, ScoreboardCol(HERO), "{{Portrait:ASAS::1}}{{Portrait:PLDN::1}}{{Portrait:MAGE::1}}",ScoreboardCol(HERO));
  SetScoreboardData(SBRD_Caption, ScoreboardCol(COUN), "{{CLNK}}",                ScoreboardCol(COUN));
  // Leben aktualiesieren
  for(var i = 0; i < GetTeamCount(); i++)
    TWRATKChangeLP(GetTeamByIndex(i),0);
  // Helden erfassen
  var aHeroes=CreateArray(GetTeamCount());
  for(i = 0; i < GetPlayerCount(); i++)
  {
    iPlr=GetPlayerByIndex(i);
    iTeam=GetPlayerTeam(iPlr);
    if(!aHeroes[iTeam])
        aHeroes[iTeam]="";
    aHeroes[iTeam]=Format("%s{{%i}}",aHeroes[iTeam],GetID(GetHiRank(iPlr)));
  }
  // Scorebord setzen
  for(i = 0; i < GetTeamCount(); i++)
  {
    iTeam=GetTeamByIndex(i);
    SetScoreboardData(iTeam,ScoreboardCol(HERO),aHeroes[iTeam],1);
    SetScoreboardData(iTeam,ScoreboardCol(COUN),Format("%d/%d",g_aArmyCount[iTeam],g_aArmyAllowed[iTeam]),1);
  }
}

/* ----- Effekt: Relaunch ----- */

global func FxRelaunchStop(object Target, int EffectNumber, int Reason, bool Temp)
{
  if(Temp)
    return(1);

  if(Reason==4)// Nur Tod. Kann schon mal vorkommen. Vielleicht währe Wiederbeleben jetzt angebracht.
  {
    CastParticles("FSpark",80,10,GetX(Target),GetY(Target),50,70,RGB(127,127,127),RGB(127*2,127*2,127*2));
    var iEffect,i;
    // Von Effektzahl abwärts zählen, da Effekte entfernt werden
    i = GetEffectCount(0,Target);
      while (i--)
        if (iEffect = GetEffect("**",Target,i,0,200))
          RemoveEffect(0,Target,iEffect);
    if(Contained(Target))
      Exit(Target);

    // Positionieren
    GameCall("SetRelaunchPos",Target);

    // Clonk wiederbeleben
    SetAlive(1,Target);
    MakeCrewMember(Target, GetOwner(Target));
    ObjectSetAction(Target,"Walk",0,0,1);
    SetComDir(COMD_Stop,Target);
    SetXDir(0,Target);
    SetYDir(0,Target);

    // Energie geben
    DoEnergy(GetPhysical("Energy",0,Target)/1000-GetEnergy(Target),Target);
    DoMagicEnergy(25,Target);
    Extinguish(Target);

    // Particelz!!!...
    CastParticles("Blast",60,25,GetX(Target),GetY(Target),50,70,GetColorDw(Target),GetColorDw(Target));
    /*CastParticles("NoGravSpark",60,20,GetX(Target),GetY(Target),50,70,HSL(Random(255),255,127),HSL(Random(255),255,127));
    CastParticles("PSpark",50,30,GetX(Target),GetY(Target),50,70,HSL(Random(255),255,127),HSL(Random(255),255,127));
    CastParticles("NoGravSpark",60,10,GetX(Target),GetY(Target),50,70,HSL(Random(255),255,127),HSL(Random(255),255,127));
    CastParticles("PSpark",50,20,GetX(Target),GetY(Target),50,70,HSL(Random(255),255,127),HSL(Random(255),255,127));
    CastParticles("NoGravSpark",60,5,GetX(Target),GetY(Target),50,70,HSL(Random(255),255,127),HSL(Random(255),255,127));
    CastParticles("PSpark",50,10,GetX(Target),GetY(Target),50,70,HSL(Random(255),255,127),HSL(Random(255),255,127));*/

    // Bestrafen...
    DoWealth(GetOwner(Target),-100);
    // ... und belohnen
    DoWealth(GetKiller(Target),50);

    return -1;
  }

  return 1;
}

// Armeen der Spieler erschaffen
global func FxArmyCreatorTimer()
{
  if(!g_fStarted)
    return 0;
  var plr,army,j,pClonk,ai;
  for(var i = 0; i < GetPlayerCount(); i++)
  {
    plr=GetPlayerByIndex(i);
    if(g_aArmyCount[GetPlayerTeam(plr)]>=g_aArmyAllowed[GetPlayerTeam(plr)])
      continue;
    if(GetLength(g_Armys[plr]))
      for(army in g_Armys[plr])
        for(var j = 0; j < army[1]; j++)
        {
          if(Random(2)) continue;
	  if(army[2])
	    ai=army[2];
	  else
	    ai="Bulk";
          pClonk=CreateObject(army[0], AbsX(GameCall("GetCrapStartPosition",GetPlayerTeam(plr))), AbsY(GameCall("GetCrapStartPosition",GetPlayerTeam(plr),true)),plr);
          if(!pClonk){ Log("Error! {{%i}} coudnt created!|Please report this to the Author",army[0]); GameOver(137); return -1;}
	  pClonk->~Call(Format("Set%sAI",ai));
          // Call für M&M Crewmembers wegen Kirche
          pClonk->~ChangedTo();
          AddEffect("IntBulkArmyPart",pClonk,2,0,pClonk);
        }
  }
}

global func FxIntBulkArmyPartStart(pObj,num,temp)
{
  if(temp) return 0;
  var iTeam=GetPlayerTeam(GetOwner(pObj));
  g_aArmyCount[iTeam]++;
  SetScoreboardData(iTeam,ScoreboardCol(COUN),Format("%d/%d",g_aArmyCount[iTeam],g_aArmyAllowed[iTeam]),1);
}

global func FxIntBulkArmyPartStop(pObj,num,reas,temp)
{
  if(temp) return 0;
  var iTeam=GetPlayerTeam(GetOwner(pObj));
  g_aArmyCount[iTeam]--;
  SetScoreboardData(iTeam,ScoreboardCol(COUN),Format("%d/%d",g_aArmyCount[iTeam],g_aArmyAllowed[iTeam]),1);
}




// Veraltetes Zeugs! //

global func FxCreateArmyStart(pTarget, iEffectNumber, iTemp, idType, iX, iY, iPlr)
{
  if(iTemp) return true;
  EffectVar(0,pTarget,iEffectNumber)=idType;
  EffectVar(1,pTarget,iEffectNumber)=iX;
  EffectVar(2,pTarget,iEffectNumber)=iY;
  EffectVar(3,pTarget,iEffectNumber)=iPlr;
}

global func FxCreateArmyTimer(pTarget, iEffectNumber, iTime)
{
  if(!g_fStarted) return 0;
  var idType=EffectVar(0,pTarget,iEffectNumber);
  var iX    =EffectVar(1,pTarget,iEffectNumber);
  var iY    =EffectVar(2,pTarget,iEffectNumber);
  var iPlr  =EffectVar(3,pTarget,iEffectNumber);
  var iX    =EffectVar(1,pTarget,iEffectNumber);
  var iY    =EffectVar(2,pTarget,iEffectNumber);
  // Spieler nicht mehr da?
  if(!GetPlayerName(iPlr))
    return -1;

  // Schon zuviele?
  if(g_aArmyCount[GetPlayerTeam(iPlr)]>=g_aArmyAllowed[GetPlayerTeam(iPlr)])
    return 0;

  if(Random(5))
    return 0;

  var pClonk=CreateObject(idType,iX,iY,iPlr);
  if(!pClonk) return 0;
  pClonk->~SetBulkAI();
  // Call für M&M Crewmembers wegen Kirche
  pClonk->~ChangedTo();
  AddEffect("IntBulkArmyPart",pClonk,2,0,pClonk);
}

// Effekt: GiveMeMoney

global func FxGiveMeMoneyTimer(pTarget, iEffectNumber, iTime)
{
  for(var i = 0; i < GetPlayerCount(); i++)
    if(GetWealth(GetPlayerByIndex(i))<350)
      DoWealth(GetPlayerByIndex(i),RandomX(1,2));
  for(var i = 0; i < GetPlayerCount(); i++)
    if(GetWealth(GetPlayerByIndex(i))<750)
      DoWealth(GetPlayerByIndex(i),1);
}
