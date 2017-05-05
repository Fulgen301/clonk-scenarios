/*-- Turrets --*/

#strict
#appendto FK5B
#appendto PC5B
#appendto TC5B

func IsTurret(){ return true; }

global func EkeFindVictim(x, y, w, h, exclude)
{
  for (var victim in FindObjects(Find_InRect(x, y, w, h),
                                 Find_NoContainer(),
                                 Find_Exclude(exclude)))
  {
    var b0 = !ObjectCount(NF5B);
    var b1 = Hostile(GetController(), GetController(victim), 1);
    var b2 = GetOCF(victim) & OCF_Alive();
    var b3 = GetOCF(victim) & OCF_Container();
    var b4 = GetOCF(victim) & OCF_Grab();
    var b5 = GetOCF(victim) & OCF_Inflammable();
    var b6 = victim ->~IsTurret();
    
    if ((b0 || b1) && (b2 || b3 || b4 || (b1 && b5) || b6)) return(true);
  }
  return(false);
}
