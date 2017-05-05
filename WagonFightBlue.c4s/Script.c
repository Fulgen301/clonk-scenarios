/*-- Wagon Fight Blue --*/

#strict
static dir,menu;

func Initialize() {
   for(var i; i < 100; i++)
   {
   var wag=CreateObject(WAGN,Random(LandscapeWidth()),Position(),-1);
   if(wag)wag->Set(dir);
   }
   
   for(var i; i < 50; i++)
   {
   var wag=CreateObject(WAGN,Random(LandscapeWidth()/3),Position(),-1)->Set(dir);
   if(wag)wag->Set(dir);
   }
  CreateObject(_SPK, LandscapeWidth()/2 ,-5, -1)->SetAction("Wait");
  //CreateObject(_ETG);
  
  for(var u; u < 8; u++)
  {
  
  var y=Position();
 var x = Random(Random(LandscapeWidth() / 2 - 25));
 CreateObject(_SPK, LandscapeWidth()/2+x-GetX(),y-20, -1);
 CreateObject(_SPK, LandscapeWidth()/2-x-GetX(),y-20, -1);
 
 }
   ScriptGo(1);
   
 SetScoreboardData(SBRD_Caption,  SBRD_Caption, "<c ff0000>Lives</c>", 0);
 SetScoreboardData(SBRD_Caption,             1,       Format("{{KNIG}}"),                          0);
 SetScoreboardData(SBRD_Caption,             2,       Format("{{WBRL}}"),                          0);
 SetScoreboardData(SBRD_Caption,             3,       Format("{{ARWP}}"),                          0);
   
   SetSkyParallax(0,15,15);
   
   Schedule("SetMaxPlayer(0)",10,0);
  return(1);
}

func InitializePlayer(iPlr)
{
var wipf=PlaceAnimal(WIPF);
while(GetX(wipf) < 300 || GetX(wipf) > LandscapeWidth()-300 || GetY(wipf) > LandscapeHeight()-200 || FindObject(WAGN,GetX(wipf)-10,GetY(wipf)-1,20,2)){ RemoveObject(wipf); wipf=PlaceAnimal(WIPF); }
  
SetPosition(GetX(wipf),GetY(wipf)+3,GetCrew(iPlr));
RemoveObject(wipf);
CreateObject(WAGN,GetX(GetCrew(iPlr)),GetY(GetCrew(iPlr))+34,-1)->Fade();
CreateObject(WAGN,GetX(GetCrew(iPlr))+40,GetY(GetCrew(iPlr))+34,-1)->Fade();
CreateObject(WAGN,GetX(GetCrew(iPlr))-40,GetY(GetCrew(iPlr))+34,-1)->Fade();
SetFoW(0,iPlr);
InitScoreboard(iPlr);
DoScoreboardShow(1,iPlr);
//if(!menu)if(iPlr==0)Menu();
}

func Menu()
{
menu=1;
CreateMenu(GOLD,GetCrew(0),0,0,"foo");
AddMenuItem("Normal","Normal",WOOD,GetCrew(0),0,0,"Normal und toll");
AddMenuItem("Doof","Doof",ROCK,GetCrew(0),0,0,"Nicht normal und doof");
}

func Normal()
{
return();
}

func Doof()
{
if(GetEffect("Disco")) { RemoveEffect("Disco"); SetSkyAdjust(RGB(255,255,255)); return(1); }
AddEffect("Disco",0,20,1);
}

global func FxDiscoTimer(pTarget, iNumber)
{
EffectVar(0,pTarget,iNumber)++;
SetSkyAdjust(HSL(EffectVar(0,pTarget,iNumber),255,128));
}

protected func RemovePlayer(iPlr)
 { 
  InitScoreboard(iPlr,1,LocalN("Kills",GetCrew(iPlr))); 
 }

