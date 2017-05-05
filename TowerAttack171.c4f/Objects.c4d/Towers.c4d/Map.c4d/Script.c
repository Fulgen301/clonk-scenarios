/*-- Kartenprojektor --*/

#strict 2

local iNew; // Nächste Phase
static g_fShouldFollow;

func Initialize() {
  SetAction("Move");
  if(GetOwner()>=0)
   SetName(Format("%s%s%d",GetTeamName(GetPlayerTeam(GetOwner())),"Base",ObjectCount2(Find_ID(COBS),Find_Allied(GetOwner()))));
  if(GetPlayerTeam(GetOwner())==2)
    SetGraphics("2");
  if(!GetLength(g_fShouldFollow))
    g_fShouldFollow=[];
  return true;
}

func Check()
{
  for(var pObj in FindObjects(Find_OCF(OCF_Alive)))
    if(!Random(3))
      CreateParticle("PSpark", -13+(24*GetX(pObj)/LandscapeWidth()), -9+(14*GetY(pObj)/LandscapeHeight()), 0, 0, Random(16)+15, GetColorDw(pObj));
}

func ControlDigDouble(pClonk)
{
  if(Hostile(GetOwner(),GetOwner(pClonk)))
    return 0;
  SetOwner(GetOwner(pClonk));
  CreateMenu(COBS,pClonk,0,4,"ERROR");
  AddMenuItem("Einkaufen","CreateEquipMenu",OTSY,pClonk,0,pClonk,"",2,0);
  AddMenuItem("Befehle","CreateCommandMenu",BKAI,pClonk,0,pClonk);
  AddMenuItem("Truppen-Managment","CreateTroopMenu",OTSY,pClonk,0,pClonk,"",2,4);
  if(g_fStarted)
    AddMenuItem("Verstaerkung rufen","CreateMercenaryMenu",OTSY,pClonk,0,pClonk,"",2,3);
  var stringA,stringB;
  for(var telepoint in FindObjects(Find_Or(Find_ID(TELE),Find_And(Find_Exclude(this()),Find_ID(COBS),Find_Allied(GetOwner())))))
  {
    stringA=Format("Zu %s teleportieren",GetName(telepoint));
    stringB=Format("Teleport(%d,%d,Object(%d))",GetX(telepoint),GetY(telepoint),ObjectNumber(pClonk));
    //Log("%s:%s",stringA,stringB);
    AddMenuItem(stringA,stringB,OTSY,pClonk,0,0,"blar",2,6);
  }
}

func Teleport(iX,iY,pObject)
{
  pObject->CastObjects(SPRK,5,25);
  pObject->SetPosition(iX,iY);
  pObject->CastObjects(SPRK,5,25);
}

func Teleport2(pObject,iX,iY)
{
  Teleport(iX,iY,pObject);
}

