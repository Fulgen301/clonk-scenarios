/*-- Neues Script --*/

#strict
#appendto MONS
#appendto FMNS

local iStuckTime;

private func Activity()
{
  if(Stuck()) 
  {
    iStuckTime++;

    if(iStuckTime > 40) // Also lebt es und stuck! Das ist ein wahres Fundamentmonster!
      if(GetOwner() != NO_OWNER)
      {
        var pMedal = FindObject(BF_M);
        if(pMedal && GetOwner(this) != NO_OWNER)
          Reward(pMedal,GetOwner(this));
      }
  }
  return(_inherited());
}

//Wir müssen noch prüfen, ob das Monster den Clonk wirklich killt.
private func HitCheck()
{
  var obj;
  if (obj = FindObject(0, +1,0,0,0, OCF_Prey(), 0,0, NoContainer()))
  {
    var iPlr = GetOwner(obj);
    var fAlive = GetAlive(obj);
    Punch(obj, 10);
    
    //Alle Kriterien erfüllt? :) Medaille geben!
    if(fAlive && !GetAlive(obj) && obj->~IsClonk() && Hostile(GetOwner(this),iPlr))
    {
      var pMedal = FindObject(MF_M);
      if(pMedal)
        Reward(pMedal,GetOwner(this));
    }
  }
  return true;
}