func RelaunchPlayer(iPlr,iClonk,iRelaunchs, iKiller, iKills)
{
/*if(iKiller!=NO_OWNER && iKiller!=iPlr) {
CreateContents(COKI,GetCrew(iKiller));
if(FindContents(COKI,GetCrew(iKiller)))ScrollContents(GetCrew(iKiller));
}*/
if(iKiller!=NO_OWNER && iKiller!=iPlr && GetPlayerTeam(iKiller) != GetPlayerTeam(iPlr))if(GetCrew(iKiller)) { CreateContents(SFLN,GetCrew(iKiller)); ShiftContents(GetCrew(iKiller)); LocalN("Kills",GetCrew(iKiller))++; InitScoreboard(iKiller); } 
//if(iKiller!=NO_OWNER || iKiller==iPlr || GetPlayerTeam(iKiller) == GetPlayerTeam(iPlr)) { LocalN("Kills",GetCursor(iKiller))--; InitScoreboard(iKiller); } 

var i;
  if(iKiller==NO_OWNER || iKiller==iPlr)if(LocalN("Relaunchs",iClonk)==2) { Log("$NoRelaunch$", GetTaggedPlayerName(iPlr)); InitScoreboard(iPlr,1,iKills); return(0); }
  if(iKiller!=NO_OWNER && iKiller!=iPlr)if(LocalN("Relaunchs",iClonk)==2) { Log("$NoRelaunchWithKiller$", GetTaggedPlayerName(iPlr), GetTaggedPlayerName(iKiller)); InitScoreboard(iPlr,1,iKills); return(0); }
  
  
  
var wipf=PlaceAnimal(WIPF);
while(GetX(wipf) < 300 || GetX(wipf) > LandscapeWidth()-300 || GetY(wipf) > LandscapeHeight()-200 || FindObject(WAGN,GetX(wipf)-10,GetY(wipf)-1,20,2)){ RemoveObject(wipf); wipf=PlaceAnimal(WIPF); }


var clnk=CreateObject(KNIG,GetX(wipf),GetY(wipf)+3,iPlr);
MakeCrewMember(clnk,iPlr);
RemoveObject(wipf);

LocalN("Relaunchs",clnk)=iRelaunchs+=1;
LocalN("Kills",clnk)=iKills;
if(iKiller==NO_OWNER || iKiller==iPlr)Log("$Relaunch$", GetTaggedPlayerName(iPlr),2-LocalN("Relaunchs",clnk));
if(iKiller!=NO_OWNER && iKiller!=iPlr)Log("$RelaunchWithKiller$", GetTaggedPlayerName(iPlr),2-LocalN("Relaunchs",clnk),GetTaggedPlayerName(iKiller));

DoEnergy(100,clnk);
SelectCrew(iPlr,clnk);
SetPosition(GetX(clnk),GetY(clnk)+10,clnk);


CreateObject(WAGN,GetX(clnk),GetY(clnk)+34,-1)->Fade();
CreateObject(WAGN,GetX(clnk)+40,GetY(clnk)+34,-1)->Fade();
CreateObject(WAGN,GetX(clnk)-40,GetY(clnk)+34,-1)->Fade();
AddEffect("Spawn",clnk,20,1);

InitScoreboard(iPlr);
}

func Script1()
{
NewWagon();
}

global func NewWagon()
{
//CreateObject(WAGN,LandscapeWidth()-20,RandomX(LandscapeHeight()))->Set(0);
var wag;
if(!dir)wag=CreateObject(WAGN,LandscapeWidth()-20,Position(),-1);
if(dir)wag=CreateObject(WAGN,20,Position(),-1);
if(wag)wag->Set(dir);

if(!Random(15))CreateObject(FBMP,Random(LandscapeWidth()),0,-1);
//if(!Random(15))CreateObject(BLNK,Random(LandscapeWidth()),8,-1);

/*for(var obj in FindObjects(Find_ID(KNIG)))
{
 //Camper ganz oben? Kusch.
 //if(GetY(obj) < 25)if(!Random(20))CreateObject(FBMP,GetX(obj)+RandomX(-35,35),0,-1);
 //Camper überhaupt? Kusch.
 if(!Random(15))if(GetActTime(obj) > 160)CreateObject(FBMP,GetX(obj)+RandomX(-35,35),0,-1);
}*/

if(!Random(150))ChangeDir();
}

global func ChangeDir()
{
if(dir==0)dir=1;
else { dir=0; }

for(var i in FindObjects(Find_ID(WAGN)))
 {
 i->Set(dir);
 }
}

func Script3()
{
goto(1);
}

global func Position()
{
var y;
var i=Random(7);
if(!i)y=50;
if(!--i)y=100;
if(!--i)y=150;
if(!--i)y=200;
if(!--i)y=250;
if(!--i)y=300;
if(!--i)y=350;
if(!--i)y=400;
return(y);
}

