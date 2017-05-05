/*-- Neues Script --*/

#strict
#appendto ZAP1

//Killfeststellung
private func Sting(obj) 
{
  var iPlr = GetOwner(obj);
  var fAlive = GetAlive(obj);
  
  Punch(obj,3+Random(2));
  Sound("Sting");

  if(fAlive && !GetAlive(obj) && obj->~IsClonk() && Hostile(GetOwner(this),iPlr))
  {
    var pMedal = FindObject(ZL_M);
    if(pMedal)
      Reward(pMedal,GetOwner(this));
  }

  if(!Random(3)) Death();
}
