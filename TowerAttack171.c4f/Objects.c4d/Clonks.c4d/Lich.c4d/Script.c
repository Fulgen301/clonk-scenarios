/* Lich */

#strict

#include MAGE

local alreadyInfo;

// Der Magier kann den Stab verwenden
public func CanUse(id)
{
  if(id == SMOD) return(true);

  return(false);
}

public func Collection2(object pObj)
{
  if(bNoStaff) return(0);
  // Stäbe werden beim einsammeln "geschluckt"
  if(pObj->~IsStaff())
  {
    // Der Stab wird aufgenomen und ein Bild für das Inventar gesetzt
    pStaff = pObj;
    pStaffPict = CreateObject(MGST, 0, 0, GetOwner());
    pStaffPict->SetStaff(pStaff, this);
    SetGraphics("Wear", this, GetID(pStaff), 1, GFXOV_MODE_ExtraGraphics);
    return();
  }
  // Stabbild anpassen
  if(pStaffPict) SetPosition(60,-25, pStaffPict);
}

protected func Initialize()
{
  // Wassereffekt anhängen
  AddEffect("SkeletonWaterCheck",this,20,1,this);
  if(ObjectCount(FSTF) || !fInitialized)
    if(!FindContents(SMOD)) CreateContents(SMOD);
  fInitialized = 1;
  return(_inherited());
}

protected func Recruitment()
{
  if(!alreadyInfo)
  {
    alreadyInfo = 1;
    var clnk = CreateObject(MAGE,0,0,GetOwner());
    MakeCrewMember(clnk,GetOwner());
    GrabObjectInfo(clnk,this);
    RemoveObject(clnk);
    DoEnergy(100);
  }
  // Portrait setzen
  SetPortrait("1");
  DoEnergy(100);
  return(_inherited());
}

// Zur Sicherheit, damit Überladungen keinen Fehler beim Starten geben
protected func Scaling()
{
  var szDesiredAction;
  if (GetYDir()>0) szDesiredAction = "ScaleDown"; else szDesiredAction = "Scale";
  if (GetAction() ne szDesiredAction) SetAction(szDesiredAction);
  return(1);   
}

protected func ContactBottom()
{
  // Skelette können am Grund eines Sees laufen
  if (InLiquid())
    SetAction("Walk");
  return(1);
}

protected func Death()
{
  _inherited(Par(),Par(1),Par(2));
 
  if(this)
    if(!GetAlive())
    {
      CastObjects(BONE,4,10);
      RemoveObject(0,1);
    }
  return(1);
}

/* Essen */  

public func Feed(iLevel)
{
  // Schon mal ein Skelett essen sehen?
  CastParticles ("DoughSlice", Random(3)+4, 13, 0,0, 30,35, RGB(170,115,60), RGB(145,95,50));
  Sound("WoodHit*");Sound("WoodHit*");
  return(1);
}

protected func FxSkeletonWaterCheckTimer(pTarget,iEffectNumber)
{
  // Im Wasser beim Springen...
  if(!InLiquid()) return(1);
  if(GetAction() ne "Jump" && GetAction() ne "Tumble") return(1);
  if(!GetXDir() && !GetYDir()) return(1);
  
  // ... wird das Skelett leicht abgebremst
  var xDir = GetXDir();
  if(GetXDir() > 16) xDir=(GetXDir()*7)/8;
  var yDir = GetYDir();
  if(GetYDir() > 16) yDir=(GetYDir()*7)/8;
  SetXDir(xDir);
  SetYDir(yDir);
  
  return(1);
}

// Böser Effektmissbrauch! :O
protected func FxSkeletonWaterCheckDamage(pTarget,iEffectNumber,iDmg,iCause)
{
  // Feuer ist einfach immer böse
  if(iCause == 35) return(iDmg);
  // Explosionen auch!
  if(iCause == 1)  return(iDmg);
  // Heilen sowiesoüberhauptundeh!
  if(iDmg > 0)return(iDmg);
 
  // Im Nahkampf nur etwas abschwächen
  if(iCause == 40) return((iDmg/10)*9);
 
  return((iDmg/10)*6);
}

public func ControlDown()
{
  // Skelett kann sich "tot" stellen
  if(GetPlrDownDouble(GetOwner()) && GetAction() eq "Walk") SetAction("Dead");
  if(_inherited(Par(),Par(1))) return 1;
}

public func ControlUp()
{
  // Nach dem "Tot-Stellen" wieder aufstehen
  if(GetAction() eq "Dead") ObjectSetAction(this,"FlatUp",0,0,1);
  if(_inherited(Par(),Par(1))) return 1;
}

/* Itemlimit */
public func MaxContentsCount() { return(1); }

public func IsMagiclonk() { return(1);}

private func SpecialSpellsA(&idSpell)
{
  if (idSpell ==  RUND) // Keine Untoten raisen
  {
    var temp=[MSMN,MRVL];
    idSpell = temp[Random(GetLength(temp)-1)];
    if(!(this->AI_CanCast(idSpell)))
      idSpell = temp[Random(GetLength(temp)-1)];
  }
  _inherited();
}
