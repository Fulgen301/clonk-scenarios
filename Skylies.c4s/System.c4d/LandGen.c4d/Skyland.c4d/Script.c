/*-- Neues Objekt --*/

#strict

local iStop;
local iMod;

local pHouse;

local iX;
local iY;
local iCount;

func Initialize() {

  return(1);
}
public func GetHouse()  {
  return(pHouse);
}
func CreatePlayerIsland() {
SetPosition(GetX(),GetY()+30);
CreateObject(FLYF,50,-60,-1);
CreateObject(FLYF,-50,-60,-1);
for(var i = 0; i < 30; i++){
  CreateObject(QONT,RandomX(-200,200),30)->CreateMyScape();
  CreateObject(QONT,RandomX(-180,180),40)->CreateMyScape();
  CreateObject(QONT,RandomX(-160,160),50)->CreateMyScape();
  CreateObject(QONT,RandomX(-160,150),60)->CreateMyScape();
  CreateObject(QONT,RandomX(-150,140),70)->CreateMyScape();
 if(!Random(2)) {
  CreateObject(QONT,RandomX(-120,120),80)->CreateMyScape();
  CreateObject(QONT,RandomX(-100,100),90)->CreateMyScape();
  CreateObject(QONT,RandomX(-80,80),100)->CreateMyScape();
 if(!Random(2)) {
   CreateObject(QONT,RandomX(-40,40),110)->CreateMyScape();
  CreateObject(QONT,RandomX(-10,10),120)->CreateMyScape();
   }
  }
 }
for(var i = 0; i < 50; i++){
 var ding2 = CreateObject(QONT,RandomX(-200,200),10,-1);
 ding2->~Set(5,RandomX(5,20),RandomX(0,360),-20,20,12,1,"Earth",1);
 ding2->~CreateMyScape();
  }
CreateObject(MFFA,0,-40,GetOwner())->Activate(this());

if(!Random(2)){
var burg = CreateConstruction(idBase,RandomX(-10,10),-15,GetOwner(),100,1);
FreeRect(GetX(burg)-32,GetY(burg)-25,+32,+25);
CreateContents(WOOD,burg,5);
CreateContents(METL,burg,5);
CreateContents(LOAM,burg,5);
CreateContents(ROCK,burg,5);
CreateContents(FLNT,burg,5);
var windmill;
if(FindObject(ENRG)){ if(!windmill) windmill = CreateConstruction(WMIL,RandomX(-100,-80), -15,GetOwner(),100,1); }
FreeRect(GetX(windmill)-15,GetY(windmill)-29,+15,+29);
var werk = CreateConstruction(WRKS,RandomX(65,75),-15,GetOwner(),100,1);
FreeRect(GetX(werk)-40,GetY(werk)-25,+40,+25);
CreateContents(WOOD,werk,10);
CreateContents(METL,werk,10);
CreateContents(LOAM,werk,3);
CreateContents(ROCK,werk,10);
CreateContents(LORY,werk,1);
if(FindObject(ENRG)) { CreateObject(LNKT)->CreateLine(PWRL,GetOwner(),windmill, werk);    }
var chemi = CreateConstruction(CHEM,RandomX(100,130),-15,GetOwner(),100,1);
FreeRect(GetX(chemi)-25,GetY(chemi)-28,+25,+28);
FreeRect(GetX()-100,GetY()-50,200,30);
CreateContents(SPHR,chemi,10);
CreateContents(FLNT,chemi,5);
CreateContents(SFLN,chemi,3);
CreateContents(GUNP,chemi,7);
CreateContents(GNBR,chemi,3);
//C4D_LinePower
if(FindObject(ENRG)) { CreateObject(LNKT)->CreateLine(PWRL,GetOwner(),werk, chemi);  }
}
else {
var burg = CreateConstruction(idBase,RandomX(-10,10),-15,GetOwner(),100,1);
FreeRect(GetX(burg)-32,GetY(burg)-25,+32,+25);
CreateContents(WOOD,burg,5);
CreateContents(METL,burg,5);
CreateContents(LOAM,burg,5);
CreateContents(ROCK,burg,5);
CreateContents(FLNT,burg,5);
var windmill;
if(FindObject(ENRG)) { if(!windmill) windmill = CreateConstruction(WMIL,RandomX(80,120), -15,GetOwner(),100,1); }
FreeRect(GetX(windmill)-15,GetY(windmill)-29,+15,+29);
var werk = CreateConstruction(WRKS,RandomX(-65,-75),-15,GetOwner(),100,1);
FreeRect(GetX(werk)-40,GetY(werk)-25,+40,+25);
CreateContents(WOOD,werk,10);
CreateContents(METL,werk,10);
CreateContents(LOAM,werk,3);
CreateContents(ROCK,werk,10);
CreateContents(LORY,werk,1);
if(FindObject(ENRG)) { CreateObject(LNKT)->CreateLine(PWRL,GetOwner(),windmill, werk);   }
var chemi = CreateConstruction(CHEM,RandomX(-100,-130),-15,GetOwner(),100,1);
FreeRect(GetX(chemi)-25,GetY(chemi)-28,+25,+28);
FreeRect(GetX()-100,GetY()-50,200,30);
CreateContents(SPHR,chemi,10);
CreateContents(FLNT,chemi,5);
CreateContents(SFLN,chemi,3);
CreateContents(GUNP,chemi,7);
CreateContents(GNBR,chemi,3);
//C4D_LinePower
if(FindObject(ENRG)) { CreateObject(LNKT)->CreateLine(PWRL,GetOwner(),werk, chemi);     }
}
PlaceObjects (ROCK, RandomX(6,19), "Earth", -200, -100, 400, 500);
PlaceObjects (CNKT, RandomX(1,2), "Earth", -200, -100, 400, 500);
PlaceObjects (FLNT, RandomX(7,15), "Earth", -200, -100, 400, 500);
PlaceObjects (GOLD, RandomX(2,4), "Earth", -200, -100, 400, 500);
PlaceObjects (ZAPN, RandomX(0,2), "Earth", -200, -100, 400, 500);
PlaceObjects (MEGG, RandomX(0,2), "Earth", -200, -100, 400, 500);
PlaceObjects (LOAM, RandomX(6,19), "Earth", -200, -100, 400, 500);
pHouse = burg;
 var r;
r = RandomX(0,2);
for(var i = 0; i < r; i++){
PlaceVegetation(TRE1,-200,-40,400,70,RandomX(80000,100000));
  }
r = RandomX(0,2);
for(var i = 0; i < r; i++){
PlaceVegetation(TRE2,-200,-40,400,70,RandomX(80000,100000));
  }
r = RandomX(0,2);
for(var i = 0; i < r; i++){
PlaceVegetation(TRE3,-200,-40,400,70,RandomX(80000,100000));
  }
PlaceOnLand(VINE, RandomX(12,24), -200, -200, 400, 600, 1);

if(SeaAddon) {
CreateObject(TRTS,0,200,GetOwner());
}

  return(1);
}

