/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 0;}
func MedalIndex() {return 8;}

func Initialize()
{
  AddEffect("FlightCheck",this,100,5,this);
  return true;
}

func FxFlightCheckStart(object pTarget, int iIndex, int iTemp)
{
  if(GetID(pTarget) != IS_M) return -1;
  return true;
}

func FxFlightCheckTimer(object pTarget, int iIndex, int iTime)
{
  for(var pClonk in FindObjects(Find_Func("Above",-200),Find_OCF(OCF_Alive|OCF_CrewMember)))
    Reward(this,GetOwner(pClonk));
  return true;
}

global func LeftOf(int iX) {return GetX(this) <= iX;}
global func RightOf(int iX) {return GetX(this) >= iX;}
global func Above(int iY) {return GetY(this) <= iY;}
global func Below(int iY) {return GetY(this) >= iY;}
