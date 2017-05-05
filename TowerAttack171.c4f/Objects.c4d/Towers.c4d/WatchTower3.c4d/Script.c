/*-- Turm --*/

#strict
#include BTW1

//func StrikeDamage(){ return RandomX(3,5);}
func MinRange(){ return 50;}
func Range(){ return 750;}
func ArrowID(){ return FARW;}
func ArrowPower(){ return 140;}
func ArrowOutYOff(){ return -56;}

func UpgradeTo()
{
  return false;
}

func UpgradeCost()
{
  return 0;
}

func NeedToBeResearched()
{
  return true;
}

func IsLevel1(){return 0;}

func Attack()
{
  if(GetCon()<100)
    return 0;
  //Log("Attack %v",pTarget);
  var pTarget;
  if(pTarget=FindObject2(Find_NotHidden(),Find_OCF(OCF_Alive()),Find_Hostile(GetOwner()),Find_Not(Find_Distance(MinRange())),Find_Distance(Range()),Find_PathFree(0,ArrowOutYOff()),Sort_Distance()))
    ScheduleCall(this,"ShotAt",3,RandomX(1,3),pTarget);
}
