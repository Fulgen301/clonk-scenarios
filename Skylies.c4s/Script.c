/*-- SkyMayhem --*/

#strict

//Anzahl Scriptzeilen eines Szenarios ohne Scripts
static const lines = 35135;
//Debugkonstante. Bei Release bitte auf false stellen.
static const debug = false;

static StartOkay;
static SeaAddon;

/* Start Menu Variabeln */
static idBase;

/* FGOGOGO! */

static iTeam1;
static iTeam2;
static iTeam3;
static iTeam4;
static iTeam5;
static iTeam6;

 static aKills;
 static aValue;
 static aOldScore;
 static aHardcore;
 static aEvaluatedPlr; // Liste der Spieler, die ausgewertet wurden (Was nur am Ende eines Szenarios sein kann!)

static StartRdy;

func Initialize()
{
  if(debug)
  {
    Log("<c ffffff>VORSICHT! Die Debugkonstante ist auf <i>true</i>. Wenn dies nicht beabsichtigt ist, bitte ändern.</c>");
    CreateObject(NMGE);
  }

  StartRdy = 1;
  aKills = [];
  aValue = [];
  aOldScore = [];
  aHardcore = [];
  aEvaluatedPlr = [];
  idBase = HUT3;
  CreateObject(SCOR,0,0,-1);
  CreateObject(SP33,0,0,-1)->Set();
  AddMsgBoardCmd("version","GetSkyMayhemVersionInfo()");
  AddMsgBoardCmd("nospeedeffect","CheckSpeedEffectRemove(%player%)");
  AddMsgBoardCmd("hardcore","CheckHardcore(%player%)");
  AddMsgBoardCmd("Trailer9751","CheckTrailerReward(%player%)");
  return(ScriptGo(1));
}

global func GetSkyMayhemVersionInfo(bool short)
{
  var szVersion = "1.0 We did it! {{HTBM}}";

  if(short) return szVersion;
  Log("<c 007bff>Sky Mayhem</c> {{FREZ}} <c b0ffffff>%s</c>.|By Gecko & Pitri. Supported by Snow, Octagon, Wipfjäger.",szVersion);
}

global func CheckSpeedEffectRemove(int iPlr)
{
  if(iPlr > 0) return false;
  Log("<System> Host removed Speedeffect. {{FGOB}}");
  RemoveAll(SP33);
}
global func CheckTrailerReward(int iPlr)
{
  var pMedal = FindObject(TY_M);
  if(pMedal)
   Reward(pMedal,iPlr);
}

global func CheckHardcore(int iPlr)
{
  if(FindObject(HCOR) || !GetCrew(iPlr))
    return false;

  var allPlr;
  for(var i=0; i<GetPlayerCount(); i++)
  {
    var iPlr = GetPlayerByIndex(i);
    if(GetCrew(iPlr)) allPlr++;
  }

  //kleine Änderung: Der erste Spieler, der Hardcore ausruft, bekommt eine 2 (Rage-Medaille)
  if(!PartOf(2,aHardcore) && !PartOf(1,aHardcore))
    aHardcore[iPlr] = 2;
  else aHardcore[iPlr] = 1;

  var HardcoreOkay;
  for(var i2=0; i2< allPlr; i2++)
    if(aHardcore[i2])
      HardcoreOkay++;

  if(HardcoreOkay == allPlr)
  {
    if(!FindObject(HCOR))CreateObject(HCOR,0,0,-1);
    Log("$TxtHC2$ {{IR0D}}",GetTaggedPlayerName(iPlr));
  }

  else Log("$TxtHC1$ {{IR0D}}",GetTaggedPlayerName(iPlr),HardcoreOkay,allPlr);
}

