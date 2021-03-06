/*-- KI-Status --*/

#strict

protected func Activate(iByPlayer)
{
  var pClonk=GetCursor(iByPlayer);
  // Modernes Dialog-Men
  CreateMenu(CXIN,pClonk,this(),0,"",0,3,true);
  AddMenuItem("AISE", "", NONE, pClonk, 0, 0, "", C4MN_Add_ImgTextSpec);

  // Info
  
  // Alle Spieler-KIs durchgehen
  var i = GetEffectCount("AIPlayer");
  var eff,plr;
  while (i--)
  {
    eff=GetEffect("AIPlayer",0,i);
    plr=EffectVar(0,0,eff);
    if(!Hostile(iByPlayer,plr))
      AddMenuItem(Format("{{%i}}%s %s, spielt meistens %s und hat %d Gold.",GetID(GetCursor(plr)),GetTaggedPlayerName(plr),AIModeString(EffectVar(1,0,eff)),AITypeString(EffectVar(3,0,eff)),GetWealth(plr)),Format("ControlMenu(%d,%d,%d)",eff,iByPlayer,plr),NONE,pClonk,0,0,"",512);
    else
      AddMenuItem(Format("{{%i}}%s spielt meistens %s.",GetID(GetCursor(plr)),GetTaggedPlayerName(plr),AITypeString(EffectVar(3,0,eff))),"",NONE,pClonk,0,0,"",512);
  }
  return(1);
}

protected func ControlMenu(eff,iPlr,iAI)
{
  var pClonk=GetCursor(iPlr);
  CreateMenu(CXIN,pClonk,this(),0,"KI",0,3,true);
  AddMenuItem(Format("Portrait:%i::%x::1",GetID(GetCursor(iAI)),GetPlrColorDw(iAI)), "", NONE, pClonk, 0, 0, "", C4MN_Add_ImgTextSpec);
  AddMenuItem(Format("%s %s, spielt meistens %s und hat %d Gold",GetTaggedPlayerName(iAI),AIModeString(EffectVar(1,0,eff)),AITypeString(EffectVar(3,0,eff)),GetWealth(iAI)),0,NONE,pClonk,0,0,"",512);
  AddMenuItem("","",NONE,pClonk,0,0,"",512);
  AddMenuItem("Baue mehr Trme",Format("(EffectVar(1,0,%d)=0)*ControlMenu(%d,%d,%d)",eff,eff,iPlr,iAI),CXCN,pClonk,0,pClonk,"",512);
  AddMenuItem("Greife den Gegner an",Format("(EffectVar(1,0,%d)=1)*ControlMenu(%d,%d,%d)",eff,eff,iPlr,iAI),AXE1,pClonk,0,pClonk,"",512);
  AddMenuItem("Starte einen Sturmangriff",Format("(EffectVar(1,0,%d)=3)*ControlMenu(%d,%d,%d)",eff,eff,iPlr,iAI),LANC,pClonk,0,pClonk,"",512);
  AddMenuItem("Spare dein Geld",Format("(EffectVar(1,0,%d)=4)*ControlMenu(%d,%d,%d)",eff,eff,iPlr,iAI),GOLD,pClonk,0,pClonk,"",512);
  AddMenuItem("Versuche vorzurcken",Format("(EffectVar(1,0,%d)=5)*ControlMenu(%d,%d,%d)",eff,eff,iPlr,iAI),EFLN,pClonk,0,pClonk,"",512);
  AddMenuItem("","",NONE);
  AddMenuItem("Sicht folgen",Format("FollowPlayer(%d,%d)*ControlMenu(%d,%d,%d)",iAI,iPlr,eff,iPlr,iAI),CXCN,pClonk,0,pClonk,"",512);
}

public func FollowPlayer(iPlr,iPlr2)
{
  SetPlrView(iPlr2,GetCursor(iPlr));
}

protected func AIModeString(iMode)
{
  if(iMode==TWRATCK_AIMode_BuildUp)
    return "baut eine Verteidigung auf";
  if(iMode==TWRATCK_AIMode_Attack)
    return "greift an";
  if(iMode==TWRATCK_AIMode_BuildUpDefense)
    return "verteidigt";
  if(iMode==TWRATCK_AIMode_StormTroop)
    return "startet einen Sturmangriff";
  if(iMode==TWRATCK_AIMode_SaveMoney)
    return "spart Geld";
  if(iMode==TWRATCK_AIMode_FinalStrike)
    return "holt zum entscheidenem Schlag aus";
  if(iMode==TWRATCK_AIMode_Expand)
    return "versucht ein Gebiet zu erobern";
}

