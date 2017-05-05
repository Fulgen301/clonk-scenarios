/*-- Neues Script --*/

#strict

#appendto CTW4

protected func CannonPower(object obj) { return(22 - 2 * ((GetOCF(obj) & OCF_CrewMember()) != 0) ); }   