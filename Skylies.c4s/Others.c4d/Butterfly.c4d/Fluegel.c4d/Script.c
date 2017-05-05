/*-- Blüte --*/

#strict

local dir, dir2, alpha;

func Initialize() {
  SetAction("Vine");
  SetPhase(Random(9));
  SetComDir(COMD_Down());
  dir=RandomX(-5,5);
  dir2=1-Random(2)*2;
  SetRDir(RandomX(-6,6));
  return(1);
}
public func Set(int ding) {
SetGraphics("2");
}
func Timer()
{
  if(GBackLiquid(0,1)&&dir2)
  {
    dir2=0;
    SetComDir(COMD_None());
    var i= GetPhase();
    SetAction("Vine2");
    SetPhase(i);
    SetSpeed();
    return(1);
  }
  if(!dir2) return(FadeMeOut());
  if(dir2==1)
  {
    if(dir>20) dir2=-1;
    dir++;
  }
  if(dir2==-1)
  {
    if(dir<-20) dir2=1;
    dir--;
  }
  SetSpeed(dir,(20-Abs(dir))*3/4);
  return(1);
}

func FadeMeOut()
{
  SetClrModulation(RGBa(255,255,255,alpha++));
    if(alpha==255) return(RemoveObject());
    return(1);
}

func Hit()
{
  dir2=0;
}