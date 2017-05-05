/*-- Fledermaus --*/

#strict 2

public func IsPossessible() { return 1; }

public func SearchRange() { if(GetAction()=="Hang") return(50); return(150); }

local pTarget;
local pMaster;

/* Initialisierung */

public func Purchase(int iByPlr, object BuyObject)
{
	var pCultSite = FindObject2(Find_ID(CLST), Find_Allied(iByPlr));
	if(pCultSite)
	{
		pCultSite->Summon(GetID(), BuyObject, 1);
		DrawParticleLine("MSpark", GetX(pCultSite)-GetX(), GetY(pCultSite)-GetY(), GetX(BuyObject)-GetX(), GetY(BuyObject)-GetY(), 20, 100, RGBa(255,255,255,50), RGBa(200,255,255,100), -5);
		Message("", BuyObject, GetName());
		RemoveObject(this);
	}
}

protected func Initialize()
{
  SetAction("Fly");
  if (Random(2)) return SetComDir(COMD_Right);
  return SetComDir(COMD_Left);
}

/* TimerCall mit KI-Steuerung */

protected func FlySound() { Sound("BatFly*"); }

protected func Activity()
{
  // Nur wenn noch lebt
  if(!GetAlive()) return;
  // Ger�usche machen
  if (GetAction()=="Fly") Sound("BatFly*");

  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this)) return;

  // Gegner suchen
  if(!pTarget && !GetCommand())
  {
    if(GetOwner()==-1) pTarget = FindObject2(Find_Distance(SearchRange()), Find_OCF(OCF_CrewMember | OCF_Prey), Find_NoContainer());
    else pTarget = FindObject2(Find_Distance(SearchRange()), Find_Hostile(GetOwner()), Find_OCF(OCF_CrewMember | OCF_Prey), Find_NoContainer());//FindObject(0, -SearchRange(), -SearchRange(), SearchRange()*2, SearchRange()*2, OCF_CrewMember | OCF_Prey, 0, 0, NoContainer());
    if(pTarget) if(GetAction()=="Hang") SetAction("Fly");
  }
  
  // Beute am Maul bei�en
  if (Attack()) return;
  
  // Angreifen
  if(!pMaster || ObjectDistance(pMaster)<300 || OnFire())
  if(pTarget)
  {
    // Wenn Gegner im Haus, tot oder zu weit weg abbrechen    
    if(Contained(pTarget)) { SetCommand(this, "None"); return pTarget=0; }   
    if(!GetAlive(pTarget)) { SetCommand(this, "None"); return pTarget=0; }
    if(ObjectDistance(pTarget)>SearchRange()) { SetCommand(this, "None"); return pTarget=0; }
    // sonst zum Gegner fliegen
    var iFromSide = +1; if (GetX(pTarget)>GetX()) iFromSide = -1;
    SetCommand(this, "MoveTo", 0, GetX(pTarget) + 13 * iFromSide, GetY(pTarget));
    if(iFromSide>0 && GetDir()) TurnLeft();
    if(iFromSide<0 && !GetDir()) TurnRight();
    return;
  }
  if(pMaster && !OnFire())
  {
    if(!GetAlive(pMaster)) return pMaster = 0;
    if(ObjectDistance(pMaster)>150)
    {
      CastParticles("PxSpark", 10,20,0,0,50,80,RGB(100,0,200), RGB(100,0,200));
      SetPosition(GetX(pMaster), GetY(pMaster));
      CastParticles("PxSpark", 10,20,0,0,50,80,RGB(100,0,200), RGB(100,0,200));
    }
    // zum Meister fliegen
    var iFromSide = +1; if (GetX(pMaster)>GetX()) iFromSide = -1;
    SetCommand(this, "MoveTo", 0, GetX(pMaster), GetY(pMaster));
    if(iFromSide>0 && GetDir()) TurnLeft();
    if(iFromSide<0 && !GetDir()) TurnRight();
    return;
  }

  if(GetAction()=="Hang" && GetActTime()>35*30) if(!Random(100)) SetAction("Fly");
  
  // Nichts machen
  if (Random(2) || GetAction() != "Fly") return 1;

  // Nach oben oder unten fliegen
  SetComDir(COMD_Up);
  if (Random(2)) SetComDir(COMD_Down);

  // Nichts machen
  if (!Random(4)) return 1;

  // Umdrehen
  if (Random(2)) return TurnRight();
  return TurnLeft();
}

protected func HitCheck()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this)) return;
}

