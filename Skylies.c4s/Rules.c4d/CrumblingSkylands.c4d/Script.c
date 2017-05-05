/*-- Steinschlag --*/

#strict

protected func Initialize()
{
  // Eigene Position festlegen
  SetPosition(1,1);
  return(1);
}

/* Eventuell Steinschlag erstellen */
private func DoRocks()
{
 if(SeaAddon) return(1);
 if (Random(150)) return(1);
 var cnt = RandomX(1,6);
 if(!Random(30)){ cnt = cnt+RandomX(3,9); } // Grosses Fressen.
 var x = Random(LandscapeWidth());
 for(var i = 0; i <= cnt; i++){
 var relX = x-RandomX(-100,100);
 if(relX <= 0) relX = x;
 if(relX >= LandscapeWidth()) relX = x;
 var pRock = CreateObject(FREZ, relX, LandscapeHeight()-40, -1);
 }
  return(1);
}