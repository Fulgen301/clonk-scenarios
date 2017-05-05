/*-- Message-Objekt --*/

#strict 2

global func ExtraMessage(string szText,id idPicture,int iColor,object pObj)
{
  if(!pObj) return false;
  if(!iColor) iColor = RGB(255,255,255);

  var pText = CreateObject(ME0D,AbsX(GetX(pObj)),AbsY(GetY(pObj))-10,NO_OWNER);
  SetYDir(-50,pText);
  SetXDir(Random(5)-2,pText);
  AddEffect("Message",pText,100,1,pText,0,szText,idPicture,iColor);
  return true;
}

func FxMessageStart(object pTarget, int iIndex, int iTemp, string szText, id idPicture, int iColor)
{
  EffectVar(0,pTarget,iIndex) = szText;
  EffectVar(1,pTarget,iIndex) = idPicture;
  EffectVar(2,pTarget,iIndex) = iColor;

  return true;
}

func FxMessageTimer(object pTarget, int iIndex, int iTime) 
{
  if(iTime >= 250) return RemoveObject(pTarget);

  var szText = EffectVar(0,pTarget,iIndex);
  var idPicture = EffectVar(1,pTarget,iIndex);
  var iColor = EffectVar(2,pTarget,iIndex);

  var iR, iG, iB, iA;
  SplitRGBaValue(iColor,iR,iG,iB,iA);

  Message("<c %x>{{%i}}</c>|<c %x>%s</c>",pTarget,RGBa(255,255,255,255-iTime),idPicture,RGBa(iR,iG,iB,255-iTime),szText);
  SetYDir(-(250-iTime)/50,pTarget);
  return true;
}
