/*-- Turm --*/

#strict
//#include BSC1

func Initialize()
{
  SetGraphics("");
}

protected func Incineration()
{
  SetGraphics("Dmg");
}

func Attack()
{
  if(GetCon()<100)
    return 0;
  //Log("Attack %v",pTarget);
  var pTarget;
  if(pTarget=FindObject2(Find_NotHidden(),Find_OCF(OCF_Alive()),Find_Hostile(GetOwner()),Find_Not(Find_Distance(MinRange())),Find_Distance(Range()),Find_PathFree(0,ArrowOutYOff()),Sort_Distance()))
    ShotAt(pTarget);
}

public func ShotAt(pTarget)
{
  //Log("ShotAt %v",pTarget);
  // Pfeil erstellen
  var pArrow = CreateObject(ArrowID(),0,0,-1);
  var iAngle = CalcAngle(GetX(pTarget),GetY(pTarget)+RandomX(40,40));
  // Austrittsgeschwindigkeit ermitteln
  var iOutX, iOutY, iOutR, iOutXDir, iOutYDir, iOutRDir;
  GetBowOutAngle(Contained(), iAngle, true, iOutX, iOutY, iOutR, iOutXDir, iOutYDir, iOutRDir);
  // Pfeil abfeuern
  //Log("pArrow %v",pArrow);
  Exit(pArrow, GetX()+iOutX,GetY()+iOutY+ArrowOutYOff(),iOutR, 0,0,iOutRDir );
  pArrow->SetPosition(GetX()+iOutX,GetY()+iOutY+ArrowOutYOff());
  pArrow->SetR(iOutR); pArrow->SetRDir(iOutRDir);
  pArrow->SetXDir(iOutXDir); pArrow->SetYDir(iOutYDir);
  pArrow->~Launch();
  //Schedule("FadeOut(0,2)",350,0,pArrow);
  AddEffect("IntArrowVanish",pArrow,1,3,0,MGBW);
	// Sound
  Sound("Bow");
}

public func CalcAngle(iX,iY)
{
  var iAngle = Angle(GetX(),GetY()+ArrowOutYOff(),iX,iY);
  // Bei größerer Distanz höher zielen
  if(Inside(iX-GetX(),+1,+Range()))
     iAngle -= Abs(iX-GetX())*8/ArrowPower();
  if(Inside(iX-GetX(),-Range(),-1))
     iAngle += Abs(iX-GetX())*8/ArrowPower();
  return iAngle;
}

public func GetBowOutAngle(pClonk, iAngle, fDeviate, &iOutX, &iOutY, &iOutR, &iOutXDir, &iOutYDir, &iOutRDir)
{
  // Zufallsabweichung
  if(fDeviate) { iAngle += Random(11) - 5; }
  // Austrittsgeschwindigkeit ermitteln
  iOutXDir = Sin(iAngle, ArrowPower());
  iOutYDir = -Cos(iAngle, ArrowPower());
  // Austrittsposition...
  iOutX = Sin(iAngle, 25);
  iOutY = -Cos(iAngle, 25);
  // Pfeildrehung
  iOutR = iAngle;
  if(iAngle > 0) iOutRDir = 3; else iOutRDir = -3;
  // Fertig
  return(1);
}

//func StrikeDamage(){ return RandomX(3,5);}
func MinRange(){ return 100;}
func Range(){ return 500;}
func ArrowID(){ return ARRW;}
func ArrowPower(){ return 110;}
func ArrowOutYOff(){ return -46;}

func CanBeBuild(pClonk)
{
  //if(GetID(pClonk)==PLDN)
    return true;
}

func UpgradeTo()
{
  return BTW2;
}

func UpgradeCost()
{
  return 105;
}

func IsLevel1(){return 1;}
