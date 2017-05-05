/*-- Neues Objekt --*/

#strict

func Initialize() {
   var sAction = Format("Exist%d",RandomX(1,3));
   SetAction(sAction);
   SetRDir(RandomX(50,-50));
   if(Stuck()) Hit();
  return(1);
}
func Hit() {
 RemoveObject(this());
  return(1);
}
