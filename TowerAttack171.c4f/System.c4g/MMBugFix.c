/*-- Neues Script --*/

#strict
#appendto MYST

func CastC4Object(pObj) {
  if(GetType(pObj)==C4V_C4Object)
    return true;
  return CastAny(pObj);
}
