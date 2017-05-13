/*-- Funke --*/

#strict

local R,G,B,a,i;

protected func Initialize() {
  return(StartIt());
}

func StartIt() {
  R=RandomX(255,-255);
  G=RandomX(255,-255);
  B=RandomX(255,-255);
  SetAction("i");
}

private func Effect() {
  CreateParticle("VMSpark",0,0,0,0,RandomX(40,60),RGBa(R,G,B,Random(50)));
  ++i;
  Sound("Fuse");
  if(i>=45){
    return(Finshes());
    }
  return(1);
}

protected func Hit() {
 return(RemoveObject(this()));
}

private func Finshes() {
 return(RemoveObject(this()));
}
