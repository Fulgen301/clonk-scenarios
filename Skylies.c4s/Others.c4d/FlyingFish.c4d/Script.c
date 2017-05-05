/*-- Fisch --*/

#strict
#include ANIM

local Bait; // Verfolgter Köder
local iAgro;

public func IsPossessible() { return(1); }

/* Initialisierung */

protected func Initialize() { if(GetAction() S= "Idle") return(Birth()); }

/* TimerCall mit KI-Steuerung */

protected func Activity()
{		

  // Geräusche machen
 // if (!Random(25)) Sound("Raven*");
  
  // Rückwärtsfliegen? umdrehen
  if (GetXDir()>0 && GetDir() == DIR_Left)  return(TurnRight());
  if (GetXDir()<0 && GetDir() == DIR_Right) return(TurnLeft());

  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();
  if(Contained()) return();
  if(GetCommand()) return();
  
  if(!Random(6)) SetAction("StartFloat");
  
  // Köder fressen
  if(Bait)
    if(ObjectDistance(Bait, this()) <= 25)
      if(GetAction() eq "Swim")
        SetAction("Eat");

  var pBait;
  // Nur wenn der Vogel ausgewachsen ist
  if (GetCon()==100) 
   // Soll nicht zu einfach sein...
   if (!Random(5))
     // Ein Köder in der Nähe?
     while (pBait = FindObject( 0, -250,-250,500,500, 0,0,0,NoContainer(), pBait))
      // Köder?
      if(WildcardMatch(GetAction(pBait), "*MeatBait*"))
       // Je nach Köderqualität...
       if (Random(100) < pBait->~IsBait())
        {
         // ...hinfliegen
         SetCommand(this(), "Follow", pBait);
         // Und Köder merken
         Bait = pBait;
        }

  // Nichts machen
  if (Random(2) || GetAction() ne "Swim") return(1);

  // Nach oben oder unten fliegen
  SetComDir(COMD_Up());
  if (Random(2)) SetComDir(COMD_Down());

  // Nichts machen
  if (!Random(4)) return(1);
  
  // Ein Ei legen
  if (!Random(ReproductionRate())) 
   Reproduction();
  
  // Umdrehen
  if (Random(2)) return(TurnRight());
  return(TurnLeft());
}

private func WalkDir()
{
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
  return(1);
}

/* Kontakte */

protected func Survive()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  // Nicht in Flüssigkeiten oder brennende Objekte fliegen
  if (InLiquid() || GBackLiquid(GetXDir()*2, GetYDir()*2) || GBackLiquid(GetXDir()*3, GetYDir()*3) || FindObject(0, -20 + GetXDir() * 2, -20 + GetYDir() * 2, 40, 40, OCF_OnFire()))
   SetComDir(COMD_Up());
}
protected func SurviveFloat()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())){ return();
  }
  SetYDir(+1);
  
  if(GBackSemiSolid(0,+20)){ 
  SetAction("Swim");
  SetComDir(COMD_Up());
  }
  
  if(!Random(50)){
  // Umdrehen
  if (Random(2)) TurnRight();
  TurnLeft();
  }
  
  if(!Random(50)){ SetAction("Swim"); SetYDir(); }
  // Nicht in Flüssigkeiten oder brennende Objekte fliegen
  if (InLiquid() || GBackLiquid(GetXDir()*2, GetYDir()*2) || GBackLiquid(GetXDir()*3, GetYDir()*3) || FindObject(0, -20 + GetXDir() * 2, -20 + GetYDir() * 2, 40, 40, OCF_OnFire())){
   SetAction("Swim");
   SetComDir(COMD_Up());
    }
}

/* Kontakte */

protected func ContactLeft()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  return(TurnRight());
}

protected func ContactRight()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  return(TurnLeft());
}

protected func ContactTop()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  return(SetComDir(COMD_Down()));
}

protected func ContactBottom()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  return(SetComDir(COMD_Up()));
}


/* Aktionen */

private func TurnRight()
{
  if (Stuck() || (GetAction() ne "Floating" && GetAction() ne "Swim")) return();
  if (GetXDir() < 0) SetXDir(0);
  SetDir(DIR_Right());
  SetComDir(COMD_Right());
  return(1);
}

private func TurnLeft()
{
  if (Stuck() || (GetAction() ne "Floating" && GetAction() ne "Swim")) return();
  if (GetXDir() > 0) SetXDir(0);
  SetDir(DIR_Left());
  SetComDir(COMD_Left());
  return(1);
}

public func Entrance(container) 
{
  // Damit der Fisch nicht aus U-Booten flieht und so.
  SetCommand(this(), "None");
}


/* Einwirkungen */

public func Activate(object pClonk)
{
  [$TxtEmbowel$|Image=KNFE]
  if (pClonk)
    {
    // Aquaclonks (und damit Hydroclonks) können Fische direkt essen
    if (pClonk->~IsAquaClonk()) return(Eat(pClonk));
    // Andere versuchen zu zerlegen (lebende Fische im Inventar dürften ohnehin selten sein)
    return(ObjectSetAction(pClonk, "Embowel", this()));
    }
  return(1);
}

public func Eat(object pByObject)
{
  pByObject->~Feed(50);
  RemoveObject();
  return(1);
}

public func Cook()
{
  ChangeDef(CFSH);
  SetAlive(0);
  return(1);
}

