#strict

local iXDir,iYDir;

/* --- Boomerang --- */

protected func Departure(pObj) {
  if(GetXDir())
    if(GetOCF(pObj)&OCF_Living())
      SetAction("Depart");
  if(GetAlive(pObj)) pObj->CreateContents(GetID(this));
  Schedule("RemoveObject()", 75,0);
}

protected func Departure2() {
  if(Contained()) return(SetAction("Idle"));
  Sound("Catapult");
  SetXDir(GetXDir()*3);
  SetYDir(-50);
  SetRDir(GetXDir()*2);
  iXDir=(GetXDir()>0)*2-1;
  iYDir=20;
}

protected func Hit() {
  Sound("BmHit");
  if(!Random(5)) return(1);
  if(Random(3)) SetRDir(0-GetRDir());
  if(!GBackSolid(0,-10)) SetYDir(-8);
  if(!ActIdle()) NormalFlight();
  if(GBackSolid(-10,0)) return(SetXDir(+15));
  if(GBackSolid(10,0))  return(SetXDir(-15));
  SetXDir(GetXDir()/2);
}

protected func FlyCheck() {
  if(--iYDir < 6) return(NormalFlight());
  SetXDir(GetXDir()-iXDir*10);
  if(iYDir>17) SetYDir(GetYDir()+12);
  if(iYDir<16) SetYDir(GetYDir()-10);
}

func NormalFlight() {
  SetRDir(GetRDir()/4);
  SetYDir(GetYDir()/2);
  SetAction("Idle");
  iXDir=0;
  iYDir=1;
}
