/*-- Neues Objekt --*/

#strict 2

local Master;
local iA;

func Initialize() {
iA = 150;
  return(1);
}
public func Set() { Master = true; }

public func Check() 
{
  if(!Master) return false;

  for(var pMed in FindObjects(Find_OCF(OCF_HitSpeed3),Find_NoContainer(),Find_Not(Find_Category(C4D_StaticBack)),Find_Not(Find_Category(C4D_Parallax))))
    SpeedEffect(pMed);
}

public func SpeedEffect(object pTarget)
{
  var obj;
  if(!Contained(pTarget))
  {
    // Erstellen des unnötigen Objektes.
    obj=CreateObject(SP33,AbsX(GetX(pTarget)),AbsY(GetY(pTarget))+32,NO_OWNER);
    // Grafik setzen
    SetGraphics(0,obj,0,1,GFXOV_MODE_Object,0,/*GFX_BLIT_ClrSfc_OwnClr*/,pTarget);
    //Besser als "Ein neues Objekt!"
    SetName(GetName(pTarget),obj);
    AddEffect("FadeOut",obj,100,1,obj,0,pTarget);
  }

}

func FxFadeOutStart(object pTarget, int iIndex, int iTemp, object pSource)
{
  var iClr = GetClrModulation(pSource);
  if(!iClr) iClr = RGB(255,255,255);

  var R, G, B, a;
  SplitRGBaValue(iClr,R,G,B,a);

  EffectVar(0,pTarget,iIndex) = pSource;  
  EffectVar(1,pTarget,iIndex) = R;
  EffectVar(2,pTarget,iIndex) = G;
  EffectVar(3,pTarget,iIndex) = B;
  EffectVar(4,pTarget,iIndex) = a;

  return true;
}

func FxFadeOutTimer(object pTarget, int iIndex, int iTime)
{
  if(iTime >= 8)
  {
    RemoveObject(pTarget);
    return -1;
  }
  
  var pSource = EffectVar(0,pTarget,iIndex);
  if(!pSource) return false;

  var R = EffectVar(1,pTarget,iIndex);
  var G = EffectVar(2,pTarget,iIndex);
  var B = EffectVar(3,pTarget,iIndex);
  var a = EffectVar(4,pTarget,iIndex);
  var iDiff = 255-a;
  
  SetClrModulation(RGBa(R,G,B,a+iDiff*iTime/7),pTarget,1);

  return true;
}
