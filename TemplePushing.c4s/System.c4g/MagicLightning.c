/*-- Prevent Magic Lighting scrolls from disappearing --*/

#strict

#appendto MLGT

func Activate(pCaster,pRealcaster) {
  var pClonk;
  if(pRealcaster) pClonk=pRealcaster;
  else pClonk=pCaster;

  var iResult;
  if (iResult = CheckEffect("LightningNSpell", 0, 125)) return(iResult!=-1 && RemoveObject());
  
  // Zielen wenn möglich
  if (pClonk->~DoSpellAim(this(), pCaster)) return(1);

  // Blitz erzeugen
  var obj = CreateObject(LGTS, -GetX(), -GetY(), GetOwner(pClonk));
  obj->Launch(pCaster, GetX(pCaster)+GetVertex(0, VTX_X, pCaster), GetY(pCaster)+GetVertex(0, VTX_Y, pCaster), (!GetDir(pCaster))*1800);
  Sound("Thunder*");
  RemoveObject();
  return(1);
}

public func ActivateAngle(object pCaller, int iAngle)
{
  var obj = CreateObject(LGTS, -GetX(), -GetY(), GetOwner(pCaller));
  obj->Launch(pCaller, GetX(pCaller), GetY(pCaller), (900-iAngle*10));
  Sound("Thunder*");
  
  RemoveObject();
  return(1);
}
