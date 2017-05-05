/*-- Monster --*/

#strict
#appendto MONS

local pMaster;

// Kann mit einem Ritual beschworen werden
public func IsRitual()	 { if(GetID()==_SMS) return(1); }

// Nur für Kirchenlose
public func NeedChurch() { return(-1); }

public func Summoned(pClonk)
{
  if(GetID()==_SMS) return(CreateObject(MONS,0,-10,GetOwner(pClonk))->~Summoned(pClonk),RemoveObject());
  pMaster=pClonk;
  CastParticles("FSpark",10,10,0,0,50,80,RGB(0,255,0),RGB(64,255,64));
}

/* TimerCall mit KI-Steuerung */

private func Activity()
{
  if(!pMaster) return _inherited();
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this)) return();

  // Nichts machen
  if (Random(2) || (GetAction() ne "Walk" && GetAction() ne "Swim")) return(1);

  // Springen
  if (GetAction() eq "Walk")
   if (!Random(3)||((GetY()-GetY(pMaster))>20&&ObjectDistance(this,pMaster)<100)) return(this->~DoJump());

  // Teleporten
  if(ObjectDistance(pMaster)>500)
  {
    CastParticles("FSpark", 10,20,0,0,50,80,RGB(0,255,0), RGB(0,255,0));
    SetPosition(GetX(pMaster), GetY(pMaster));
    CastParticles("FSpark", 10,20,0,0,50,80,RGB(0,255,0), RGB(0,255,0));
  }
  
  // Umsehen
  if (GetAction() eq "Walk")
   if (!Random(8)) return(SetAction("LookUp"));

  // Umdrehen
  if(ObjectDistance(this,pMaster)<100)
  {
    if(Random(2)) TurnLeft(); else TurnRight();
  }
  else if(!Random(5)){ if(GetX()>GetX(pMaster)) return TurnLeft(); else return TurnRight();}
}

/* Aktionen */
protected func ContactLeft()
{
  _inherited();
  if(pMaster)
    if(ObjectDistance(this,pMaster)>100)
      SetComDirTo(pMaster);
}

protected func ContactRight()
{
  _inherited();
  if(pMaster)
    if(ObjectDistance(this,pMaster)>100)
      SetComDirTo(pMaster);
}
      
public func TurnRight()
{
  return(_inherited());
}

public func TurnLeft()
{
  return(_inherited());
}

private func HitCheck()
{
  var obj;
  if(pMaster)
  {
    if(obj = FindObject2(Find_AtPoint(),Find_OCF(OCF_Prey),Find_OCF(OCF_Alive),Find_Hostile(GetOwner(pMaster))))
      Punch(obj, 10);
  }
  else
    _inherited();
  return(1);
}

/* Vermehrung */

func SpecialReprodCond()
{
  if(pMaster) return 0;
  return 1;
}

global func SetComDirTo(pObj)
{
  if(Abs(GetX(pObj)-GetX())<10)
  {
    if(GetY(pObj)>GetY())
      return SetComDir(COMD_Down);
    return SetComDir(COMD_Up);
  }
  if(GetX(pObj)<GetX())
    return SetComDir(COMD_Left);
  return SetComDir(COMD_Right);
}
