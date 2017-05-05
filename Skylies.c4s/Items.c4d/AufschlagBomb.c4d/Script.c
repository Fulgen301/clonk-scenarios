/*--- Magiebombe ---*/

#strict

local iPower;
local iHited;

public func Hit3()
{
 ShakeTheWorld();
 iHited = 1;
 SetSpeed(0,0);
 var iIndex = GetEffect("MedalShake",this);
  if(iIndex)
    if(EffectVar(0,this,iIndex))
      EffectVar(0,this,iIndex) ->~ AddStrike();
 return(1);
}

public func Check()
{
if(Abs(GetYDir()) > 10) iHited = 0;
if(!iHited) iPower = Abs(GetYDir());
}

public func ShakeTheWorld()
{
  Sound("MetallStampf");
  ShakeViewPort(RandomX(20,30),this());
  var Power = iPower;
  var iCount = 0;  
  
  for(var pObj in FindObjects(Find_Distance(60),Find_NoContainer(),Find_Not(Find_Category(C4D_Structure)),Find_Not(Find_Category(C4D_StaticBack))))
  {
    if(pObj)
      if(!GetAlive(pObj))
      {
        SetSpeed(GetXDir(pObj)+RandomX(-20,20),GetYDir(pObj)-RandomX(Power/10,Power+(iPower/4)),pObj);
        iCount++;
      }
    if(GetAlive(pObj)) 
    {
      pObj->~SetAction("Tumble");
      SetSpeed(GetXDir(pObj)+RandomX(-12,12),GetYDir(pObj)-RandomX(Power/10,Power+(iPower/6)),pObj); 
    }
  }
  iPower = 0;
  
  for(var pObj in FindObjects(Find_ID(BRDG),Find_AtRect(-10,-10,20,20)))
  {
    if(!Random(3))
      pObj ->~ Release();
  }
  
  for(var i=0;i<5;i++) 
  {
    CreateParticle("PxSpark",RandomX(-10,10),+8,RandomX(-2,2),RandomX(-15,-20),RandomX(20,30),RGB(255, 255, 255));
    var st = CreateObject(ROCK,RandomX(-10,10),+10,GetOwner());
    ShakeFree (GetX(st), GetY(st), RandomX(6,15));
    RemoveObject(st);
  }

  //Genug Objekte rumgeschmissen? Belohnen!
  if(iCount >= 50)
  {
    var pMedal = FindObject(HC_M);
    if(pMedal)
      Reward(pMedal,GetController(this));
  }

}

/* Kann in der Chemiefabrik hergestellt werden */
public func IsChemicalProduct() { return(1); }
