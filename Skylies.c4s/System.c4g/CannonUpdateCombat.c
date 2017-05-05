/*-- Neues Script --*/

#strict

#appendto CTW2

protected func CannonPower(object obj) { return(18); }

protected func CannonPowderNeeded(object obj) { if(!IsHardcoreMod()) return(1); }
