/* Killtracing */

#strict
#appendto CANN

public func Fire(bool fAuto)
{
  // Schieﬂpulver und Projektil suchen
  var pGunpowder=FindContents(GUNP), pProjectile=FindOtherContents(GUNP);

  //Projektil fehlt? Weder im normalen Spiel toll, noch im Hardcoremodus. Sofort abbrechen
  if(!pProjectile)
  {
    Sound("Click");
    return false;
  }  

  if(!IsHardcoreMod()) 
  {
    // Schieﬂpulver fehlt
    if (!pGunpowder)
    {
      Sound("Click");
      return false;
    }
    // Schieﬂpulver verbrauchen
    RemoveObject(pGunpowder);
  }

  // Austritt berechnen
  var iX = (GetPhase()+3)*(GetDir()*2-1);
  var iY = GetPhase()-14;
  var iAngle = BoundBy(GetPhase()*5-5,0,90);
  var iXDir = Sin(iAngle,32*(GetDir()*2-1));
  var iYDir = Cos(iAngle,-18);

  // Projektil abfeuern
  //Hier Owner setzen f¸rs Killtracing
  SetController(GetOwner(GetActionTarget(1)),pProjectile);
  Exit(pProjectile,iX,iY,Random(360),iXDir,iYDir,+30);

  // Sicht verfolgen (wenn kein automatischer Schuss)
  if(!fAuto)
    if(GetPlrViewMode(GetController())!=2)
      SetPlrView(GetController(),pProjectile);
  // Sound
  Sound("Blast2");
  // Rauch
  for (var i = 0; i < 6; ++i)
    Smoke(iX+RandomX(-5,+5),iY+RandomX(-5,+5),RandomX(5,12));
  // Erfolgreich geschossen
  return true;
}