func Script5()
{
  if(GetCursor())
  {
    if(GetCursor(0)->~GetMenu() != FLYF)
    {
      CreateMenu(FLYF,GetCursor(0),GetCursor(0),0,"Spiel Optionen",1,1);
      AddMenuItem("<c 88ffffff>Menü zeigt aktuelle Auswahl.</c>",0,FREZ,GetCursor(0));
      if(FindObject(ENRG)) AddMenuItem("Strombedarf An","MenuStrom()",ENRG,GetCursor(0));
      if(!FindObject(ENRG)) AddMenuItem("Strombedarf Aus","MenuStrom()",ENRG,GetCursor(0));
      if(idBase == HUT3) AddMenuItem("Startbasis: Steinhütte","MenuBase()",HUT3,GetCursor(0));
      if(idBase == CST2) AddMenuItem("Startbasis: Burg","MenuBase()",CST2,GetCursor(0));
      if(idBase == WZKP) AddMenuItem("Startbasis: Zauberkastel","MenuBase()",WZKP,GetCursor(0));
      if(!SeaAddon) AddMenuItem("Spielmodi: Classic","MenuAddon()",BLMP,GetCursor(0));
      if(SeaAddon) AddMenuItem("Spielmodi: Sea Crisis Addon","MenuAddon()",SLBT,GetCursor(0));
      AddMenuItem("Start!","MenuStart()",FREZ,GetCursor(0));
      AddMenuItem(Format("<c 88ffffff>v. %s</c>",GetSkyMayhemVersionInfo(1)),0,SP33,GetCursor(0));
    }
  }
}
global func MenuStart() {
StartOkay = true;
ShowMessage("Der Host ist fertig und es kann gespielt werden!");
goto(9);
}
global func MenuStrom() {
if(!FindObject(ENRG)){
CreateObject(ENRG);
ShowMessage("Strombedarf:{{ENRG}} An!");
Sound("Electric",1);
}
else {
RemoveAll(ENRG);
ShowMessage("Strombedarf:{{ENRG}} Aus!");
Sound("DeEnergize",1);
}
goto(5);
}
global func MenuAddon() {
if(SeaAddon){
SeaAddon = 0;
ShowMessage("Spielmodi:{{BLMB}} Classical Sky Mayhem!");
Sound("MagicElementAir",1);
}
else {
SeaAddon = 1;
ShowMessage("Spielmodi:{{SLBT}} Sea Crisis Addon!");
Sound("Splash*",1);
}
goto(5);
}
global func MenuBase() {

if(idBase == WZKP){
idBase = HUT3;
ShowMessage("Startbasis {{HUT3}}!");
Sound("Build*",1);
goto(5);
return(0);
}

if(idBase == HUT3){
idBase = CST2;
ShowMessage("Startbasis {{CST2}}!");
Sound("Build*",1);
goto(5);
return(0);
}

if(idBase == CST2){
idBase = WZKP;
ShowMessage("Startbasis {{WZKP}}!");
Sound("Build*",1);
goto(5);
return(0);
}

}

func Script9() {
if(!StartOkay) goto(2);
}
func Script10() {
if(SeaAddon){ AddSeaAddon(); }

// Alle Spieler durchgehen
  for(var i = 0; i < GetPlayerCount(); ++ i)
  {
 var iPlr = GetPlayerByIndex(i);
  SkylandPlayer(iPlr);
   }

   if(!SeaAddon)
     PlaceDekoSkylands(7, 300, 1000);
}
func Script15() {
 CreateObject(TIMZ,0,0,-1);
}
func Script100(){
 SetMaxPlayer(0);
}
func Script500()
{
  RemoveAll(FRCA);
  GameCallEx("ForceFieldRemove");

  var pButterfly = CreateObject(_BTF,RandomX(0,LandscapeWidth()),20,-1);
  AddEffect("FadeIn",pButterfly,100,1);
}

func MedalFulfil()
{
     for(var i = 0; i < GetPlayerCount(); ++ i)
      {
      var iPlr = GetPlayerByIndex(i);
      if(GetCrew(iPlr)){ // Clonk? Also am Leben? Okay.
        PlayerEvaluation(iPlr);
       }
      }
  return(1);
}