protected func Death()
{
  SetDir(0);
  ChangeDef(DFLH);
  SetAction("Dead");
  GameCallEx("OnFishDeath",this,GetKiller(this));
  return(1);
}

/* Vermehrung */

private func SpecialReprodCond()
{
  return(GetAction() eq "Swim");
}

public func Birth()
{
  var pEnv;
  if (pEnv=FindObject(CLFS)) pEnv->CLFS::Colorize(this());
  else SetColorDw(RGB(255,255,255));
  SetAction("Swim");
  SetComDir(COMD_Left());
  if(Random(2)) SetComDir(COMD_Right());
}

public func RejectEntrance(pContainer)
{
  // Aquaclonks/Hydroclonks können ungeachtet der Regel immer einsammeln
  // (In Tiefsee sind Fische die einzige Möglichkeit, Energie aufzuladen!)
  if (pContainer->~IsAquaClonk()) return();
  // Fischtürme sollten auch immer funktionieren
  if (pContainer->~IsFishTower()) return();
  // ANIM-Definition (Einsammelbare Tiere)
  return(_inherited(pContainer, ...));
}

/* Steuerung durch Besessenheit */

protected func RejectCollect(c4ID, pObject)
{
 var iEffectNumber, pSorcerer;
 if (iEffectNumber = GetEffect("PossessionSpell", this()))
  if (pSorcerer = EffectVar(0, this(), iEffectNumber))
   if (!GetEffect("IntCollectionDelay", this()))
    if (!pSorcerer->Contents())
     if (!(pObject->GetOCF() & OCF_Living()))
      Collect(pObject, pSorcerer);
 return(1);
}

protected func ControlCommand(szCommand, pTarget, iTx, iTy)
{
 // Bewegungskommando
 if (szCommand eq "MoveTo")
  return(SetCommand(this(),szCommand, pTarget, iTx, iTy));
 return(0);
}

protected func ContainedLeft(object caller)
{
  [$TxtMovement$]
  SetCommand(this(),"None");
  if(!GetPlrCoreJumpAndRunControl(caller->GetController()))
    TurnLeft();
  return(1);
}

protected func ContainedRight(object caller)
{
  [$TxtMovement$]
  SetCommand(this(),"None");
  if(!GetPlrCoreJumpAndRunControl(caller->GetController()))
    TurnRight();
  return(1);
}

protected func ContainedUp(object caller)
{
  [$TxtMovement$]
  SetCommand(this(),"None");
  if(!GetPlrCoreJumpAndRunControl(caller->GetController()))
    SetComDir(COMD_Up());
  return(1);
}

protected func ContainedDown(object caller)
{
  [$TxtMovement$]
  SetCommand(this(),"None");
  if(Contained()) return SetCommand(this, "Exit");
  if(!GetPlrCoreJumpAndRunControl(caller->GetController()))
    SetComDir(COMD_Down());
  return(1);
}

/* JumpAndRun-Steuerung */

private func ClearDir(bool fX)
{
  if(fX && GetXDir())
  {
    if(GetXDir() > 0) SetXDir(Max(GetXDir() - 2, 0));
    else SetXDir(Min(GetXDir() + 2, 0));
  }
  if(!fX && GetYDir())
  {
    if(GetYDir() > 0) SetYDir(Max(GetYDir() - 2, 0));
    else SetYDir(Min(GetYDir() + 2, 0));
  }
}

public func ContainedUpdate(object self, int comdir)
{
  SetComDir(comdir);
  ClearScheduleCall(this(), "ClearDir");
  if(comdir == COMD_Down || comdir == COMD_Up) ScheduleCall(this(), "ClearDir", 1, (Abs(GetXDir())+1)/2, true);
  if(comdir == COMD_Left || comdir == COMD_Right) ScheduleCall(this(), "ClearDir", 1, (Abs(GetYDir())+1)/2, false);

  return(1);
}

protected func ContainedThrow()
{
 [$TxtDrop$]
 var iEffectNumber, pSorcerer;
 if (iEffectNumber = GetEffect("PossessionSpell", this()))
  if (pSorcerer = EffectVar(0, this(), iEffectNumber))
  {
   if (pSorcerer->Contents()) pSorcerer->Contents()->Exit(0,0,6);
   AddEffect("IntCollectionDelay", this(), 1, 70);
  }
 return(1);
}

protected func ContainedDigDouble()
{
 [$TxtLeave$]
 RemoveEffect("PossessionSpell", this());
 return(1);
}

/* Aufwertungszauberkombo: Mit Fisch wird der Clonk zum Aquaclonk */
public func GetRevaluationCombo(object pClonk) { return(ACLK); }


/* Zerlegen nach Clonktyp */

protected func GetCustomComponents(object pClonk)
  {
  if (pClonk)
    {
    // Jedem seine Extrawürste
    if (pClonk->~IsTrapper() || pClonk->~IsIndian()) return ([FSHM, FSHM, FSHB]);
    if (pClonk->~IsInuk()) return([MEAT, FAT1, FSHB]);
    //if (pClonk->~IsJungleClonk()) return([MEAT, FAT1, FSHB]); // Jungelclonk kann (noch) nicht zerlegen
    }
  }


/* Kranke Tiere (Arktis) */

public func Sick() { ChangeDef(QFSH);  Birth(); }
