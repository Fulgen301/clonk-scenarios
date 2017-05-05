/*-- Neues Script --*/

#strict
#appendto SF5B

protected func RejectCollect(id idObj, object pObj)
{
  // nicht mehr als 5 Objekte tragbar
  if(pObj->~IsWeapon()||pObj->~IsUpgrade()||pObj->~IsEquipment()) return (1);
  if(pObj->~IsEkeWeapon()&&ContentsCount(idObj)) return 1;
  if (ContentsCount() >= 10) return(1);
  return(0);
}