protected func AITypeString(iType)
{
  if(iType==TWRATCK_AIType_Defense)
    return "defensiv";
  if(iType==TWRATCK_AIType_Default)
    return "normal";
  if(iType==TWRATCK_AIType_Attack)
    return "aggressiv";
  if(iType==TWRATCK_AIType_Rush)
    return "extrem aggressiv";
}

global func AddPlayerAI(iPlr)
{
  AddEffect("AIPlayer",0,1,35,0,GetID(),iPlr);
}

//*---------------* KI-SpielerSteuerung *---------------*//
/*/
//* EffectVars:
//* 0=Spielernummer
//* 1=Aktueller Modus
//* 2=Vorherige Lebenspunkte
//* 3=Gegnertyp
/*/

// Gegnertyp
static const TWRATCK_AIType_Defense=0;          // Die ultimative Verteidigung
static const TWRATCK_AIType_Default=1;          // Standart
static const TWRATCK_AIType_Attack=2;           // Agressiv
static const TWRATCK_AIType_Rush=3;             // Sehr agressiv

static const TWRATCK_MaxAIType=2;
static const TWRATCK_MaxAIType_Special=3;

// Standartmodi
static const TWRATCK_AIMode_BuildUp=0;          // Aufbauen
static const TWRATCK_AIMode_Attack=1;           // Angreifen (passiv)
static const TWRATCK_AIMode_BuildUpDefense=2;   // Verteidigen
static const TWRATCK_AIMode_StormTroop=3;       // Grossen Angriffstrupp losschicken
static const TWRATCK_AIMode_SaveMoney=4;        // Geld sparen
static const TWRATCK_AIMode_Expand=5;           // Expandieren

static const TWRATCK_MaxAIMode=5;

// Sondermodi
static const TWRATCK_AIMode_FinalStrike=6;
/*static const TWRATCK_AIMode_FinalStrikeInit=5;  // Zum letzen Schlag ausholen (Geld sparen und dann Angreifen)
static const TWRATCK_AIMode_FinalStrikeExec=6;*/

global func FxAIPlayerStart(pTarget, iEffectNumber, iTemp, iPlr)
{
  if(iTemp) return true;
  EffectVar(0,pTarget,iEffectNumber)=iPlr;
  // Baupositionen
  var aPosX=GameCall("TA_AIBuildplacesX",iPlr);
  var aPosY=GameCall("TA_AIBuildplacesY",iPlr);
  var iTarget=Random(GetLength(aPosX));
  SetPosition(aPosX[iTarget],aPosY[iTarget],GetCursor(iPlr));

  // Typ des KI-Gegners festlegen : Verteidiger, Ausgeglichen, Agressiv oder Rusher?
  EffectVar(3,pTarget,iEffectNumber)=RandomX(TWRATCK_AIType_Defense,TWRATCK_MaxAIType);
  if(!Random(3))
    EffectVar(3,pTarget,iEffectNumber)=RandomX(TWRATCK_AIType_Defense,TWRATCK_MaxAIType_Special);
}

