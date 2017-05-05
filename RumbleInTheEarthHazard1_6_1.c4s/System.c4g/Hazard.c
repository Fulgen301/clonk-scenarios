/*-- Neues Script --*/

#strict
#appendto HZCK

protected func RejectCollect(id idObj, object pObj)
{
  if(pObj->~IsEkeWeapon()) return 1;
  // Für die KI
  var effect;
  if(effect = GetEffect("CollectionException", pObj))
    if(EffectVar(0, pObj, effect) == this())
      return(1);
  // Spawnpunkt-Hack
  if(idObj == SPNP) return();
  // Munitionspaket?
  if(pObj ->~ IsAmmoPacket())
    // Davon kann man in jeden Fall _eines_ im Inventar haben
    if(!CustomContentsCount("IsAmmoPacket"))
      return(0);
  //Waffe?
  if(pObj ->~ IsWeapon()) {
    //Sonderbehandlung?
    if(!(pObj ->~ OnCollection(this()))) {
      //nein. Standardprozedur:
      //schon so eine Waffe im Inventar? Oder bereits 3 andere Waffen?
      if(ContentsCount(idObj) || CustomContentsCount("IsWeapon") >= 5)
        return(1);  //Ja, nicht aufnehmen
      else
        return(0);
    }
    else
      return(0);
  }
  // Einsammellimit für Ausrüstung
  if(pObj ->~ IsEquipment() && ContentsCount(idObj) > 0)
    return(1);
  //Wieviel haben wir denn schon im inventar?
  if(ContentsCount() - CustomContentsCount("IsWeapon") >= 5)
    return(1);
  
  // nicht angelegte Ausrüstung nochmal aufsammeln
  for(var gear in aGear)
    if(gear)
      if(GetID(gear) == idObj)
        return(1);
  
  // Ok
  return(0);
}
