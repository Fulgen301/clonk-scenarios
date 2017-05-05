#strict 2
#appendto ASAS

//Keulenschläge errorn nicht

protected func FxSleepNSpellStart(object pTarget, int iEffectNumber, int iTemp) {
  // temporäre aufrufe
  if(iTemp) return;
  // Scheintoter Zustand
  ObjectSetAction(pTarget, "Dead");
  // Zeit bis zum Aufwachen speichern
  EffectVar(0,pTarget,iEffectNumber) = 250;
  // Fertig
  return 1;
}

protected func FxSleepNSpellStop(object pTarget, int iEffectNumber) {
  // clonk hat den Schlaf nicht überstanden ;)
  if(!GetAlive(pTarget)) return 1;
  // aufstehen
  ObjectSetAction(pTarget,"FlatUp",0,0,1);
  // stehenbleiben
  SetComDir(COMD_Stop,pTarget);
  // Markereffekt entfernen (für KI benötigt)
  RemoveEffect("IntFoundMarker", pTarget);
  // Fertig
  return 1;
}

//Alpha-Hack geht nicht

public func DoShow()
{
  var i = _inherited(...);
  if (GetEffect("Hide", this))
    EffectCall(this, GetEffect("Hide", this), "Timer", GetEffect("Hide", this, 0, 6));
}

func FxHideStart(pTarget, iNumber, fTmp, fInstantHide)
{
  if (GetEffect("Freeze", pTarget))
    return -1;
  // Alpha auf 240 setzen
  var iAlpha = GetRGBaValue(GetClrModulation(), 0);
  EffectVar(0, pTarget, iNumber) = iAlpha;
  EffectVar(3, pTarget, iNumber) = iAlpha;
  // Instanttarnen?
  if(fInstantHide)
    EffectVar(3, pTarget, iNumber) = 234;
  // Walk Physical verringern
  EffectVar(5, pTarget, iNumber) = GetPhysical("Walk", PHYS_Current, pTarget);
  EffectVar(6, pTarget, iNumber) = GetPhysical("Scale", PHYS_Current, pTarget);
  EffectVar(7, pTarget, iNumber) = GetPhysical("Hangle", PHYS_Current, pTarget);
  SetPhysical("Walk", GetPhysical("Walk", PHYS_Current, pTarget)-20000, PHYS_Temporary, pTarget);
  SetPhysical("Scale", GetPhysical("Walk", PHYS_Current, pTarget)-20000, PHYS_Temporary, pTarget);
  SetPhysical("Hangle", GetPhysical("Walk", PHYS_Current, pTarget)-20000, PHYS_Temporary, pTarget);
  // Hilfsobjekt erzeugen, dass den Clonk für den Spieler anzeigt
  var pShower = CreateObject(SNHP, 0, 0, GetOwner());
  SetCategory(8388609, pShower);
  EffectVar(1, pTarget, iNumber) = pShower;
  pShower->SetAction("Attach", this);
  // Kategorie auf C4D_MouseIgnore setzten
  EffectVar(4, pTarget, iNumber) = GetCategory();
  SetCategory(GetCategory()|C4D_MouseIgnore);
  // Flag setzen
  fHide = 1;
}

func FxHideTimer(pTarget, iNumber)
{
  // Transparenter werden
  if(EffectVar(3, pTarget, iNumber)<235)
  { 
    var iChange = Min(235-EffectVar(3, pTarget, iNumber), 20);
    EffectVar(3, pTarget, iNumber) += iChange;
    if (EffectVar(3, pTarget, iNumber) == 235)
    {
      SetGraphics(0, pTarget, _TAS);
      SetClrModulation(RGBa(255, 255, 255), pTarget);
    }
    else
    {
      SetGraphics(0, pTarget, ASAS);
      SetClrModulation(RGBa(255,255,255,EffectVar(3, pTarget, iNumber)));
    }
  }
  SetColorDw(GetPlrColorDw(GetOwner(pTarget)), pTarget);
  // Partikeleffekt
  EffectVar(2, pTarget, iNumber) += 40;
  if(EffectVar(2, pTarget, iNumber)==360) EffectVar(2, pTarget, iNumber) = 0;
  EffectVar(1, pTarget, iNumber)->CreateParticle("HideSpark", Sin(EffectVar(2, pTarget, iNumber), 20), Cos(EffectVar(2, pTarget, iNumber), 20),-Sin(EffectVar(2, pTarget, iNumber), 2),-Cos(EffectVar(2, pTarget, iNumber), 2), 30, GetPlrColorDw(GetOwner(pTarget)), EffectVar(1, pTarget, iNumber));
}

func FxHideDamage(pTarget,iEffectNumber,iDmg,iCause)
{
  // Heilen nichts machen
  if(iDmg > 0) return iDmg;
  // aber bei Schaden wird die Tarnung aufgegeben
  RemoveEffect("Hide", pTarget);
  return iDmg;
}

func FxHideStop(pTarget, iNumber, fTmp)
{
  // Alpha auf alten Wert setzen
  SetClrModulation(RGBa(255, 255, 255));
  SetGraphics(0, pTarget, ASAS);
  SetColorDw(GetPlrColorDw(GetOwner(pTarget)), pTarget);

  SetPhysical("Walk", EffectVar(5, pTarget, iNumber), PHYS_Temporary, pTarget);
  SetPhysical("Scale", EffectVar(6, pTarget, iNumber), PHYS_Temporary, pTarget);
  SetPhysical("Hangle", EffectVar(7, pTarget, iNumber), PHYS_Temporary, pTarget);
  // Hilfsobjekt entfernen
  RemoveObject(EffectVar(1, pTarget, iNumber));
  // Kategorie zurücksetzten
  SetCategory(EffectVar(4, pTarget, iNumber));
  fHide = 0;
}