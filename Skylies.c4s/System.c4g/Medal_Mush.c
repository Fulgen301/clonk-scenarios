/*-- Pilzpilzpilzpilzpilz --*/

#strict 2
#appendto MUSH

public func Reproduction()
{
  // Ist noch Platz für einen Baum?
  var iSize = ReproductionAreaSize();
  var iOffset = iSize / -2;
  if (ObjectCount(GetID(), iOffset, iOffset, iSize, iSize)<MaxTreeCount()) {
    // OK, hin damit
    var pMush = PlaceVegetation(GetID(), iOffset, iOffset, iSize, iSize, 10);
    if(pMush) pMush->~GetMyColor(GetColorDw());
    SetOwner(GetOwner(this),pMush);
    
    var pMedal = FindObject(MR_M);
    if(pMedal && GetOwner(this) != NO_OWNER)
      Reward(pMedal,GetOwner(this));
    
    return(1);
  }
  // Kein Platz ;'(
  return(0);
}