public func PlayerEvaluation(int iPlr){
if(!aEvaluatedPlr[iPlr]){
 aEvaluatedPlr[iPlr] = true; // Nicht nochmal machen.
 AddEvaluationData(Format("Medailien von %s:%s",GetTaggedPlayerName(iPlr),ListMedals(iPlr)));
 AddEvaluationData(Format("{{MELE}}%d Kills", aKills[iPlr]),GetPlayerID(iPlr));
 AddEvaluationData(Format("{{GLDM}}%d Killvalue", aValue[iPlr]),GetPlayerID(iPlr));
 AddEvaluationData(Format("{{SCOR}}%d Score(%d)|", GetGeckoScore(iPlr),GetGeckoScore(iPlr)-aOldScore[iPlr]),GetPlayerID(iPlr));
 }
}

func InitializePlayer(int iPlr) {
 var c1 = GetCrew(iPlr);  var c2 = GetCrew(iPlr,1); var c3 = GetCrew(iPlr,2);
 SetWealth(iPlr,GetWealth(iPlr)+80); var doof; var y;
 var team = GetPlayerTeam(iPlr);
 aValue[iPlr] = 0;
 aKills[iPlr] = 0;
 aEvaluatedPlr[iPlr] = false; // Schonmal da gewesen? Naja. Dann wollen wir auch am ende updaten.
 ScoreInitPlayer(iPlr);
 UpdateScoreboard(iPlr);
 Enter(CreateObject(FLYF,RandomX(100,LandscapeWidth()-100),LandscapeHeight()/2),c1,-1);
 Enter(CreateObject(FLYF,RandomX(100,LandscapeWidth()-100),LandscapeHeight()/2),c2,-1);
 Enter(CreateObject(FLYF,RandomX(100,LandscapeWidth()-100),LandscapeHeight()/2),c3,-1);

 if(ScriptCounter() >= 10) SkylandPlayer(iPlr);

  return(1);
}
public func SkylandPlayer(int iPlr) {

 var c1 = GetCrew(iPlr);  var c2 = GetCrew(iPlr,1); var c3 = GetCrew(iPlr,2);
 var doof; var y;
 var team = GetPlayerTeam(iPlr);
 var x = RandomX(750,850)*team;

 Exit(c1);
 Exit(c2);
 Exit(c3);

 if(team == 1){ if(iTeam1) doof = 1; y = iTeam1; }
 if(team == 2){ if(iTeam2) doof = 1; y = iTeam2; }
 if(team == 3){ if(iTeam3) doof = 1; y = iTeam3; }
 if(team == 4){ if(iTeam4) doof = 1; y = iTeam4; }
 if(team == 5){ if(iTeam5) doof = 1; y = iTeam5; }
 if(team == 6){ if(iTeam6) doof = 1; y = iTeam6; }


 if(doof){

 SetPosition(x,y-20,c1);
 SetPosition(x,y-20,c2);
 SetPosition(x,y-20,c3);

 }
 if(team == 1) if(iTeam1) return(0);
 if(team == 2) if(iTeam2) return(0);
 if(team == 3) if(iTeam3) return(0);
 if(team == 4) if(iTeam4) return(0);
 if(team == 5) if(iTeam5) return(0);
 if(team == 6) if(iTeam6) return(0);
 if(!doof) y = RandomX(160,500);

 if(SeaAddon) y = 360;

 CreateContents(FLAG,c1);
 CreateObject(SKYL,x,y+40,iPlr)->CreatePlayerIsland();
 if(team == 1) iTeam1 = y;
 if(team == 2) iTeam2 = y;
 if(team == 3) iTeam3 = y;
 if(team == 4) iTeam4 = y;
 if(team == 5) iTeam5 = y;
 if(team == 6) iTeam6 = y;

 var pSkyland = FindObject2(Find_ID(SKYL),Find_Allied(iPlr));

 if(pSkyland){ if(pSkyland->~GetHouse()){ x = GetX(pSkyland->~GetHouse()); y = GetY(pSkyland->~GetHouse());  }  }

 SetPosition(x,y-20,c1);
 SetPosition(x,y-20,c2);
 SetPosition(x,y-20,c3);
 }

