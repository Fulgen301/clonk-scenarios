#strict 2

// Globaler Aufruf zum Erzeugen des Auswahlpfeils
global func CreateSelector(object pCommandObject, object pMenuObj, int iRadius)
{
  if(!pCommandObject) return ;
  if(!pMenuObj) return ;
  if(pCommandObject->~IsAI()) return ;
  if(pMenuObj->~IsAI()) return ;
  return _inherited(pCommandObject,pMenuObj,iRadius,...);
}

// Globaler Aufruf zum Erzeugen des Zielobjektes
global func CreateAimer(object pCommandObject, object pMenuObj, int iAngle)
{
  if(!pCommandObject) return ;
  if(!pMenuObj) return ;
  if(pCommandObject->~IsAI()) return ;
  if(pMenuObj->~IsAI()) return ;
  return _inherited(pCommandObject,pMenuObj,iAngle,...);
}
 