/*-- Neues Script --*/

#strict
#appendto MSMN
#appendto MRVL

public func GetSpellStaff(object pMage) { return(SMOD); }

public func GetSpellStaffCombo(pMage)
{
  if(GetID()==MSMN)
    return "52";
  if(GetID()==MRVL)
    return "25";
} // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
