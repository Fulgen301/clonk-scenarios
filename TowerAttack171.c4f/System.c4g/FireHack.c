/*-- FireHack --*/

#strict

global func FxFireStart(object obj, int iNumber, int iTemp, int iCausedBy, bool fBlasted, object pIncineratingObject)
{
  if(GetAlive(obj))
    if(Random(2))
      return -1;
  return(inherited(obj, iNumber, iTemp, iCausedBy, fBlasted, pIncineratingObject));
}

global func FxFireTimer(a,b,c,d,e,f,g,h,i)
{
  _inherited(a,b,c,d,e,f,g,h,i);
  if(!GetDefCoreVal("NoBurnDecay",0,GetID(a)))
    if(!Random(2))
      DoCon(-1,a);
}
