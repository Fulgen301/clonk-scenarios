/*-- Troll und Gigant Bugfix --*/

#strict

global func FxIntScheduleTimer(object pObj,  int iEffect)
{
  // Falls eval einen Fehler enth�lt bleibts bei einer Fehlermeldung
  EffectVar(1, pObj, iEffect)--;
  if(EffectVar(1, pObj, iEffect)<0) return -1;
  // Nur eine bestimmte Anzahl Ausf�hrungen
  var fDone = EffectVar(1, pObj, iEffect) <= 0;
  // Ausf�hren
  eval(EffectVar(0, pObj, iEffect));
  return(-fDone);
}
