/*-- Paar globale Scripts --*/

#strict

global func CreateCloud() {
	// Wolke
	var x;
	var WindDirection;
	if(GetWind() < 0){ WindDirection = 2; }
	if(GetWind() > 0){ WindDirection = 1; }
	if(WindDirection == 1){ x = 0; } else { x =LandscapeWidth(); }
	CreateParticle("Cloud",RandomX(0,LandscapeWidth()),RandomX(0,150),RandomX(GetWind()/4,GetWind()/2),RandomX(-2,0),RandomX(1000,1500));
return(1);
	
}

global func PlaceInSea(id id, int amount, int ox, int oy, int wdt, int hgt) // Funktion: Platziert amount Objekte vom Typ id auf dem Meeresboden.
{
  if(!wdt) wdt=LandscapeWidth();
  if(!hgt) hgt=LandscapeHeight();
  var x,y;
  var c;
  for(var i=amount; i>=0; --i)
  {
    x=RandomX(ox, wdt);
    y=RandomX(oy, hgt);
    while(!GBackLiquid(x,y))
    {
      x=RandomX(ox, wdt);
      y=RandomX(oy, hgt);
      if(++c > 500) break;
    }
    if(!GBackLiquid(x,y)) continue;
    c=0;
    while(GBackLiquid(x,y))
    {
      y++;
      if(++c > 500) break;
    }
    if(GBackLiquid(x,y)) continue;
    CreateObject(id, x, y, -1);
  }
}
// Funktion: Platziert amount Objekte vom Typ id auf dem Festland.
global func PlaceOnLand(id id, int amount, int ox, int oy, int wdt, int hgt, int reverse, int rndcon)
{
  if(!wdt) wdt=LandscapeWidth();
  if(!hgt) hgt=LandscapeHeight();
  var x,y;
  var c;
  for(var i=amount; i>=0; --i)
  {
    x=RandomX(ox, wdt);
    y=RandomX(oy, hgt);
    while(GBackSemiSolid(x,y))
    {
      x=RandomX(ox, wdt);
      y=RandomX(oy, hgt);
      if(++c > 500) break;
    }
    if(GBackSolid(x,y)) continue; 
    c=0;
    while(!GBackSolid(x,y))
    {
      if(reverse) y--;
      else y++;
      if(++c > 500 || GBackLiquid(x,y)) break;
    }
    if(!GBackSolid(x,y) || GBackLiquid(x,y)) continue;
    if(!reverse) y+=5;
    var obj=CreateObject(id, x, y, -1);
    if(rndcon) obj->SetCon(RandomX(20,100));
  }    
}  

