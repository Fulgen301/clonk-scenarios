/*-- Kugel --*/

#strict 2

#appendto CSHO

func Travel(){
if(GetActTime()>20)RemoveObject();
return _inherited();
}
