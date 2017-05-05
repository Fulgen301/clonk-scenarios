/*-- Holzfaﬂ --*/

#strict

/* TimerCall */

private func Check()
{
 if(Contained()) {
 if(GetID(Contained()) ==CANN) {
 CreateContents(GUNP,Contained(),3);
 RemoveObject(this());
   }
 }

  return(1);
}

/* Aufschlag */

protected func Hit()
{
  Sound("Woodbarrel");
  //BarrelEject();
  return(1);
}
protected func Hit3()
{
  Sound("Woodbarrel");
  if(!Random(3)) {
  for(var i = 0; i < 3; i++){
  var doof = CreateObject(GUNP,0,0,GetOwner());
  SetSpeed(GetXDir()+RandomX(-5,5),GetYDir()-RandomX(0,12),doof);
  }
  RemoveObject();
  }
  return(1);
}
protected func Activate(object pClonk) {
  [$Split$]
  CreateContents(GUNP,pClonk,3);
  RemoveObject(this());
  return(1);
}
/* Entz¸ndung */

protected func Incineration()
{
  // Explosion - verzˆgert, um Endlosrekursion zu verhindern
  var iR = RandomX(1,12);
  Schedule("Explode(50)", iR);
  // Verdunkeln, damit man besser sieht dass es unbenutzbar ist
  SetClrModulation(0x5f5f4f);
  return _inherited(...);
}