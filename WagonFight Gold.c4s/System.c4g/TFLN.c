/*-- Killverfolgung --*/

#strict
#appendto TFLN
#appendto SFLN

func Departure(object pContainer) {
 //Log("%s %d",GetName(pContainer),SetOwner(GetOwner(pContainer)));
 if(GetAlive(pContainer)) SetOwner(GetOwner(pContainer));
 _inherited();
 }