/*-- Gold --*/

#strict
local iTime,iTimer2,iTimer3,iWin;

protected func Entrance(object pObj)
{
 iTime=240;
 var pObj = FindObject(MAGE,-20, -20, 40, 40, OCF_CrewMember,0,0,0,pObj);//Lebewesen TÖTEN! >:D
 CreateParticle("NoGravSpark", RandomX(-2,1), RandomX(-1,2), RandomX(-2,3), RandomX(-1,2), RandomX(80,60), RGB(155,020,000));
 CreateParticle("NoGravSpark", RandomX(-2,1), RandomX(-1,2), RandomX(-2,3), RandomX(-1,2), RandomX(80,60), RGB(155,000,020));
 CreateParticle("NoGravSpark", RandomX(-2,1), RandomX(-1,2), RandomX(-2,3), RandomX(-1,2), RandomX(80,60), RGB(155,010,030));
   CastObjects(FU_8,5,50);
 Sound("MagicElementEarth");
 Sound("MagicElementAir");
SetOwner(GetOwner(GetCursor(GetOwner(pObj))),0);
 return(1);
}

protected func Initialize() {
  iTime=240;
  return(1);
}

/* Aufschlag */

protected func Hit(object pObj)
{
  CastObjects(BUM2,10,50);
  CastObjects(FU_8,5,50);
  CastObjects(FU_8,5,150);
  Log("Der <c ffcc00>Goldklumpen</c> wurde fallen gelassen!");
  SetPosition(583,404,this());
  Message("",this());
  SetYDir(0);
  SetXDir(0);
  iTime=140;
  Sound("RockHit*");
  DoRound();
  SetOwner(-1,0);
  iWin=0;
  return(1);
}

protected func Check(){
if(iTimer3==0){
iTimer3=1;
}
if(iTime<=0){
Win();
}
if(Contained(this())){
if(iTimer2>=20){
iTime--;
iTimer2=0;
}
iTimer2++;
Message("Noch <c 00ccff>%d</c> zu halten.", this(), iTime);
  }
}

protected func Win(){
  var Winner = GetPlayerTeam(GetOwner(this()));  
  for(var i=0; i<GetPlayerCount(); i++)
    {
    var Loser = FindObjectOwner(MAGE,i,0,0,0,0,0,0,0,0);
    if(GetPlayerByIndex(i))
      {
      if(Hostile(GetOwner(Loser),GetOwner(this())))
        {
        EliminatePlayer(GetOwner(Loser));
        }
      }
    }  
  iWin++;
  /*if(iWin==1)
  {
  Log("%s hat sein Team zum Sieg gebracht!",GetTaggedPlayerName(GetOwner(this())));
  Message("Siegreicher Sieg. :)");
  }*/
}

