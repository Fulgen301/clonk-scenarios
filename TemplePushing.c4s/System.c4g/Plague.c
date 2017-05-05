/*-- Adjust Plague damage --*/

#strict

#appendto MGPL

protected func Slay() {
	var pClonk;
	while(pClonk=FindObject(0,-iRand/6,-iRand/6,iRand/3,iRand/3,OCF_Alive(),0,0,0, pClonk))
		if(GetActionTarget() != pClonk)
			AddEffect("Poison",pClonk,182,5,0,GetID(), fSnake, GetActionTarget());
		RemoveObject();
}

func FxPoisonStart(object pClonk,int iEffectNumber, int iTemp, fSnake, pCaster)
{
	EffectVar(2, pClonk, iEffectNumber) = GetController(pCaster);
	return _inherited(pClonk, iEffectNumber, iTemp, fSnake);
}

func FxPoisonTimer(pClonk, iEffectNumber, iEffectTime)
{
  if(iEffectTime >= 1200) return(-1);
  var fSnake = EffectVar(1, pClonk, iEffectNumber);
  var idType = GetID(pClonk);
  CreateParticle("PoisonWave", GetX(pClonk), GetY(pClonk), 0, -1, EffectVar(0, pClonk, iEffectNumber)*5+50, RGBa(fSnake*200, 255, 0), pClonk, 1);
  CreateParticle("PSpark", GetX(pClonk), GetY(pClonk), 0, -1, EffectVar(0, pClonk, iEffectNumber)*5+50, RGBa(fSnake*55, 55, 0), pClonk, 1);
  if(GBackLiquid(GetX(pClonk), GetY(pClonk))) return(-1);
         
	if(!(iEffectTime % 25))
	{
		var pFrom = GetCursor(EffectVar(2, pClonk, iEffectNumber));
		if(pFrom) pFrom->DoEnergy(-1, pClonk);
		else DoEnergy(-1, pClonk);
	}
  var obj;
  var iRadius = EffectCall(pClonk,iEffectNumber,"MaxRange");
  while(obj = FindObject(0, -iRadius+GetX(pClonk),-iRadius+GetY(pClonk),iRadius*2,iRadius*2, OCF_Alive(),0,0, NoContainer(), obj))
  {
    if(!GetEffect("Poison", obj))
	{
		if(!GetAction(obj)S="Field")
		{
			AddEffect("Poison",obj,182,10,0,MGPL,fSnake,pFrom);
		}
	}
  }
  return(1); 
}

func FxPoisonMaxRange() { return(175); }

