/* Mystiker */

#strict 2
#appendto MYST

/* Super-T-Flint */
private func ActivateMysticSTFN(pClonk)
{
  return CreateObject(FGOB,,, GetOwner(pClonk))->Activate(pClonk);
}

/* Metall */

private func ActivateMysticMETL(object pClonk)
{
  return CreateObject(MSSH, 0, 0, GetOwner(pClonk))->Activate(pClonk);
}

private func MysticTimeMETL()
{
  return 36 * 70;
}

private func MysticTimeSKUL() {
  return 1;
}

private func MysticTimeGold() {
 return 50;
}

/* Airpedo */

private func ActivateMysticARPD()
{
  return DoSpellAim(this);
}

private func ActivateAngleARPD(object pClonk, int iAngle)
{
  CreateObject(ARP2, Sin(iAngle, 5), 4 - Cos(iAngle, 5), GetOwner(pClonk))->~Launch(iAngle, pClonk);
}

private func IsAimerSpellARPD()
{
  return true;
}

private func MysticTimeARPD()
{
  return 36 * 35;
}

protected func QueryCatchBlow(object pObj)
{
  if (GetID(pObj) == ARP2 && pObj->~NoCatchBlow(this))
    return true;
  return _inherited(pObj, ...);
}

//Mysti errort nicht und verbraucht Rollen/Bücher ordnungsgemäß

public func AimingAngle(int iAngle)
  {
  // Zauber weg?
  if (!pAimedSpell) return OnAimerAbort(iAngle);
  if(GetActMapVal("Name", "AimMagic") )
    if(GetAction() == "Walk" || GetAction() == "Magic")
      SetAction("AimMagic");

  // Phase anpassen
  if(GetAction() == "AimMagic")
    {
    // Auch richtigen Winkel verwenden wenn nach links gedreht
    var iHalfAngle = iAngle;
    if(iHalfAngle < 0) iHalfAngle = -iHalfAngle;
    SetPhase(BoundBy((iHalfAngle + 9) / 18, 0, 9) );
    }
  // Weitergabe an den Zauber
  if(eval(Format("this->~AimingAngle%i(Object(%d), %d)", GetID(pMagicObject), ObjectNumber(this), iAngle))) return 1;
  if (pMagicObject)
    return pMagicObject->~AimingAngle(this, iAngle);
}

public func MysticTime(pObj)
{
  var id = GetID(pObj);
  var iTime;
  // Zeit im Mystiker gespeichert?
  if(iTime = eval(Format("this->~MysticTime%i(Object(%d))", id, ObjectNumber(this)))) return iTime;
  // oder vll doch im Objekt selber?
  if (pObj)
    return pObj->~MysticTime();
}

public func IsAimerSpell(pObj)
{
  var id;
  if (GetType(pObj) == C4V_C4ID)
    id = pObj;
  else
    id = GetID(pObj);
  // Zeit im Mystiker gespeichert?
  if(eval(Format("this->~IsAimerSpell%i()", id))) return 1;
  // oder vll doch im Objekt selber?
  if(pObj)
    return pObj->~MysticTime();
}

public func ExecMagic(pObj)
{
  pObj = CastAny(pObj);
  if(!pObj || GetType(pObj) != C4V_C4Object) return 0;
  if(GetEffect("MysticDelay", pObj)) return 0;
  pMagicObject = pObj;
  if(ActivateMystic(pObj))
    if(!pAimer)
      AddEffect("MysticDelay", pMagicObject, 1, MysticTime(pMagicObject));
  return 1;
}