/* Rakete */

#strict
#include MISS

local iSpeed, iDamage, exploding;
local shooter;

public func Acceleration() { return(10); }
public func MaxTime() { return(100); }
public func MaxSpeed() { return(200); }

private func HitObject(object pObject) {
  exploding = true;
  BlastObjects(GetX(), GetY(), iDamage/2);
  BlastObjects(GetX(), GetY(), iDamage/2);
  for(var i=RandomX(7,10); i>0; --i)
  {
    var obj=CreateObject(CGFR, 0, 0, GetController());
    var xdir = GetXDir()*2/3+RandomX(-30,30);
    var ydir = GetYDir()*2/3+RandomX(-30,30);
    var angle = Angle(0,0,xdir,ydir);

}
  Explode(iDamage,0,0,0,1);

}


public func IsBulletTarget() { return(true); }
public func NoDecoDamage() { return(true); }
public func IsMachine() { return(true); }
