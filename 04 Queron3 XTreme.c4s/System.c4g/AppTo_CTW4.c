/*--- Artilleriegesch�tz (angeschraubt) ---*/

// Kein Schiesspulver ben�tigt und Rotationsgeschwindigkeit verdoppelt

#strict 2
#appendto CTW4

/* Einige andere Eigenschaften */
protected func RotationSpeed() { return 2; }
protected func CannonPowderNeeded(object obj) { return 0; }
