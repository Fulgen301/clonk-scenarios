/* Meteoritenhagel: Treibsandminen-Kombo */
// Da es in Stimmels keine Feuermonstereier gibt, wird die Mine durch
// ein Ei ersetzt und dann beim Erzeugen der Meteore zurueck verwandelt

#strict 2

#appendto MMTR

public func Activate(object pCaster, object pRealcaster)
  {
  // Zaubernden Clonk ermitteln
  var pClonk=pRealcaster;
  if(!pClonk) pClonk=pCaster;
  // ggf. Treibsandmine durch Ei ersetzen
  var first_cont_id;
  var qsm = FindContents(_QSM, pClonk);
  if (qsm)
    {
    ChangeDef(FMEG, qsm);
    // Bug im Meteoritenhagel: Es muss das erste Inhaltsobjekt sein
    // Wir wollen aber auch erlauben, dass es mit Schriftrollen geht
    // Dadurch kann man allerdings keine andere Kombo (SFLN, EFLN) mehr waehlen
    // Sollte mal jemand korrigieren...
    first_cont_id = GetID(Contents(0, pClonk));
    if (first_cont_id != FMEG) ShiftContents(pClonk, false, FMEG, false);
    }
  var result = inherited(pCaster, pRealcaster, ...);
  if (qsm)
    {
    // Hat irgendwie nicht geklappt. Zurueck verwandeln.
    ChangeDef(_QSM, qsm);
    }
  // Immer Inhaltsreihenfolge des Clonks korrigieren
  if (first_cont_id && (first_cont_id != FMEG))
    ShiftContents(pClonk, false, first_cont_id, false);
  return result;
  }

public func CastMeteor(id idObj)
  { 
  if (idObj == FMEG) idObj = _QSM;
  return inherited(idObj, ...);
  }

func SetController(int plr, object obj)
  {
  // Fuer Treibsandminenhagel muss neben dem Controller auch direkt
  // der Besitzer angepasst werden, damit sie nach einem Treffer noch
  // stimmt
  if (GetID(obj) == _QSM) SetOwner(plr, obj);
  return inherited(plr, obj, ...);
  }
