/*-- Neues Script --*/

#strict 2
#appendto MELE

public func IsFulfilled()
{
  var iFulFil = _inherited(...);
  if(iFulFil)
  {
    /* Diverse Medaillenobjekte benachrichtigen */
    GameCallEx("MedalFulfil");
    
    
    //Still Alive
    var pMedal = FindObject(SA_M);
    if(pMedal)
      pMedal ->~ Fulfil();
    
    //Rage Mode
    pMedal = FindObject(RM_M);
    if(pMedal)
      pMedal ->~ Fulfil();
    
  }
  return iFulFil;
}


