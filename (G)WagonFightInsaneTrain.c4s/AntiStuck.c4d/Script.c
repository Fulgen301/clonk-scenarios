
#strict

protected func Activate(int iPlr)
{
  while(Stuck(GetCrew(iPlr))) { SetPosition(GetX(GetCrew(iPlr)),GetY(GetCrew(iPlr))-5,GetCrew(iPlr)); }
  SetComDir(COMD_Down(),GetCrew(iPlr));
  return(1);
}
