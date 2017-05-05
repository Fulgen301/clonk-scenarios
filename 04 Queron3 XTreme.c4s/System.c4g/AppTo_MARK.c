#strict 2
#appendto MARK

func Activate(pCaller, pRealCaller)
{
  if (pRealCaller)
    pCaller = pRealCaller;
  // Zauber
  Sound("Magic*");

  // Zielen wenn möglich
  if (pCaller->~DoSpellAim(this))
    return true;
  // Clonk kann nicht zielen:
  ActivateAngle(pCaller, GetDir(pCaller)*180-90);
  return 1;
}

public func ActivateAngle(object pCaller, int iAngle)
{
  SetPosition(GetX(pCaller), GetY(pCaller));
  ScheduleCall(this, "CastRock", 1, 10 + Random(5), pCaller, iAngle);

  Schedule("RemoveObject()", 20, 0, this);
  return true;
}

protected func CastRock(object pCaller, int iAngle)
{
  var iOutX, iOutY, iOutR, iOutXDir, iOutYDir, iOutRDir;
  iAngle = iAngle + Random(21) - 10;
 
  // Austrittsgeschwindigkeit ermitteln 
  iOutXDir = Sin(iAngle, 100);
  iOutYDir = -Cos(iAngle, 100);
  // Austrittsposition... 
  iOutX = Sin(iAngle, 20 * GetCon() / 100);
  iOutY = -Cos(iAngle, 20 * GetCon() / 100); 
  // Drehung 
  iOutR = iAngle; 
  if(iAngle > 0) iOutRDir = 3; else iOutRDir = -3;
  
  // Stein abfeuern
  var pRock = CreateObject(BIRK, GetX(pCaller) - GetX() + iOutX, GetY(pCaller) - GetY() + iOutY + 12, GetOwner(pCaller));
  if (pRock)
  {
    SetXDir(iOutXDir, pRock);
    SetYDir(iOutYDir, pRock);
    SetR(iOutR, pRock);
    SetRDir(iOutRDir, pRock);
  }
}