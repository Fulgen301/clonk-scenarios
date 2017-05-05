/*-- Feindliche Flaggen zu vernichten bringt eine Medaille --*/

#strict 2
#appendto FLAG

local iOriginal, iLast;

func Initialize()
{
  iOriginal = GetOwner(this);
  iLast = -1;
  return _inherited(...);
}

func Entrance(object pClonk)
{
  iLast = GetOwner(pClonk);
  return _inherited(...);
}

//Sowohl verkaufen
func SellTo(int iPlr)
{
  if(Hostile(GetOwner(this),iPlr))
  {
    var pMedal = FindObject(AS_M);
    if(pMedal)
      Reward(pMedal,iPlr);
  }
  return _inherited(...);
}

//Als auch zerstören
func Destruction()
{
  if(Hostile(GetOwner(this),iLast))
  {
    var pMedal = FindObject(AS_M);
    if(pMedal)
      Reward(pMedal,iLast);
  }
  
  return _inherited(...);
}

func OnOwnerChanged(int iNew, int iOld)
{
  //Spieler existiert noch und die Spieler sind verfeindet? Spielerwechsel unterbinden.
  if(GetPlayerName(iOriginal) && Hostile(iNew,iOriginal))
    SetOwner(iOriginal,this);
  return _inherited(iNew,iOld);
}
