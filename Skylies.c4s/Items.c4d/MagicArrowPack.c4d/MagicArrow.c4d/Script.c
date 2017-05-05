/*-- Sprengpfeil --*/

#strict

#include ARRW

local Armed;

/* Abfeuern */

public func Launch(object pByObject)
{
  // Der Sprengpfeil wird nur durch korrektes Abfeuern scharf gemacht
  Armed = 1;    
  return(_inherited() );
}

/* Pfeileigenschaften */
public func PackTo() {  return(MARP); }
public func ArrowStrength() { return(3+Random(2)); }
public func ArrowTumbleRandom() {return(2);}
public func ArrowStopsOnHit() { return(0); }

/* Aufschlag */

protected func Hit()
{
  if (Armed){
  Sound("Crystal*");
  CastParticles("PxSpark", 20,30, 0,-3, 70, 100, RGBa(100,100,250,0));
  
    for(var i = 0; i <= 36; i++)
    {
    var dwClr;
    dwClr = RGB(RandomX(1,40),RandomX(1,40),200+RandomX(1,50));
    var dwClr1 = RGB(RandomX(1,50),RandomX(1,50),200+RandomX(1,50));
    CreateParticle("PxSpark", 0, 0, Sin(i*10,30),Cos(i*10,30), Random(150)+20,dwClr);
    CreateParticle("PxSpark", 0, 0, Cos(i*10,30), Sin(i*10,30), Random(150)+20,dwClr1);     
    }
  for(var i=0; i < 360; i+=4){
    CreateParticle("PSpark",Cos(i,30),Sin(i,30),0,0,50,RGB(0,120,255));
  }   
  
  for(var pObj in FindObjects(Find_OCF(OCF_CrewMember), Find_OCF(OCF_Alive), Find_Distance(30), Find_Not(Find_Owner(-1))))
  {
    Fling(pObj, -3+6*(GetX(pObj)>GetX()), -2);
    DoEnergy(-RandomX(7,14), pObj);
  }
  RemoveObject();
 } 
}

/* Treffer */

private func HitTarget(pTarget)
{
 if(pTarget->~IsArrowTarget(this())) return(Hit());
 
 return(_inherited(pTarget));
}
