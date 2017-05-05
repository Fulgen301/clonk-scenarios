/*-- Schmetterling --*/

#strict

local iLastDamager;

protected func Initialize() {
  SetAction("Fly");
  MoveToTarget();
  return(1);
}

/* TimerCall */

private func Activity() {
  if(GetEnergy() <= 0) Death();
  // Unterwasser
  if (InLiquid()) return(SetComDir(COMD_Up()));
  // Sitzt: warten
  if (SEqual(GetAction(),"Sit")) return(1);
  // Neues Ziel
  if (Or( Not(GetCommand()), Not(Random(5)) )) MoveToTarget();
  return(1);
 }
/* Bewegung */

public func Death() 
{
  GameCallEx("Buttercake",this,GetKiller(this));
  Sound("Rip");

  var iCount = 4+Random(4);

  for(var i = 0; i < iCount; i++)
  {
    var wing = CreateObject(_BTW,RandomX(-2,2),0,-1);
    if(!Random(3)) wing->~Set(2);
  }

  RemoveObject(this);
}

private func Flying() {
  // Richtung anpassen
  if (GreaterThan(GetXDir())) SetDir(DIR_Right());
  if (LessThan(GetXDir())) SetDir(DIR_Left());
  // Aktion ändern
  if (Not(Random(3))) SetAction("Flutter");
  return(1);
 }
private func Fluttering(){
  // Richtung anpassen
  if (GreaterThan(GetXDir())) SetDir(DIR_Right());
  if (LessThan(GetXDir())) SetDir(DIR_Left());
  // Aktion ändern
  if (Not(Random(7))) SetAction("Fly");
  return(1);
 }

/* Kontakt */

protected func ContactBottom() {
  SetCommand(this(),"None");
  SetComDir(COMD_Up());
  return(1);
 }
public func SitDown() {
  SetXDir(0);
  SetYDir(0);
  SetComDir(COMD_Stop());
  SetAction("Sit");
  SetCommand(0,"None");
  return(1);
}
public func TakeOff(){
  SetComDir(COMD_Up());
  return(1);
}
private func MoveToTarget() {
  SetVar(0,Random(LandscapeWidth()));
  SetVar(1,Sum(Random(Sum(GetHorizonHeight(Var(0)),-60)),+30));
  SetCommand(this(),"MoveTo",0,Var(0),Var(1));
  return(1);
 }
public func GetHorizonHeight() { // int iX
  while (And( LessThan(Var(0),LandscapeHeight()), Not(GBackSemiSolid(Par(0),Var(0))) ))
    SetVar(0,Sum(Var(0),+10));
  return(Var(0));
}