func CreateGodIsland() {
 iMod = 2;
  return(1);
}

func CreateNormalIsland() {
CreateObject(FLYF,50,-30,-1);
CreateObject(FLYF,-50,-30,-1);
var r;
for(var i = 0; i < 30; i++){
  CreateObject(QONT,RandomX(-250,250),RandomX(20,40))->CreateMyScape();
  CreateObject(QONT,RandomX(-180,180),RandomX(40,50))->CreateMyScape();
  CreateObject(QONT,RandomX(-160,160),RandomX(50,60))->CreateMyScape();
  CreateObject(QONT,RandomX(-160,150),RandomX(60,70))->CreateMyScape();
  CreateObject(QONT,RandomX(-150,140),RandomX(80,90))->CreateMyScape();
 if(!Random(2)) {
  CreateObject(QONT,RandomX(-120,120),RandomX(90,110))->CreateMyScape();
  CreateObject(QONT,RandomX(-100,100),RandomX(110,125))->CreateMyScape();
  CreateObject(QONT,RandomX(-80,80),RandomX(125,140))->CreateMyScape();
 if(!Random(2)) {
   CreateObject(QONT,RandomX(-40,40),RandomX(140,150))->CreateMyScape();
  CreateObject(QONT,RandomX(-10,10),RandomX(140,145))->CreateMyScape();
   }
  }
 }
for(var i = 0; i < 50; i++){
 var ding2 = CreateObject(QONT,RandomX(-200,200),10,-1);
 ding2->~Set(5,RandomX(5,20),RandomX(0,360),-20,20,12,1,"Earth",1);
 ding2->~CreateMyScape();
  }


PlaceObjects (ROCK, RandomX(6,19), "Earth", -200, -100, 400, 500);
PlaceObjects (LOAM, RandomX(6,19), "Earth", -200, -100, 400, 500);
PlaceObjects (FLNT, RandomX(7,15), "Earth", -200, -100, 400, 500);
PlaceObjects (GOLD, RandomX(2,4), "Earth", -200, -100, 400, 500);

 var r;
r = RandomX(2,7);
for(var i = 0; i < r; i++){
PlaceVegetation(TRE1,-200,-40,400,70,RandomX(80000,100000));
  }
r = RandomX(4,9);
for(var i = 0; i < r; i++){
PlaceVegetation(TRE2,-200,-40,400,70,RandomX(80000,100000));
  }
r = RandomX(2,5);
for(var i = 0; i < r; i++){
PlaceVegetation(TRE3,-200,-40,400,70,RandomX(80000,100000));
  }
PlaceOnLand(VINE, RandomX(12,24), -200, -200, 400, 600, 1);

  return(1);
}
func Grow() {
 if(iMod == 2){ // Gott Insel
 var x = iX+RandomX(-40,40);
 var y = iY+RandomX(-20,20);
 var y2 = iY+20+RandomX(0,15);
 var od = 1;
 var mat = "Crystal";
 if(!Random(2)) mat = "Brick";
 var ir = RandomX(0,360);
 var irnd = 10;
 if(mat S= "Brick") ir = 0;
 if(mat S= "Brick") irnd = 0;
 var ding = CreateObject(QONT,x,y,-1);
 ding->~Set(5,RandomX(10,20),RandomX(0,360),-irnd,irnd,2,1,mat);
 ding->~CreateMyScape();
 var ding2 = CreateObject(QONT,x,y2,-1);
 ding2->~Set(5,RandomX(5,20),RandomX(0,360),-20,20,12,1,"Cloud");
 ding2->~CreateMyScape();
 iCount++;
 //iX = x;
 //iY = y;
// if(!Random(20)) iX = 0;
// if(!Random(20)) iY = 0;
 if(iCount > 40) RemoveObject();
 }
  return(1);
}