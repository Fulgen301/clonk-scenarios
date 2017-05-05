/*-- Neues Objekt --*/

#strict

local iSize;
local stoped;
local Timer;

func Initialize() {
   iSize = RandomX(4,8);
  return(1);
}
public func Check() {
  SetYDir(-10); // Kommen von unten
  SetXDir(RandomX(-20,20));
  if(GBackSolid(0,6)) DestroyLand();
  return(1);
}
public func DestroyLand(){
 var r = GetMaterialColor(GetMaterial(),0,0);
 var g = GetMaterialColor(GetMaterial(),0,1);
 var b = GetMaterialColor(GetMaterial(),0,2);
 
 CreateAScape(this(),"Tunnel",RandomX(0,360),RandomX(5,30),-180,180,1,RandomX(3,18));
 if(GetMaterial()){
 Sound("LandCrackle*");
 for(var i = 0; i <= RandomX(4,16); i++){
 var ding = CreateObject(1EBK,RandomX(-10,10),RandomX(-10,10),-1);
 SetSpeed(RandomX(-15,15),RandomX(5,15),ding);
 SetClrModulation(RGB(r,g,b),ding);
  }
 }
 RemoveObject();
  return(1);
}
