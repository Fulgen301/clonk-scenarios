/*--- Flint ---*/

#strict

local iHit;

protected func Hit()
{
if(!iHit) {
 iHit++;
 Schedule("Hit()",30);
 SetSpeed(GetXDir()/3,-130);
 Sound("Boing");
 return(0);
}
if(!iHit) return(0);
Sound("DeEnergize");
for(var i = 180-45; i <=180+45; i+=5) {
 LaunchLightning(GetX(), GetY()+2, Sin(-i,30), 15, -Cos(-i,30), 21);
 }
 CastObjects(SPRK,RandomX(5,18),RandomX(20,50));

RemoveObject();

}

/* Kann in der Chemiefabrik hergestellt werden */
public func IsChemicalProduct() { return(1); }