//Spawnschutz 
global func FxSpawnTimer(pTarget, iEffectNumber,iEffectTime)
 {
  EffectVar(3,pTarget,iEffectNumber)+=5;

  
  if(EffectVar(0,pTarget,iEffectNumber) <= 0)EffectVar(1,pTarget,iEffectNumber)=3;
  if(EffectVar(0,pTarget,iEffectNumber) >= 40)EffectVar(1,pTarget,iEffectNumber)=-3;
  
  
  if(Contained(pTarget))return(0);
  //if(++EffectVar(0,pTarget,iEffectTime)>100)return(-1);
  if(iEffectTime > 150) { /*AddEffect("Normal",pTarget,20,1,0,0,EffectVar(0,pTarget,iEffectNumber));*/ SetClrModulation(RGB(255,255,255),pTarget); return(-1); }
  
  //CreateParticle("PSpark",GetX(pTarget)+Cos(EffectVar(3,pTarget,iEffectNumber),20),GetY(pTarget)+Sin(EffectVar(3,pTarget,iEffectNumber),20),GetXDir(pTarget)-Cos(EffectVar(3,pTarget,iEffectNumber),20)/3,GetYDir(pTarget)-Sin(EffectVar(3,pTarget,iEffectNumber),20)/3,30,HSL(EffectVar(0,pTarget,iEffectNumber),255,128));
  //CreateParticle("PSpark",GetX(pTarget)+Cos(EffectVar(3,pTarget,iEffectNumber)-180,20),GetY(pTarget)+Sin(EffectVar(3,pTarget,iEffectNumber)-180,20),GetXDir(pTarget)-Cos(EffectVar(3,pTarget,iEffectNumber)+180,20)/3,GetYDir(pTarget)-Sin(EffectVar(3,pTarget,iEffectNumber)+180,20)/3,30,HSL(EffectVar(0,pTarget,iEffectNumber),255,128));
  CreateParticle("PSpark",GetX(pTarget)+Cos(EffectVar(3,pTarget,iEffectNumber),10),GetY(pTarget)+Sin(EffectVar(3,pTarget,iEffectNumber),10),0,0,30,HSL(EffectVar(0,pTarget,iEffectNumber),255,128));
  CreateParticle("PSpark",GetX(pTarget)+Cos(EffectVar(3,pTarget,iEffectNumber)-180,10),GetY(pTarget)+Sin(EffectVar(3,pTarget,iEffectNumber)-180,10),0,0,30,HSL(EffectVar(0,pTarget,iEffectNumber),255,128));
  SetClrModulation(HSL(EffectVar(0,pTarget,iEffectNumber),255,128),pTarget);
  
  EffectVar(0,pTarget,iEffectNumber)+=EffectVar(1,pTarget,iEffectNumber);
  Extinguish(pTarget);
 }

global func FxSpawnDamage(pTarget, iEffectNumber,foo,iCause)
 {
  return(0);
 }

global func InitScoreboard(int iPlr, bool Dead, int iKills)
{
 
if(Dead) {
 SetScoreboardData(iPlr, 1, Format("%s",GetTaggedPlayerName(iPlr)), LocalN("Relaunchs",GetCrew(iPlr)));
 SetScoreboardData(iPlr, 2, "{{SKUL}}", 999);
 SetScoreboardData(iPlr, 3, Format("%d",iKills), iKills);
 
 SortScoreboard(3,1);
 SortScoreboard(2);
 return();
}
 
 
 SetScoreboardData(iPlr, 1, Format("%s",GetTaggedPlayerName(iPlr)), 0);
 SetScoreboardData(iPlr, 2, Format("%d",2-LocalN("Relaunchs",GetCrew(iPlr))), LocalN("Relaunchs",GetCrew(iPlr))+1);
 SetScoreboardData(iPlr, 3, Format("%d",LocalN("Kills",GetCrew(iPlr))), LocalN("Kills",GetCrew(iPlr)));
 SortScoreboard(3,1);
 SortScoreboard(2);
}

//CastObjects mit Owner
global func CastObjects2(id ID, int iCount, int iLevel, int iX, int iY, int iOwner)
{
 for(var i=0; i < iCount; i++)
 {
  var obj=CreateObject(ID,iX,iY,iOwner);
  SetXDir(RandomX(-iLevel,+iLevel),obj);
  SetYDir(RandomX(-iLevel,+iLevel),obj);
  SetController(GetOwner(obj),obj);
 }
}
