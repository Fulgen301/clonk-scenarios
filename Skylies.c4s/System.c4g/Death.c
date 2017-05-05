/*-- Clonk --*/

#strict 2
#appendto CLNK

local iLastDamager;
local iFlightDistance;

public func & idDamage() { return Local(57); }

public func Damage(int iChange, int iByPlayer) {
  iLastDamager = iByPlayer;
  return _inherited(iChange, iByPlayer);
}

public func Initialize() {
  if(!GetEffect("DamageCounter", this())) AddEffect("DamageCounter", this(), 1, 0, 0, 0);
  iLastDamager = -1;
  return _inherited();
}

global func FxDamageCounterDamage (object pTarget, int iEffectNumber, int iDmgEngy, int iCause) {
  var idID = 0;
  if(iCause == 33) idID = BLST; // Explosion
  if(iCause == 35) idID = FLAM; // Feuer
  if(iCause == 37) idID = SUFO; // Ersticken
  if(iCause == 38) idID = ACID; // Säure
  if(idID) pTarget->~NewDamageID(idID);
  if(iDmgEngy <= -40000)
  {
    var plr = LocalN("iLastDamager",this);
    var pMedal = FindObject(CH_M);
    if(pMedal)
      Reward(pMedal,LocalN("iLastDamager",this));
  }

  return iDmgEngy;
}

public func QueryCatchBlow(pBy) {
  idDamage() = GetID(pBy);
  return _inherited(pBy);
}

public func NewDamageID(id idID, pObj) {
  idDamage() = idID;
}

global func Punch(object pObj, int iX) {
  if(this() && pObj) pObj->~NewDamageID(GetID(this()));
  return _inherited(pObj, iX);
}

global func DoEnergy(int iChange, object pObj) {
  if(this() && pObj) pObj->~NewDamageID(GetID(this()));
  return _inherited(iChange, pObj);
}

public func ControlThrow() {
  // Beim Werfen Besitzer setzen (für genauere Fragzuordnung)
  if(Contents()) SetOwner(GetOwner(), Contents());
  return _inherited();
}

//protected func Death(int iKilledBy) {
//  CreateDeathLog(iKilledBy);
//  return _inherited(iKilledBy);
//}

protected func Death(int iKilledBy) {
  if(iKilledBy == -1) iKilledBy = iLastDamager;
  CreateDeathLog(iKilledBy);

  // Info-Broadcasts für sterbende Clonks
  GameCallEx("OnClonkDeath", this(), iKilledBy);
  AddTot(GetOwner());
  // Der Broadcast könnte seltsame Dinge gemacht haben: Clonk ist noch tot?
  if (GetAlive()) return 0;

  for(var pObj in FindObjects(Find_Container(this))) {
    Exit(pObj);
    SetXDir(GetXDir(this, 100), pObj, 100);
    SetYDir(GetYDir(this, 100), pObj, 100);
  }
   /* CRIKEY! */
  var pHostileFlag = FindObject2(Find_ID(FLAG),Find_Hostile(GetOwner()),Find_Distance(100));
  if(pHostileFlag)
  {
    var pMedal = FindObject(CY_M);
    if(pMedal && GetOwner(this) != NO_OWNER)
      Reward(pMedal,iKilledBy);
   }

  Sound("Die");
  DeathAnnounce();
  // Letztes Mannschaftsmitglied tot: Script benachrichtigen
  if (!GetCrew(GetOwner()))
    GameCallEx("RelaunchPlayer", GetOwner(), this(), GetKiller());
  return 1;
}

protected func Destruction() {
  if(GetOwner() != -1) Kill();
}

protected func CreateDeathLog(int iKilledBy) {
  var iPlr = GetOwner(this);
  if(!GetPlayerName(iPlr))
    return 0;

  if(iPlr != NO_OWNER)
  {
    if(iKilledBy != NO_OWNER && iKilledBy != iPlr)
      return(ShowMessage("$MsgItem1$", Format("<c %x>%s</c>", GetPlrColorDw(iKilledBy), FilterClanTag(GetPlayerName(iKilledBy))), idDamage(), Format("<c %x>%s</c>", GetPlrColorDw(iPlr), FilterClanTag(GetPlayerName(iPlr)))));
    if(iKilledBy == NO_OWNER || iKilledBy == iPlr)
      return(ShowMessage("$MsgSelf1$", Format("<c %x>%s</c>", GetPlrColorDw(iPlr), FilterClanTag(GetPlayerName(iPlr))), SKUL));
  }
  return(Log("! Test: iPlr: %v; iKilledBy: %v", iPlr, iKilledBy));
}

/* NYAN WIPF CHECK */


protected func CheckStuck()
{
  if(GetAction() == "Tumble")
  {
    iFlightDistance+=Distance(GetXDir(),GetYDir());   // Count ocunt ocun!
    // Message("%d",this(),iFlightDistance);
    if(iFlightDistance >= 1600)
    {
      var pMedal = FindObject(NY_M);
      if(pMedal && GetOwner(this) != NO_OWNER)
        Reward(pMedal,GetOwner(this));
    }
  }
  if(GetAction() != "Tumble")
    iFlightDistance = 0;
}