public func RelaunchPlayer(int iPlr){
if(GetPlayerName(iPlr)){
ShowMessage("%s {{%i}}", Format("<c %x>%s</c>", GetPlrColorDw(iPlr), FilterClanTag(GetPlayerName(iPlr))), RACE);
PlayerEvaluation(iPlr); // Auswertung.
  }
 }

protected func OnClonkDeath(object pClonk, int iKilledBy)  {
  if(iKilledBy == GetOwner(pClonk)) return(0);
  if(iKilledBy == GetOwner(pClonk) || iKilledBy == -1) return(0);
  var pOwner = GetOwner(pClonk);
  var r = Random(3);
  if (!r)   return(Boni(pClonk,iKilledBy,1));
  if (!--r) return(Boni(pClonk,iKilledBy,2));
  if (!--r) return(Boni(pClonk,iKilledBy,3));
}
protected func Boni(object pOpfer,int iLucky,int iMod){
var pLucky = GetCursor(iLucky);
var iOpfer = GetOwner(pOpfer);
if(!Hostile(iLucky,iOpfer)) return(0);
var Mana;
var Heal;
iMod = 2;
 if(iMod == 2){
  Heal = RandomX(20,100);
  SetWealth(iLucky,GetWealth(iLucky)+Heal);
   aValue[iLucky] += Heal;
   aKills[iLucky] += 1;
   AddKill(iLucky,iOpfer);

   /* STEIN SHEREPAPIER MEDAILE */

   if(aKillsBonusTime[iOpfer]){ // Omg dein Opfer hat KillBonus zeit. Das heißt ...
      var pMedal = FindObject(SP_M);
      if(pMedal)
        Reward(pMedal,iLucky);    // Schere-Stein-Papier-Medaille
    }

   /* -- ENDE */

   UpdateScoreboard(iLucky);
   UpdateScoreboard(iOpfer);
 }
  //Bugfix? vorher: if(Heal > 1 & Mana == 0)
  if(Heal > 1 && Mana == 0){
  Message("{{GOLD}} Du hast <c ffcc00>%d Clunker</c> Killbelohnung erhalten.",pLucky,Heal);
  }

}

 /* Sea Addon */
