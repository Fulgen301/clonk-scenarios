/*--- Dampfmaschine ---*/

#strict

local a1;
local a2;
local a3;
local a4;
local acounter;

local iTimer;

local ZwangDir;

local iZugSpeed;

func Initialize()
{
var x;
var y=Position()-15;
var Dingdir = GetScenDir();
iZugSpeed = 250;
if(imod) iZugSpeed = 105;
ZwangDir = Dingdir;
    if(!Dingdir){x=LandscapeWidth()-20; }
    if(Dingdir) {x=30; }
    SetPosition(x,y);
    if(Dingdir==0){ SetDir(0); SetComDir(COMD_Left()); }
    if(Dingdir==1){ SetDir(1); SetComDir(COMD_Right()); }
    SetAction("Fly");
    CreateWaggons();
    SetPhysical("Float", iZugSpeed, PHYS_Temporary, a4); 
   if(!imod){ CreateObject(QSMI,0,0,-1)->Set(this()); }    if(imod){ if(!Random(3)) CreateObject(QSMI,0,0,-1)->Set(this()); }
  for(var obj in FindObjects(Find_ID(STMG),Find_Exclude(this()))){
     if(!imod){ 
     if(GetY(obj) == GetY()){ RemoveObject();
     }
     }
    if(imod){ 
     if(GetY(obj) == GetY()){ if(ObjectDistance(this(),obj) < 80){ RemoveObject(); } 
     } 
        }
     }
 
}
func CreateWaggons(){
if(!imod) Sound("TrainHorn",1,0,70);
if(imod){ if(!Random(20)) Sound("TrainHorn",1,0,70); }
}
public func Check(){
iTimer++;
if(iTimer > 2){

if(!a1){ CreateDingens("a1"); }
if(!a2){ CreateDingens("a2"); }
if(!a3){ CreateDingens("a3"); }
if(!a4){ CreateDingens("a4"); } 

}
var xdir;
if(!GetDir()){ xdir = -75; }
if(GetDir()){ xdir = +75; }
SetXDir(xdir);
if(!imod) SetDir(GetScenDir());
if(imod) SetDir(ZwangDir);
 if(!Random(3)) CreateParticle("PSpark",RandomX(-12,12),14,0,0,80,RGB(255,100,0));
if(!Random(150)){  TrainAbwurf();  }
var x;
if(GetDir() == 0){ x = -15; }
if(GetDir() == 1){ x = +15; }
if(!Random(5)){
Smoke(-5, -14, 5 + Random(4));
 }
var pOpfer = FindObject2(Find_ID(WAGN),Find_AtPoint (x, 12));
if(pOpfer) {
 pOpfer->~Crush();
 
 }
var pOpfer2 = FindObject2(Find_ID(STMG),Find_AtPoint (x, 12),Find_Exclude(this()));
if(pOpfer2) {
  pOpfer2->~Crush();
  Crush();
 } 
}
public func Crush() {
 
 RemoveObject();
 if(a1) SetPhysical("Float", 35, PHYS_Temporary, a1);
 if(a2) SetPhysical("Float", 35, PHYS_Temporary, a2);
 if(a3) SetPhysical("Float", 35, PHYS_Temporary, a3);
 if(a4) SetPhysical("Float", 35, PHYS_Temporary, a4);
}
public func CreateDingens(string bla){
var xdir;
if(GetDir() == 0){ xdir = -75; }
if(GetDir() == 1){ xdir = +75; }
if(acounter > 4){ iTimer = -50; }
if(bla S= "a1"){
 a1 = CreateObject(WAGN,-35*(GetDir()*2-1),14,-1);
 SetXDir(xdir,a1); 
 SetPhysical("Float", iZugSpeed, PHYS_Temporary, a1);
 acounter++;
  }
if(bla S= "a2"){
 a2 = CreateObject(WAGN,-75*(GetDir()*2-1),14,-1);
 SetXDir(xdir,a2); 
 SetPhysical("Float", iZugSpeed, PHYS_Temporary, a2);
 acounter++;
  }
if(bla S= "a3"){
 a3 = CreateObject(WAGN,-115*(GetDir()*2-1),14,-1);
 SetXDir(xdir,a3); 
 SetPhysical("Float", iZugSpeed, PHYS_Temporary, a3);
 acounter++;
  }
if(bla S= "a4"){
 a4 = CreateObject(WAGN,-155*(GetDir()*2-1),14,-1);
 SetXDir(xdir,a4); 
 SetPhysical("Float", iZugSpeed, PHYS_Temporary, a4);
 acounter++;
  }


}
public func TrainAbwurf(int ignore){
if(imod){ return(0); }
if(a4){ SetPhysical("Float", 35, PHYS_Temporary, a4); a4 = 0; iTimer = -15; return(0); }
if(!a4){
 if(a3){ SetPhysical("Float", 35, PHYS_Temporary, a3); a3 = 0; iTimer = -15; return(0);  }
  if(!a3){ if(a2){ SetPhysical("Float", 35, PHYS_Temporary, a2); a2 = 0; iTimer = -15; return(0);  } 
   if(!a2){ if(a1){ SetPhysical("Float", 35, PHYS_Temporary, a1); a1 = 0; iTimer = -15; return(0);  } 
   }
  }
 }
}
