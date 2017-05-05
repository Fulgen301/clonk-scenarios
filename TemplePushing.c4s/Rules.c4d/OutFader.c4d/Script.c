/*-- Outfader --*/

#strict 2

protected func Activate(iByPlayer) 
{
  MessageWindow(GetDesc(), iByPlayer);
  return(1);
}

func Fading(iPlr)
{
	for (var obj in FindObjects(Find_OCF(OCF_InFree | OCF_InSolid | OCF_InLiquid),Find_Category(C4D_Object | C4D_Living)))
	if (!ImportantID(GetID(obj)))
	{
		if (GetAction(obj)=="Idle")
		{
			// Object owned by anyone?
			if (GetOwner(obj)== -1) FadeOut(obj,2);
			else FadeOut(obj,3);
		}
		else if (!GetAlive(obj))
		{
			if (GetOwner(obj)== -1) FadeOut(obj,1);		
			else FadeOut(obj,5);
		}
		else if (GetAction(obj)=="Be")
		{
			if (GetOwner(obj)== -1) FadeOut(obj,2);		
			else FadeOut(obj,3);
		}
		else if (GetAction(obj)=="None")
		{
			if (GetOwner(obj)== -1) FadeOut(obj,2);		
			else FadeOut(obj,3);
		}
		else if (GetAction(obj)=="Exist")
		{
			if (GetOwner(obj)== -1) FadeOut(obj,2);		
			else FadeOut(obj,3);
		}
	}
 return(1);
}


global func FadeOut(pObj,iTime)
{
 if (!iTime) iTime=2;
 if (!pObj) pObj=this;
 if (GetEffect("FadeOut",pObj)) return(0);
 AddEffect("FadeOut",pObj,200,iTime,0,OFDR);
 return(1);
}

func FxFadeOutStart(pTarget,iEffectNumber)
{
 EffectVar(0,pTarget,iEffectNumber)=255;
 return(1);
}

func FxFadeOutStop(pTarget,iEffectNumber)
{
 SetClrModulation(RGBpA(GetClrModulation(pTarget) || RGB(255, 255, 255)),pTarget);
 return(1);
}

func FxFadeOutTimer(pTarget,iEffectNumber)
{ 
 if (!pTarget) return(-1);
 if (Contained(pTarget) || pTarget->~AvoidFadeOut()) return(-1);
 EffectVar(0,pTarget,iEffectNumber)--;
 if (!EffectVar(0,pTarget,iEffectNumber)) RemoveObject(pTarget);
 SetClrModulation(RGBpA(GetClrModulation(pTarget) || RGB(255, 255, 255), 255-EffectVar(0,pTarget,iEffectNumber)),pTarget);
 return(1);
}

global func ImportantID(idObj) { return 0; }