global func AddSeaAddon(){
 DrawMaterialQuad("Water",0,420, LandscapeWidth(),420, LandscapeWidth(),420+1000, 0,420+1000);

 for(var i = 0; i <= 600; i++) {
 CreateObject(QONT,RandomX(0,LandscapeWidth()),LandscapeHeight()-RandomX(0,20))->CreateMyScape();
 var ding2 = CreateObject(QONT,RandomX(0,LandscapeWidth()),LandscapeHeight()-(RandomX(10,50)+RandomX(0,15)),-1);
 ding2->~Set(5,RandomX(5,20),RandomX(0,360),-20,20,12,1,"Sand",1);
 ding2->~CreateMyScape();
   }
 var num;

 num = RandomX(16,20); while(--num) PlaceInMaterial(FISH,Material("Water"),20);
 num = RandomX(10,15); while(--num) PlaceInMaterial(SHRK,Material("Water"),10);

 num = RandomX(2,3);  while(--num) PlaceInMaterial(DANK,Material("Water"),3);
 num = RandomX(7,12); while(--num) PlaceInMaterial(SWD1,Material("Water"),RandomX(5,9));
 num = RandomX(7,12); while(--num) PlaceInMaterial(SWD2,Material("Water"),RandomX(5,9));
 num = RandomX(7,12); while(--num) PlaceInMaterial(SWD3,Material("Water"),RandomX(5,9));
 num = RandomX(7,12); while(--num) PlaceInMaterial(SWD4,Material("Water"),RandomX(5,9));
 num = RandomX(7,12); while(--num) PlaceInMaterial(SWD5,Material("Water"),RandomX(5,9));
 num = RandomX(7,12); while(--num) PlaceInMaterial(SWD6,Material("Water"),RandomX(5,9));
 num = RandomX(7,12); while(--num) PlaceInMaterial(SWD7,Material("Water"),RandomX(5,9));
 num = RandomX(2,5);  while(--num) PlaceInMaterial(SEBL,Material("Water"),RandomX(5,9));
 num = RandomX(2,4);  while(--num) PlaceInMaterial(VSHL,Material("Water"),RandomX(2,4));
 num = RandomX(2,4);  while(--num) PlaceInMaterial(RSHL,Material("Water"),RandomX(2,4));
 num = RandomX(2,4);  while(--num) PlaceInMaterial(SSHL,Material("Water"),RandomX(2,4));
 num = 1;             while(--num) PlaceInMaterial(GSHL,Material("Water"),1);
 num = RandomX(8,16); while(--num) PlaceInMaterial(MSHL,Material("Water"),10);
 num = RandomX(1,2);  while(--num) PlaceInMaterial(BSUB,Material("Water"),1);


 DrawMaterialQuad("Vehicle",0,420, 2,420, 2,420+1000, 0,420+1000);

 DrawMaterialQuad("Vehicle",LandscapeWidth()-2,420, LandscapeWidth(),350, LandscapeWidth(),420+1000, LandscapeWidth()-2,420+1000);

  DrawMaterialQuad("Vehicle",0,LandscapeHeight()-2, LandscapeWidth(),LandscapeHeight()-2,LandscapeWidth(),LandscapeHeight(), 0,LandscapeHeight());

  for(var i=0; i<GetPlayerCount(); i++)
  {
  var iPlr = GetPlayerByIndex(i);

  if(GetCrew(iPlr)) {

  DoHomebaseMaterial(iPlr,ACLK,3);
  DoHomebaseMaterial(iPlr,CLNK,-3);

  if(GetID(GetCrew(iPlr,0)) == CLNK){ GetCrew(iPlr)->ChangeDef(ACLK);
  GetCrew(iPlr)->Initialize();     }
  if(GetID(GetCrew(iPlr,1)) == CLNK){ GetCrew(iPlr,1)->ChangeDef(ACLK);
  GetCrew(iPlr,1)->Initialize();  }
  if(GetID(GetCrew(iPlr,2)) == CLNK){ GetCrew(iPlr,2)->ChangeDef(ACLK);
  GetCrew(iPlr,2)->Initialize(); }

  DoHomebaseMaterial(iPlr,SLBT,1);
  DoHomebaseMaterial(iPlr,TRP1,4);

  DoHomebaseProduction(iPlr,SLBT,1);
  DoHomebaseProduction(iPlr,TRP1,2);
  DoHomebaseProduction(iPlr,SUB1,1);

  DoHomebaseMaterial(iPlr,BJ5P,2);
  DoHomebaseMaterial(iPlr,BH5P,3);

  DoHomebaseProduction(iPlr,SLBT,1);
  DoHomebaseProduction(iPlr,BH5P,1);

  SetPlrKnowledge (iPlr, SUB1);
  SetPlrKnowledge (iPlr, TRP1);
  SetPlrKnowledge (iPlr, SLBT);
  SetPlrKnowledge (iPlr, BJ5P);
  SetPlrKnowledge (iPlr, BH5P);
  SetPlrMagic(iPlr,MVLC,1);
    }
   }
}


func GetMeliorateData()
{
   return [[ORE1,METL,METL,METL,METO],[GUNP,GNBR],[MARW,MARP],[ARWP,FARP,MARP],[WOOD,BLND],[STFN,HTBM],[ADM3,BFLN]];
}

global func FxFadeInStart(object pTarget, int iIndex, int iTemp)
{
  SetClrModulation(NO_OWNER,pTarget); //Enginekonstanten ftw
  return true;
}

global func FxFadeInTimer(object pTarget, int iIndex, int iTime)
{
  if(iTime >= 254)
  {
    SetClrModulation(0xffffff,pTarget);
    return -1;
  }

  SetClrModulation(0xffffff|((255-iTime)<<24),pTarget);
  return true;
}