global func FxAIPlayerTimer(pTarget, iEffectNumber, iTime)
{
  var iPlr  =EffectVar(0,pTarget,iEffectNumber);
  // Spieler nicht mehr da?
  if(!GetPlayerName(iPlr))
    return -1;

  var pClonk=GetCursor(iPlr);

  if(GetCommand(pClonk)S="MoveTo")
    if(!Random(250))
    {
      temp=FindObject2(Find_ID(COBS),Find_Allied(iPlr),Sort_Distance());
      SetPosition(GetX(temp),GetY(temp),pClonk);
      SetCommand(pClonk,"None");
      return 0;
    }

  GameCall("HardcodetAIMovement",pClonk);

  if(!Random(100))
    SetCommand(pClonk,"None");

  if(GetCommand(pClonk)) return 0;

  var iMode =EffectVar(1,pTarget,iEffectNumber);
  var iType=EffectVar(3,pTarget,iEffectNumber);
  // KI im VSModus
  if(g_iMode==TWRATK_MODE_VS)
  {
    if(EffectVar(2,pTarget,iEffectNumber)!=g_aLiveAmount[GetPlayerTeam(iPlr)])
      if(!Random(3))
        iMode=TWRATCK_AIMode_BuildUpDefense;
  
    EffectVar(2,pTarget,iEffectNumber)=g_aLiveAmount[GetPlayerTeam(iPlr)];
    
    // Rusher intressieren sich nicht so für die eigene Verteidigung
    if(ScriptCounter()>(14000*(iType!=TWRATCK_AIType_Rush)))
      if(iMode!=TWRATCK_AIMode_FinalStrike)
        if(!Random(100))
        {
          iMode=RandomX(TWRATCK_AIMode_BuildUp,TWRATCK_MaxAIMode);
          if(Random(2))
          {
            if(iType==TWRATCK_AIType_Rush||iType==TWRATCK_AIType_Attack)
              iMode=RandomX(TWRATCK_AIMode_Attack,TWRATCK_MaxAIMode);
            else if(iType==TWRATCK_AIType_Defense)
              while(iMode==TWRATCK_AIMode_Attack)
                iMode=RandomX(TWRATCK_AIType_Defense,TWRATCK_MaxAIMode);
          }
        }
  
    // Verteidigung fertig? Dann zum entscheidenen Schlag aushohlen
    if(ObjectCount2(Find_Category(C4D_Structure),Find_Allied(iPlr),Find_OCF(OCF_Fullcon))>RandomX(20,100))
      if(!Random(250))
        iMode=TWRATCK_AIMode_FinalStrike;
  
    if(iMode==TWRATCK_AIMode_StormTroop)
      if(GetWealth(iPlr)<50)
        iMode=TWRATCK_AIMode_BuildUp;
  }
  // KI im Zeitkampfmodus
  else if(g_iMode==TWRATK_MODE_VSTime)
  {
    if(g_iGamePhase==2)
    {
      if(iMode==TWRATCK_AIMode_Attack)
      {
        if(!Random(100))
          iMode=TWRATCK_AIMode_StormTroop;
        if(!Random(250))
          iMode=TWRATCK_AIMode_FinalStrike;
      }
      else
      {
        if(!Random(100))
          iMode=TWRATCK_AIMode_Attack;
      }
    }
  }
  // sonstige KI (Survival)
  else
  {
    // den Modus nicht von selbst ändern
  }

  EffectVar(1,pTarget,iEffectNumber)=iMode;

  // Die KI an seinen Charakter anpassen
  var iBBuild;
  var iBAttack;
  var iBLevelUp;

  if(iType==TWRATCK_AIType_Defense)
  {
    iBBuild=-2;
    iBAttack=5;
    iBLevelUp=0;
  }

  if(iType==TWRATCK_AIType_Attack)
  {
    iBBuild=2;
    iBAttack=-1;
    iBLevelUp=0;
  }

  if(iType==TWRATCK_AIType_Rush)
  {
    iBBuild=5;
    iBAttack=-2;
    iBLevelUp=5;
  }

  // Die KI an den Modus anpassen
  var iBuild;
  var iAttack;
  var iLevelUp;

  if(iMode==TWRATCK_AIMode_BuildUp)
  {
    iBuild=4;
    iAttack=55;
    iLevelUp=55;
  }

  if(iMode==TWRATCK_AIMode_BuildUpDefense)
  {
    iBuild=5;
    iAttack=20;
    iLevelUp=15;
  }

  if(iMode==TWRATCK_AIMode_Attack)
  {
    iBuild=20;
    iAttack=10;
    iLevelUp=10;
  }

  if(iMode==TWRATCK_AIMode_Expand)
  {
    iBuild=13;
    iAttack=8;
    iLevelUp=300;
  }

  if(iMode==TWRATCK_AIMode_StormTroop)
  {
    iBuild=200;
    iAttack=2;
    iLevelUp=200;
  }

  if(iMode==TWRATCK_AIMode_SaveMoney)
  {
    return 0;
  }

  if(iMode==TWRATCK_AIMode_FinalStrike)
  {
    if(GetWealth(iPlr)<750-(350*(iType==TWRATCK_AIType_Rush)))
    {
      iBuild=500;
      iAttack=500;
      iLevelUp=150;
    }
    else
      EffectVar(1,pTarget,iEffectNumber)=TWRATCK_AIMode_StormTroop;
  }

  iBuild+=iBBuild;
  iAttack+=iBAttack;
  iLevelUp+=iBLevelUp;

  // Sachen bauen
  if(!Random(iBuild))
    //if(GetWealth(iPlr)>50)
      //if(!GetCommand(pClonk))
      {
        SetCommand(pClonk,"UnGrab");
        var temp;
        // Unfertige Türme zuerst fertigbauen
        if(!Random(4))
          if(temp=FindObject2(Find_Category(C4D_Structure),Find_Allied(iPlr),Find_Not(Find_OCF(OCF_Fullcon)),Find_Not(OCF_OnFire)))
          {
            var tele=FindObject2(Find_ID(COBS),Find_Allied(iPlr),Sort_Distance(GetX(pClonk),GetY(pClonk)));
              if(Distance(Var(0),Var(1),GetX(pClonk),GetY(pClonk))>ObjectDistance(tele,pClonk))
                if(Distance(Var(0),Var(1),GetX(pClonk),GetY(pClonk))>200)
                  CommandTeleportTo(pClonk,GetX(temp),GetY(temp));
            SetCommand(pClonk,"Build",temp);
            return true;
          }
        // Ansonsten neue bauen
        if(g_iGamePhase!=2)
        {
            // Baupositionen
            var aPosX=GameCall("TA_AIBuildplacesX",iPlr,iMode);
            var aPosY=GameCall("TA_AIBuildplacesY",iPlr,iMode);
            var i,iTarget;
            
            // Vom Feind eroberte Baupl„tze aussortieren
            for(i = 0; i < GetLength(aPosX); i++)
            {
              var iVal=ObjectCount2(Find_Category(C4D_Structure),Find_Hostile(iPlr),Find_Distance(200,aPosX[i],aPosY[i]),Find_OCF(OCF_Fullcon))*20;
              iVal+=ObjectCount2(Find_OCF(OCF_Alive),Find_Category(C4D_Living),Find_Hostile(iPlr),Find_Distance(200))*10;
              if(iVal>50)
              {
                // Baustellen im erobertem Gebiet wieder abbauen
                if(!Random(5))
                  if(temp=FindObject2(Find_Category(C4D_Structure),Find_Owner(iPlr),Find_Distance(200,aPosX[i],aPosY[i]),Find_Not(Find_OCF(OCF_Fullcon))))
                    temp->Schedule("DoCon(-1)",3,200);
                // Position löschen
                DeleteArrayItem(i, aPosX);
                DeleteArrayItem(i, aPosY);
                i--;
              }
            }

            // Kaum bebaute Bauplätze bevorzugen

            // Erstmal minimum rausfinden...
            var iMin=100;
            for(i = 0; i < GetLength(aPosX); i++)
            {
              iVal=ObjectCount2(Find_Category(C4D_Structure),Find_Allied(iPlr),Find_Distance(200,aPosX[i],aPosY[i]),Find_OCF(OCF_Fullcon));
              if(iVal<iMin)
                iMin=iVal;
            }
            // ...und dann Wahrscheinlicher machen
            for(i = 0; i < GetLength(aPosX); i++)
            {
              iVal=ObjectCount2(Find_Category(C4D_Structure),Find_Allied(iPlr),Find_Distance(200,aPosX[i],aPosY[i]),Find_OCF(OCF_Fullcon));
              if(Random(iVal-iMin))
              {
                // Position löschen
                DeleteArrayItem(i, aPosX);
                DeleteArrayItem(i, aPosY);
                i--;
              }
            }

            if(!GetLength(aPosX))
              return 0;

            // Wurde zuviel erobert? In Verteidigungsmodus wechseln
            if(GetLength(aPosX)<4)
              if(!Random(45))
                EffectVar(1,pTarget,iEffectNumber)=TWRATCK_AIMode_BuildUpDefense;

            // Zielposition rausfinden
            for(i = 0; i < GetLength(aPosX); i++)
              if(Distance(aPosX[i],aPosY[i],GetX(pClonk),GetY(pClonk))<150)
              {
                iTarget=i+1;
                break;
              }
            // Bauplatz ab und zu wechseln
            if(!Random(3))
              iTarget=0;

            if(!iTarget)
              iTarget=Random(GetLength(aPosX))+1;

            // Beim expandieren möglichst weit entfernte Gebiete bebauen
            if(iMode==TWRATCK_AIMode_Expand)
              if(iTarget<GetLength(aPosX)/2)
                iTarget=(GetLength(aPosX)/2+Random(GetLength(aPosX)/2))+1;

            // Turm auswählen
            var j,Def;
            while(Def = GetDefinition(i++,C4D_Structure))
              if(Def->~CanBeBuild(pClonk))
                if(!(Def->~NoAIBuild(pClonk,iMode,aPosX[iTarget-1],aPosY[iTarget-1])))
                  if(GetWealth(iPlr)>GetValue(0,Def))
                    if((Random(GetValue(0,Def)/10))&&Random(GetValue(0,Def)/10)) // Teure Trme bevorzugen
                      Var(j++)=Def;

            var idTower=Var(Random(j));

            if(!idTower) return 0;

            // Position rausfinden
            Var(0)=aPosX[iTarget-1];Var(1)=aPosY[iTarget-1];
            if(!FindConstructionSite(idTower,0,1)) return 0;

            for(i = 0; i <= 10; i++)
              if(IsGoodBuildPos(idTower,Var(), Var(1)))
                break;
              else
                Var()+=RandomX(-2,2);

            if(!IsGoodBuildPos(idTower,Var(), Var(1)))
              FindConstructionSite(idTower,0,1);

            if(!IsGoodBuildPos(idTower,Var(), Var(1)))
              return 0;

            // Hat einen Bausatz?
            if(!FindContents(CNKT,pClonk))
              CreateContents(CNKT,pClonk);

            // Endlich bauen
            temp=FindObject2(Find_ID(COBS),Find_Allied(iPlr),Sort_Distance(GetX(pClonk),GetY(pClonk)));
            if(Distance(Var(0),Var(1),GetX(pClonk),GetY(pClonk))>ObjectDistance(temp,pClonk))
              if(Distance(Var(0),Var(1),GetX(pClonk),GetY(pClonk))>200)
                CommandTeleportTo(pClonk,Var(),Var(1));

            AppendCommand(pClonk,"MoveTo",0,Var(0),Var(1));
            AppendCommand(pClonk,"Call",FindContents(CNKT,pClonk),idTower,0,0,0,"CreateConstr");
            return 1;
        }
    }
  // Truppen ausbilden
  if(g_fStarted)
    if(!Random(iAttack))
      if(GetWealth(iPlr)>50)
      {
        // Ist eine Basis in der N„he? Einfach kaufen
        if(temp=FindObject2(Find_AtPoint(GetX(pClonk),GetY(pClonk)),Find_ID(COBS),Find_Allied(iPlr),Find_OCF(OCF_Fullcon)))
          temp->~BuyRandomTroops(pClonk,Random(ObjectCount2(Find_Category(C4D_Structure),Find_Hostile(iPlr),Find_OCF(OCF_Fullcon))/6)+(iMode==TWRATCK_AIMode_Expand));
        // Sonst zur n„chsten Basis laufen
        else
        {
          temp=FindObject2(Find_ID(COBS),Find_Allied(iPlr),Sort_Distance());
          SetCommand(pClonk,"MoveTo",temp);
          AppendCommand(pClonk,"Grab",temp);
          AppendCommand(pClonk,"Call",temp,0,0,0,0,"BuyRandomTroops");
        }
        return 0;
      }
  if(!Random(iLevelUp))
    if(GetWealth(iPlr)>100)
    {
      // Ist eine Basis in der N„he? Einfach kaufen
      if(temp=FindObject2(Find_AtPoint(GetX(pClonk),GetY(pClonk)),Find_ID(COBS),Find_Allied(iPlr),Find_OCF(OCF_Fullcon)))
      {
        if(!Random(g_aLiveAmount[GetPlayerTeam(iPlr)]*2))
          return temp->~IncLives(iPlr);
        if(!Random(17))
          return temp->~IncTroopStr(iPlr);
        if(!Random(16))
          return temp->~IncTroopLimit(iPlr);
        if(!Random(15))
          return temp->~IncTroopBoost(iPlr);
      }
      // Sonst zur n„chsten Basis laufen
      else
      {
        temp=FindObject2(Find_ID(COBS),Find_Allied(iPlr),Sort_Distance());
        SetCommand(pClonk,"MoveTo",temp);
        AppendCommand(pClonk,"Grab",temp);
      }
    }
}

global func CommandTeleportTo(pClonk,iX,iY)
{
  var temp=FindObject2(Find_ID(COBS),Find_Allied(GetOwner(pClonk)),Sort_Distance(GetX(pClonk),GetY(pClonk)));
  AddCommand(pClonk,"Call",temp,iX,iY-20,0,0,"Teleport2");
  AddCommand(pClonk,"Grab",temp);
  AddCommand(pClonk,"MoveTo",temp);
}

global func IsGoodBuildPos(id idDef,int iX,int iY)
{
  var dumm1=CreateObject(TIM1,iX,iY,-1);
  var dumm2=dumm1->CreateConstruction(idDef,0,0,-1,1,0,1);
  var dumm3=false;
  if(dumm2)
  {
    dumm3=true;
    RemoveObject(dumm2);
  }
  RemoveObject(dumm1);
  return dumm3;
}