public func Attack(object pAttack)
{
  // W�hrend des Fliegens kann alle 2 Sekunden einmal gebissen werden
  if (GetEffect("IntAttackDelay", this) || GetAction() != "Fly") return;

  // Beute suchen
  var aEnemy = Find_Not(Find_Owner(-1));
  if(GetOwner()>=0) aEnemy = Find_Hostile(GetOwner());
  pAttack = FindObject2(Find_AtPoint(-10+20*GetDir()), Find_OCF(OCF_Prey), Find_NoContainer(), aEnemy);

  if (!pAttack) return;

  if(GetAlive(pAttack))
  {
    // Schaden machen und schleudern      
    Punch(pAttack);
    if(GetX(pAttack) < GetX(this))
      Fling(pAttack, -1, -1);
    else
      Fling(pAttack, 1, -1);
  }
  
  // Reinbei�en!
  SetAction("Attack");
  Sound("Bat*");
  AddEffect("IntAttackDelay", this, 1, 70);
  return 1;
}

protected func Survive()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this)) return;

  // Nicht in Fl�ssigkeiten oder brennende Objekte fliegen
  if (InLiquid() || GBackLiquid(GetXDir()*2, GetYDir()*2) || GBackLiquid(GetXDir()*3, GetYDir()*3) || FindObject(0, -20 + GetXDir() * 2, -20 + GetYDir() * 2, 40, 40, OCF_OnFire))
   SetComDir(COMD_Up);
}

/* Kontakte */

protected func ContactLeft()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this)) return;

  return TurnRight();
}

protected func ContactRight()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this)) return;

  return TurnLeft();
}

protected func ContactTop()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this)) return;

  return SetComDir(COMD_Down);
}

protected func ContactTop()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this)) return;

  if(!pTarget && !pMaster)
  return SetAction("Hang");
//  return SetComDir(COMD_Up);
}

protected func ContactBottom()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this)) return;

  return SetComDir(COMD_Up);
}

/* Aktionen */

public func TurnRight()
{
  if (Stuck() || GetAction() != "Fly") return;
  if (GetXDir() < 0) SetXDir(0);
  SetDir(DIR_Right);
  SetComDir(COMD_Right); 
  return 1;
}

public func TurnLeft()
{
  if (Stuck() || GetAction() != "Fly") return;
  if (GetXDir() > 0) SetXDir(0);
  SetDir(DIR_Left);
  SetComDir(COMD_Left); 
  return 1;
}

/* Einwirkungen */

protected func CatchBlow(iLevel, pObject)
{
  if (pObject->~IsArrow()) SetAction("Tumble");
  if (!Random(3)) Sound("Bat*");
  return 1;
}

/* Steuerung durch Besessenheit */

protected func ControlCommand(szCommand, pTarget, iTx, iTy)
{
 // Bewegungskommando
 if (szCommand == "MoveTo")
  return SetCommand(this,szCommand, pTarget, iTx, iTy);
 return 0;
}

protected func ContainedLeft()
{
 [$TxtMovement$]
 SetCommand(this, "None");
 TurnLeft();
 return 1;
}

protected func ContainedRight()
{
 [$TxtMovement$]
 SetCommand(this, "None");
 TurnRight();
 return 1;
}

protected func ContainedUp()
{
 [$TxtMovement$]
 SetCommand(this, "None");
 SetComDir(COMD_Up);
 return 1;
}

protected func ContainedDown()
{
 [$TxtMovement$]
 SetCommand(this, "None");
 if(GetAction()=="Hang") SetAction("Fly");
 SetComDir(COMD_Down);
 return 1;
}

protected func ContainedDig()
{
 [$TxtAttack$]
 Attack();
 return 1;
}

protected func ContainedThrow() { return 1; }

protected func ContainedDigDouble()
{
 [$TxtLeave$]
 RemoveEffect("PossessionSpell", this);
 return 1;
}

public func Summoned(pClonk)
{
  pMaster = pClonk;
  ScheduleCall(this, "CreateBat", 12, 2);

  AddEffect("FriendProtection",this,20,2,this);
}

public func CreateBat()
{
  var pBat = CreateObject(BAT1, 0, 0, GetOwner());
  LocalN("pMaster", pBat) = pMaster;
  AddEffect("FriendProtection",pBat,20,0,pBat);
}

/* Schutz vor Freunden */

public func FxFriendProtectionStart(pTarget,iEffectNumber)
{
  return 1;
}

public func FxFriendProtectionDamage(pTarget,iEffectNumber,iDmgEngy,iCause,iPlr)
{
 if(GetPlayerName(iPlr))
   if(!Hostile(iPlr,GetOwner(pTarget)))
   {
    if(iCause == 35) { Extinguish(pTarget); return; }
    if(iDmgEngy > 0) return iDmgEngy;
    return 0;
   }
 
 return iDmgEngy;
}

// Kann mit einem Ritual beschworen werden
public func IsRitual()   { return 1; }

// Nur f�r die Blutkirche
public func NeedChurch() { return scBloodchurch; }

// Kann nicht in der Werkstatt produziert werden
public func RejectWorkshopConstruction(){return true;}
