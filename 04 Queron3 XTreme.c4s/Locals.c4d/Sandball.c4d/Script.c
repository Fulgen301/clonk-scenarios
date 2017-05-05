/*-- Sandklumpen --*/

#strict

local owner;

protected func Hit()
{
  CastPXS("Sand", 100, 20);
  RemoveObject();
  return(1);
}

// Werfen
protected func Departure(object pThrower)
{
  if(GetAlive(pThrower)) pThrower->CreateContents(GetID(this));  
  var proc = GetProcedure(pThrower);
  var comd = GetComDir(pThrower);
  // Ablegen -> Abbruch
  if (GetPlrDownDouble(GetOwner(pThrower)))
    // Nur Ablegen in der Luft mit Befehlsrichtung? Luftwurf erlauben!
    if (proc ne "FLIGHT" || GetComDir(pThrower) == COMD_None)
      return(0);
  
  // Ablegen im stehenden Hangeln -> Abbruch
  if (proc eq "HANGLE" && comd == COMD_None)
    return(0);
  
  // Ablegen im Schwimmen / Klettern -> Abbruch
  if (proc eq "SWIM" || proc eq "SCALE")
    return(0);
  
  // Wurfrichtung rausfinden
  var dir;
  // Nach Befehlsrichtung, wenn sinnvolle Werte vorhanden
  if (comd == COMD_Left() || comd == COMD_Right()) {
    if (comd == COMD_Left())  dir = -1;
    if (comd == COMD_Right()) dir = +1;
  }
  // sonst nach Blickrichtung
  else {
    if (GetDir(pThrower) == DIR_Left()) dir = -1;
    else dir = +1;
  }

  // Wurfgeschwindigkeiten berechnen
  var x_dir = dir * GetPhysical("Throw", 0, pThrower)/1000 + GetXDir(pThrower)/3;
  var y_dir = -30;

  if (!x_dir) return(0);
  
  // Position anpassen
  SetPosition(GetX() + x_dir / 5, GetY() - 2 + GetYDir(pThrower) / 2);

  // Geschwindigkeit setzen
  SetXDir(x_dir);
  SetYDir(y_dir);
}