func CreateEquipMenu(idDummy,pClonk)
{
  var i;
  CreateMenu(COBS,pClonk,0,2,"ERROR",0,0,1);
  if(pClonk->~CanUse(ARMR)){
    AddMenuItem("%s","Buy",ARMR,pClonk,0,pClonk); i++;}
  if(pClonk->~CanUse(SHIE)){
    AddMenuItem("%s","Buy",SHIE,pClonk,0,pClonk); i++;}
  if(pClonk->~CanUse(SWOR)){
    AddMenuItem("%s","Buy",SWOR,pClonk,0,pClonk); i++;}
  if(pClonk->~CanUse(AXE1)){
    AddMenuItem("%s","Buy",AXE1,pClonk,0,pClonk); i++;}
  if((pClonk->~IsKnight()||pClonk->~IsKanderian())&&!pClonk->~IsAssassin()){
    AddMenuItem("%s","Buy",SPER,pClonk,0,pClonk); i++;}
  if(pClonk->~CanUse(KNFP)){
    AddMenuItem("%s","Buy",KNFP,pClonk,0,pClonk); i++;}
  if(pClonk->~IsPaladin()){
    AddMenuItem("%s","Buy",TSWD,pClonk,0,pClonk); i++;}
  if(pClonk->~CanUse(BOW1))
  {
    AddMenuItem("%s","Buy",BOW1,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",ARWP,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",FARP,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",XARP,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",PARP,pClonk,0,pClonk);
    i+=5;
  }
  if(pClonk->~CanUse(CRBW))
  {
    AddMenuItem("%s","Buy",CRBW,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",BOTP,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",NBTP,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",HOOK,pClonk,0,pClonk);
    i+=4;
  }
  if(pClonk->~CanUse(MUSK))
  {
    AddMenuItem("%s","Buy",MUSK,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",BLTP,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",SBLP,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",PBLP,pClonk,0,pClonk);
    i+=4;
  }
  if(pClonk->~CanUse(SCKZ)){
    AddMenuItem("%s","Buy",SCKZ,pClonk,0,pClonk); i++;}
    
  if(pClonk->~CanUse(SMOD)){
    AddMenuItem("%s","Buy",SMOD,pClonk,0,pClonk); i++;}

  if(!i);
  else if(i>11)
    while(i++<22)
      AddMenuItem("",0,NONE,pClonk,0,pClonk);
  else
    while(i++<11)
      AddMenuItem("",0,NONE,pClonk,0,pClonk);
  i=0;
  
  AddMenuItem("%s","Buy",SFLN,pClonk,0,pClonk);
  AddMenuItem("%s","Buy",EFLN,pClonk,0,pClonk);
  AddMenuItem("%s","Buy",STFN,pClonk,0,pClonk);
  AddMenuItem("%s","Buy",FBMP,pClonk,0,pClonk);
  i+=4;
  
  AddMenuItem("%s","Buy",LFAM,pClonk,0,pClonk);
  AddMenuItem("%s","Buy",BRED,pClonk,0,pClonk);
  i+=2;
  while(i++<11)
    AddMenuItem("",0,NONE,pClonk,0,pClonk);
  i=0;
  
  AddMenuItem("%s","Buy",PFIR,pClonk,0,pClonk);
  AddMenuItem("%s","Buy",PHEA,pClonk,0,pClonk);
  AddMenuItem("%s","Buy",PIMM,pClonk,0,pClonk);
  i+=3;
  if(GetID(pClonk)==MAGE){
    AddMenuItem("%s","Buy",PMAN,pClonk,0,pClonk); i++;}
  AddMenuItem("%s","Buy",PMON,pClonk,0,pClonk);
  AddMenuItem("%s","Buy",PSTO,pClonk,0,pClonk);
  AddMenuItem("%s","Buy",PWIP,pClonk,0,pClonk);
  i+=3;
  while(i++<11)
    AddMenuItem("",0,NONE,pClonk,0,pClonk);
  i=0;
  AddMenuItem("5x %s","Buy",ICRS,pClonk,5,pClonk,"",128,0,10);
  AddMenuItem("5x %s","Buy",IROC,pClonk,5,pClonk,"",128,0,10);
  AddMenuItem("5x %s","Buy",ISPH,pClonk,5,pClonk,"",128,0,10);
  AddMenuItem("5x %s","Buy",IHOL,pClonk,5,pClonk,"",128,0,10);
  AddMenuItem("5x %s","Buy",ILOA,pClonk,5,pClonk,"",128,0,10);
  AddMenuItem("5x %s","Buy",IGOL,pClonk,5,pClonk,"",128,0,10);
  AddMenuItem("5x %s","Buy",IMUS,pClonk,5,pClonk,"",128,0,10);
  AddMenuItem("5x %s","Buy",INEC,pClonk,5,pClonk,"",128,0,10);
  AddMenuItem("5x %s","Buy",IBON,pClonk,5,pClonk,"",128,0,10);
  AddMenuItem("5x %s","Buy",IBLO,pClonk,5,pClonk,"",128,0,10);
  AddMenuItem("5x %s","Buy",IASH,pClonk,5,pClonk,"",128,0,10);
  if(GetID(pClonk)==MYST)
  {
    //AddMenuItem("%s","Buy",ASHS,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",COAL,pClonk,0,pClonk);
    //AddMenuItem("%s","Buy",CNCR,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",CRYS,pClonk,0,pClonk);
    //AddMenuItem("%s","Buy",ERTH,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",GOLD,pClonk,0,pClonk);
    //AddMenuItem("%s","Buy",LIQG,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",ORE1,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",SPHR,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",WOOD,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",HLGN,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",GUNP,pClonk,0,pClonk);
    AddMenuItem("%s","Buy",SKUL,pClonk,0,pClonk);
  }
  AddMenuItem("%s","Buy",SHEL,pClonk,0,pClonk);
  AddMenuItem("%s","Buy",FMEG,pClonk,0,pClonk);
  AddMenuItem("%s","Buy",MEGG,pClonk,0,pClonk);
  AddMenuItem("%s","Buy",ZAPN,pClonk,0,pClonk);
  AddMenuItem("%s","Buy",ALC_,pClonk,0,pClonk);
  if(g_iGamePhase!=2)
    AddMenuItem("%s","Buy",CNKT,pClonk,0,pClonk);
  /*AddMenuItem("",0,NONE,pClonk,0,pClonk);
  AddMenuItem("",0,NONE,pClonk,0,pClonk);
  AddMenuItem("",0,NONE,pClonk,0,pClonk);
  AddMenuItem("",0,NONE,pClonk,0,pClonk);*/
  SetMenuSize(11,0,pClonk);
}

public func Buy(idDef,pClonk,bRight,iVal)
{
  var owner=GetOwner(pClonk);
  var alchi;
  if(!iVal) iVal=GetValue(0,idDef);

  if(GetWealth(owner) < iVal)
  {
    PlayerMessage(owner,"$NotEnoughMoney$",pClonk);
    return(1);
  }
  if(GetCategory(0,idDef)&C4D_StaticBack)
    if(!(alchi=GetAlchemBag(pClonk)))
      return PlayerMessage(owner,"$NoAlchiBag$",pClonk);

  DoWealth(owner,-iVal);

  var object;
  // Alchemiezutaten
  if(GetCategory(0,idDef)&C4D_StaticBack)
    DoAlchem(idDef,5,alchi);
  else
  {
    object = CreateObject(idDef,0,25,owner);
    Collect(object,pClonk);
  }
  Sound("Cash");
}

func CreateCommandMenu(idDummy,pClonk)
{
  CreateMenu(COBS,pClonk,0,4,"ERROR");
  AddMenuItem("ANGRIFF!!",Format("SetArmyMode(%d,%d)",GetOwner(pClonk),TWRATK_Cmd_Attack),COSY,pClonk,0,0,"",2,0);
  AddMenuItem("Verteidigen",Format("SetArmyMode(%d,%d)",GetOwner(pClonk),TWRATK_Cmd_Defend),COSY,pClonk,0,0,"",2,1);
  AddMenuItem("Zurueckziehen",Format("SetArmyMode(%d,%d)",GetOwner(pClonk),TWRATK_Cmd_Retreat),COSY,pClonk,0,0,"",2,2);
  //AddMenuItem("Folgen",Format("SetArmyMode(%d,%d)",GetOwner(pClonk),TWRATK_Cmd_Follow),COSY,pClonk,0,0,"",2,3);
}

func CreateTroopMenu(idDummy,pClonk)
{
  CreateMenu(COBS,pClonk,0,2,"ERROR",0,0,1);
  AddMenuItem("+1 Lebenspunkt",Format("IncLives(%d)",GetOwner(pClonk)),OTSY,pClonk,0,0,"",130,4,200);
  AddMenuItem("+1 Einheitenlimit",Format("IncTroopLimit(%d)",GetOwner(pClonk)),OTSY,pClonk,0,0,"",130,1,100);
  AddMenuItem("+1 Truppenstaerke",Format("IncTroopStr(%d)",GetOwner(pClonk)),OTSY,pClonk,0,0,"",130,7,100);
  AddMenuItem("Truppen verstaerken",Format("OpenMoreTroopMenu(%d)",GetOwner(pClonk)),OTSY,pClonk,0,0,"",130,2,0);
}

func OpenMoreTroopMenu(iPlr,iSel)
{
  var pClonk=GetCursor(iPlr);
  CreateMenu(OTSY,pClonk,0,2,"Truppen erweitern",0,3,true);
  var szTroops="";
  for(var troop in g_Armys[iPlr])
  {
    szTroops=Format("%s %dx{{%i}}",szTroops,troop[1],troop[0]);
    if(troop[2]=="Destroyer")
      szTroops=Format("%s({{EFLN}})",szTroops);
    if(troop[2]=="Bow")
      szTroops=Format("%s({{BOW1}})",szTroops);
  }
  // Info
  AddMenuItem(Format("Hier kannst du deine Standardtruppen erweitern. |Momentane Truppen:| %s",
                    szTroops),"",NONE,pClonk,0,0,"",512);
  AddMenuItem("+Gigant",Format("AddToArmy(%d,BGNT,0,500,1)",iPlr),BGNT,pClonk,0,0,"",128,0,500);
  AddMenuItem("+Troll",Format("AddToArmy(%d,BTRL,0,500,2)",iPlr),BTRL,pClonk,0,0,"",128,0,500);
  AddMenuItem("+Ritter",Format("AddToArmy(%d,KNIG,0,300,3)",iPlr),KNIG,pClonk,0,0,"",128,0,300);
  AddMenuItem("+Kanderianer",Format("AddToArmy(%d,KAND,0,300,4)",iPlr),KAND,pClonk,0,0,"",128,0,300);
  AddMenuItem("+Priester",Format("AddToArmy(%d,PRST,0,225,5)",iPlr),PRST,pClonk,0,0,"",128,0,225);
  AddMenuItem("+Skelett",Format("AddToArmy(%d,SKLT,0,225,6)",iPlr),SKLT,pClonk,0,0,"",128,0,225);
  AddMenuItem("+Zombie",Format("AddToArmy(%d,_ZMB,0,150,7)",iPlr),_ZMB,pClonk,0,0,"",128,0,150);
  AddMenuItem("+Clonk",Format("AddToArmy(%d,CLNK,0,150,9)",iPlr),CLNK,pClonk,0,0,"",128,0,150);
  AddMenuItem("+Paladin",Format("AddToArmy(%d,PLDN,\"Pala\",800,10)",iPlr),PLDN,pClonk,0,0,"",128,0,800);
  AddMenuItem("+Magier",Format("AddToArmy(%d,SCLK,\"Magican\",800,10)",iPlr),SCLK,pClonk,0,0,"",128,0,800);
  AddMenuItem("+Magus",Format("AddToArmy(%d,MAGE,\"Magican\",1000,11)",iPlr),MAGE,pClonk,0,0,"",128,0,1000);
  AddMenuItem("+Bogenschuetze",Format("AddToArmy(%d,KNIG,\"Bow\",650,12)",iPlr),BOW1,pClonk,0,0,"",128,0,700);
  AddMenuItem("+Zerstoerer",Format("AddToArmy(%d,KNIG,\"Destroyer\",650,13)",iPlr),KNIG,pClonk,0,0,"",128,0,650);
  AddMenuItem("+Zerstoerer",Format("AddToArmy(%d,CLNK,\"Destroyer\",550,14)",iPlr),CLNK,pClonk,0,0,"",128,0,550);
  if(iSel)
    SelectMenuItem(iSel,pClonk);
}

func AddToArmy(iPlr,idDef,szAI,iCost,iSel)
{
  if(GetWealth(iPlr)<iCost)
  {
    PlayerMessage(iPlr,"$NotEnoughMoney$",this);
    return OpenMoreTroopMenu(iPlr,iSel);
  }
  DoWealth(iPlr,-iCost);
  for(var i; i<GetLength(g_Armys[iPlr]); i++)
  {
    if(g_Armys[iPlr][i][0]==idDef)
      if(g_Armys[iPlr][i][2]==szAI)
      {
	g_Armys[iPlr][i][1]++;
	return OpenMoreTroopMenu(iPlr,iSel);
      }
  }
  g_Armys[iPlr][GetLength(g_Armys[iPlr])]=[idDef,1,szAI];
  return OpenMoreTroopMenu(iPlr,iSel);
}

func CreateMercenaryMenu(idDummy,pClonk)
{
  CreateMenu(COBS,pClonk,0,2,"ERROR",0,0,1);
  AddMenuItem("2 %sen",Format("Hire(BGNT,2,40,%d)",GetOwner(pClonk)),BGNT,pClonk,2,0,"",128,0,40);
  AddMenuItem("2 %se",Format("Hire(BTRL,2,40,%d)",GetOwner(pClonk)),BTRL,pClonk,2,0,"",128,0,40);
  AddMenuItem("%s-Truppe",Format("Hire(SKLT,5,50,%d,_SKN,1)",GetOwner(pClonk)),_SKN,pClonk,0,0,"",128,0,50);
  AddMenuItem("Glaubens-Truppe",Format("Hire(KNIG,2,75,%d,PLDN,1,PRST,3)",GetOwner(pClonk)),PLDN,pClonk,0,0,"",128,0,75);
  AddMenuItem("Kanderia-Truppe",Format("Hire(KAND,4,50,%d,KAND,1)",GetOwner(pClonk)),KAND,pClonk,0,0,"",128,0,50);
  AddMenuItem("Zerstörungs-Truppe",Format("Hire(CLNK,6,70,%d,KNIG,2,0,0,\"Destroyer\")",GetOwner(pClonk)),EFLN,pClonk,0,0,"",128,0,70);
  AddMenuItem("Bogen-Truppe",Format("Hire(KNIG,4,80,%d,0,0,0,0,\"Bow\")",GetOwner(pClonk)),BOW1,pClonk,0,0,"",128,0,80);
  //AddMenuItem("","",NONE,pClonk);
  AddMenuItem("Folgen/Angreifen",Format("(g_fShouldFollow[%d]=!g_fShouldFollow[%d])+CloseMenu()+CreateMercenaryMenu(0,GetCursor(%d))",GetPlayerID(GetOwner(pClonk)),GetPlayerID(GetOwner(pClonk))),COSY,pClonk,0,0,"Blar",2,g_fShouldFollow[GetPlayerID(GetOwner(pClonk))]*3);

  /*AddMenuItem("Held:%s",Format("HireHero(MYST,35,%d)",GetOwner(pClonk)),MYST,pClonk,0,0,"",128,0,35);
  AddMenuItem("Held:%s",Format("HireHero(_SSR,55,%d)",GetOwner(pClonk)),_SSR,pClonk,0,0,"",128,0,55);
  AddMenuItem("Held:%s",Format("HireHero(PLDN,50,%d)",GetOwner(pClonk)),PLDN,pClonk,0,0,"",128,0,50);
  AddMenuItem("Held:%s",Format("HireHero(SCLK,55,%d)",GetOwner(pClonk)),SCLK,pClonk,0,0,"",128,0,55);
  AddMenuItem("Held:%s",Format("HireHero(MAGE,65,%d)",GetOwner(pClonk)),MAGE,pClonk,0,0,"",128,0,65);
  AddMenuItem("Held:%s",Format("HireHero(LICH,65,%d)",GetOwner(pClonk)),LICH,pClonk,0,0,"",128,0,65);
  AddMenuItem("Held:%s",Format("HireHero(KNIG,40,%d)",GetOwner(pClonk)),KNIG,pClonk,0,0,"",128,0,40);
  AddMenuItem("","",NONE,pClonk);*/

  AddMenuItem("General:%s",Format("HireGeneral(_SKN,45,%d)",GetOwner(pClonk)),_SKN,pClonk,0,0,"",128,0,45);
  AddMenuItem("General:%s",Format("HireGeneral(KNIG,50,%d)",GetOwner(pClonk)),KNIG,pClonk,0,0,"",128,0,50);
  AddMenuItem("General:%s",Format("HireGeneral(PLDN,60,%d)",GetOwner(pClonk)),PLDN,pClonk,0,0,"",128,0,60);
  AddMenuItem("General:%s",Format("HireGeneral(KING,75,%d)",GetOwner(pClonk)),KING,pClonk,0,0,"",128,0,75);
  AddMenuItem("General:%s",Format("HireGeneral(ASAS,65,%d)",GetOwner(pClonk)),ASAS,pClonk,0,0,"",128,0,65);
  AddMenuItem("General:%s",Format("HireGeneral(MAGE,75,%d)",GetOwner(pClonk)),MAGE,pClonk,0,0,"",128,0,75);
  AddMenuItem("General:%s",Format("HireGeneral(LICH,75,%d)",GetOwner(pClonk)),LICH,pClonk,0,0,"",128,0,75);
  AddMenuItem("General:%s",Format("HireGeneral(MYST,45,%d)",GetOwner(pClonk)),MYST,pClonk,0,0,"",128,0,45);
  SetMenuSize(8,3,pClonk);
}

func BuyRandomTroops(pClonk,fNeedDestroy)
{
  var i=Random(8);
  //if(!Random(16)) i=Random(15);
  var plr=GetOwner(pClonk);
  
  if(fNeedDestroy)
    if(Random(4))
      return Hire(CLNK,4,70,plr,KNIG,1,0,0,"Destroyer");
  
  // Einheiten
  if(!i--)
    return Hire(BGNT,2,30,plr);
  if(!i--)
    return Hire(BTRL,2,30,plr);
  if(!i--)
    return Hire(SKLT,5,50,plr,_SKN,1);
  if(!i--)
    return Hire(KNIG,2,75,plr,PLDN,1,PRST,3);
  if(!i--)
    return Hire(KAND,4,50,plr,KAND,1);
  if(!i--)
    return Hire(CLNK,4,70,plr,KNIG,1,0,0,"Destroyer");
  if(!i--)
    return Hire(KNIG,4,80,plr,0,0,0,0,"Bow");
  // Helden
  /*if(!i--)
    return HireHero(MYST,35,plr);
  if(!i--)
    return HireHero(_SSR,55,plr);
  if(!i--)
    return HireHero(PLDN,50,plr);
  if(!i--)
    return HireHero(SCLK,55,plr);
  if(!i--)
    return HireHero(MAGE,65,plr);
  if(!i--)
    return HireHero(LICH,65,plr);
  if(!i--)
    return HireHero(KNIG,40,plr);*/
}

func Hire(idDef,iCount,iCost,iPlr,idDef2,iCount2,idDef3,iCount3,szAI)
{
  if(GetWealth(iPlr) < iCost)
  {
    PlayerMessage(iPlr,"$NotEnoughMoney$",this);
    return(1);
  }
  if(!szAI)
    szAI="Bulk";
  var pClonk;
  while(iCount-->0)
  {
    (pClonk=CreateObject(idDef,RandomX(-50,50),0,iPlr))->~Call(Format("Set%sAI",szAI));
    pClonk->~ChangedTo();
    if(g_fShouldFollow[GetPlayerID(iPlr)])
      pClonk->SetAIMode(TWRATK_Cmd_Follow,GetCursor(iPlr));
  }
  while(iCount2-->0)
  {
    (pClonk=CreateObject(idDef2,RandomX(-50,50),0,iPlr))->~Call(Format("Set%sAI",szAI));
    pClonk->~ChangedTo();
    if(g_fShouldFollow[GetPlayerID(iPlr)])
      pClonk->SetAIMode(TWRATK_Cmd_Follow,GetCursor(iPlr));
  }
  while(iCount3-->0)
  {
    (pClonk=CreateObject(idDef3,RandomX(-50,50),0,iPlr))->~Call(Format("Set%sAI",szAI));
    pClonk->~ChangedTo();
    if(g_fShouldFollow[GetPlayerID(iPlr)])
      pClonk->SetAIMode(TWRATK_Cmd_Follow,GetCursor(iPlr));
  }
  DoWealth(iPlr,-iCost);
}

func HireHero(idDef,iCost,iPlr,szAI)
{
  if(!szAI)
    szAI="Bulk";
  if(GetWealth(iPlr) < iCost)
  {
    PlayerMessage(iPlr,"$NotEnoughMoney$",this);
    return(1);
  }
  var pClonk=CreateObject(idDef,0,0,iPlr);
  pClonk->~Call(Format("Set%sAI",szAI));
  DoWealth(iPlr,-iCost);
  DoEnergy(100,pClonk);
}

func HireGeneral(idDef,iCost,iPlr)
{
  if(GetWealth(iPlr) < iCost)
  {
    PlayerMessage(iPlr,"$NotEnoughMoney$",this);
    return(1);
  }
  var pClonk=CreateObject(idDef,0,0,iPlr);
  DoWealth(iPlr,-iCost);
  MakeCrewMember(pClonk,iPlr);
  DoEnergy(100,pClonk);
}

func IncLives(iPlr,fNoMoney)
{
  if(!fNoMoney)
  {
    if(GetWealth(iPlr) < 200)
    {
      PlayerMessage(iPlr,"$NotEnoughMoney$",this);
      return(1);
    }
    DoWealth(iPlr,-200);
  }
  TWRATKChangeLP(GetPlayerTeam(iPlr),1);
}

func IncTroopStr(iPlr,fNoMoney)
{
  if(!fNoMoney)
  {
    if(GetWealth(iPlr) < 100)
    {
      PlayerMessage(iPlr,"$NotEnoughMoney$",this);
      return(1);
    }
    DoWealth(iPlr,-100);
  }
  g_aStrength[GetPlayerTeam(iPlr)]++;
}

func IncTroopLimit(iPlr,fNoMoney)
{
  if(!fNoMoney)
  {
    if(GetWealth(iPlr) < 100)
    {
      PlayerMessage(iPlr,"$NotEnoughMoney$",this);
      return(1);
    }
    DoWealth(iPlr,-100);
  }
  g_aArmyAllowed[GetPlayerTeam(iPlr)]++;
}

global func SetArmyMode(iPlr,iMode)
{
  g_aArmyMode[iPlr]=iMode;
}

func CanBeBuild(pClonk)
{
  return true;
}

func Collection(pObj)
{
  Sell(GetOwner(FindObject2(Find_Action("Push"),Find_ActionTarget(this))),pObj);
}

func NoAIBuild(pClonk,iMode,iX,iY)
{
  if(FindObject2(Find_ID(COBS),Find_Distance(300,iX,iY),Find_Allied(GetOwner(pClonk))))
    return true;
  return Random(3+ObjectCount2(Find_ID(COBS),Find_Allied(GetOwner(pClonk)))*2-(iMode==TWRATCK_AIMode_Expand));
}

func IsSpecialBuilding()
{
  return true;
}
