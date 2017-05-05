/*-- Troll und Gigant Bugfix --*/

#strict

global func FxIntScheduleTimer(object pObj,  int iEffect)
{
  // Falls eval einen Fehler enthält bleibts bei einer Fehlermeldung
  EffectVar(1, pObj, iEffect)--;
  if(EffectVar(1, pObj, iEffect)<0) return -1;
  // Nur eine bestimmte Anzahl Ausführungen
  var fDone = EffectVar(1, pObj, iEffect) <= 0;
  // Ausführen
  eval(EffectVar(0, pObj, iEffect));
  return(-fDone);
}
