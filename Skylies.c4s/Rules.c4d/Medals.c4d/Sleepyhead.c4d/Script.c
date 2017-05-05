/*-- Medaille --*/

local TimeSlept;

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 0;}
func MedalIndex() {return 14;}


func Initialize()
{
  TimeSlept = CreateArray(GetPlayerCount());
  return true;
}

func AddSleepTime(iPlayer, iTime)
{
  if(iPlayer == -1)  return false;
  TimeSlept[iPlayer]+=iTime;
  CheckSleepTime();
  return iTime;
}

func CheckSleepTime()
{
  for(var i; i <= GetLength(TimeSlept); i++)
  if(TimeSlept[i]>=2160)
    Reward(this,i);
}