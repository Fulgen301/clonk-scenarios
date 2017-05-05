/*-- FadeOut --*/

#strict

global func FadeOut(obj,speed) 
{
  if(!obj)
    obj=this;
  if(!speed)
    speed=1;
  AddEffect("FadeOut",obj,100,speed,obj);
  return(1);
}

global func SetObjAlpha(byAlpha, pObj,iLayer)
{
  var byAlpha=BoundBy(byAlpha,0,255);
  var dwClrMod=GetClrModulation(pObj,iLayer);
  if(!dwClrMod)
  	dwClrMod=RGB(255,255,255);
    dwClrMod=SetRGBaValue(dwClrMod,byAlpha);
  if(iLayer)
   return(SetClrModulation(dwClrMod, pObj,iLayer));
  else
   return(SetClrModulation(dwClrMod, pObj));
}

global func FxFadeOutTimer(object pObject, int iEffectnumber, int iEffectTime)
{
  if(!pObject)
    return(-1);
  var Alpha=BoundBy(GetRGBaValue(GetClrModulation(pObject))+5,1,255);
  SetObjAlpha(Alpha,pObject);
  if(Alpha >= 255)
    return(-1);
  return(1);
}

global func FxFadeOutStop(object pObject, int iEffectNumber, iReason, Temp)
{
  //Log("FxFadeOutStop");
  if(Temp)
    return(0);
  if(pObject)
  {
    var obj;
    var i=0,x=GetX(pObject),y=GetY(pObject);
    while(obj=Contents(i++,pObject))
      Exit(obj);
    if(GetAlive(obj))
      Kill(pObject);
    RemoveObject(pObject,0);
  }
  return(1);
}

global func FxFadeOutEffect(string szNewEffectName)
{
  if(szNewEffectName S= "FadeOut")
   return(-1);
  return(0);
}
