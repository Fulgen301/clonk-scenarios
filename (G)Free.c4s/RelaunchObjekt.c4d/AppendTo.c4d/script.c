/*-- Neues Script --*/

#strict
local god;
local iEffectTime;
#appendto MAGE


protected func Death(pKiller)
{

  DeathAnnounce();
  // Letztes Mannschaftsmitglied tot: Script benachrichtigen
  if (!GetCrew(GetOwner()))
    GameCall("RelaunchPlayer",GetOwner());
  CastObjects(BUM2, 8+Random(3), 80-Random(Random(Random(120))), 0, -8);
 Sound("Poff");

     var help=CreateObject(GetID());
    GrabObjectInfo(this(),help);
    RemoveObject(help,1);
  return(1);
}
protected func Initialize()
{
AddEffect("Int",this(),1, 1,this(), BNDT);
return(_inherited());
}

func FxIntStart(object pTarget, int iEffectNumber, int iTemp)
{
  // Zeit setzen
  EffectVar(0, pTarget, iEffectNumber) += 300;
}
//effekt
func FxIntTimer(object pTarget, int iEffectNumber, int iEffectTime)
{
  if(EffectVar(0, pTarget, iEffectNumber) <= 0) {
    SetCategory(2056, pTarget);
    return(-1);
    }
  SetCategory(4);
CreateParticle("PSpark", Cos(iEffectTime*2,     12), Sin(iEffectTime*2,     12), 0, 0, 35, RGB(0,0,255),pTarget);
CreateParticle("PSpark", Cos(iEffectTime*2+240, 12), Sin(iEffectTime*2+180, 12), 0, 0, 35, RGB(0,255,0),pTarget);
CreateParticle("PSpark", Cos(iEffectTime*2+120, 12), Sin(iEffectTime*2+90, 12), 0, 0, 35, RGB(255,0,0),pTarget);
  EffectVar(0, pTarget, iEffectNumber)--;
}

func FxIntDamage(object pTarget, int iEffectNumber, int iDmgEngy, int iCause)
{
  if(iCause != 32) return(1);
}


public func QueryCatchBlow(a,b,c,d){
if(god)return(1);

return(_inherited(a,b,c,d));
}

public func NoMoreGod()
{
god=0;
Message("",this());
SetClrModulation(RGBa(255,255,255,0));
}

public func BecomeGod()
{
god=1;
Message("@<c %x>GOD</c>",this(),RGB(0,255,0));
SetClrModulation(RGBa(0,255,0,100));
ScheduleCall(this(),"NoMoreGod",GlobalN("godtime"),0);
}



