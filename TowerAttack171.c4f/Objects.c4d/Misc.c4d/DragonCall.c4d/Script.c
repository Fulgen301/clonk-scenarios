/* Drachenbeschw�rung */

#strict

/* Aufruf */

public func Summoned(pClonk)
{
  var pDragon = CreateObject(DRGN, 0, 19);
  if(GetDir(pDragon)) SetPosition(GetX(pDragon)-19, GetY(pDragon));
  pDragon->SetAction("WakeUp");
  // Kontrolle �bernehmen
  pDragon->ResetControl();
  pDragon->UpdateRideVertex();
  return(RemoveObject());
}

// Kann mit einem Ritual beschworen werden
public func IsRitual()	 { return(1); }

// Nur f�r Kirchenlose
public func NeedChurch() { return(-1); }
