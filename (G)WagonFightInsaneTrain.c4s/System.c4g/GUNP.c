/*-- Osterei!! --*/

#strict

#appendto GUNP

func Activate(pDing)
{
//ala mag nicht :(((
return(0); 
if(FindContents(SFLN,pDing))if(FindContents(ARRW,pDing)) { GameCall("Doof"); RemoveObject(this()); }
}
