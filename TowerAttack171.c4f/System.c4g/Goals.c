/*-- GameCallEx in den Spielzielen --*/

#strict
#appendto GOAL

protected func CheckTime()
{
  // Zielpr�fung aktiv?
  if(!ActIdle()) return(1);
  if (ObjectCount(RVLR))
  {
    if (CheckRivalry()) return(1);
  }
  else
  {
    if (CheckCooperative()) return(1);
  }
  // Ziel erf�llt: Vom Szenario abgefangen?
  if (GameCallEx("OnGoalsFulfilled")) return(RemoveObject());
  // Tja, jetzt ist das Spiel vorbei. Erstmal die Belohnung
  Sound("Trumpet", 1);
  // Jetzt ein wenig warten, und dann GameOver
  SetAction("Wait4End");
  return(1);
}
