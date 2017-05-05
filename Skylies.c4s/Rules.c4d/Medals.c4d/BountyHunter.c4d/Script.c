/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 0;}
func MedalIndex() {return 1;}

//Einen frame später prüfen, weil dann das Geld gilt (geld gilt ...höhö)
func OnClonkDeath(object pClonk, int iKiller)
{
  AddEffect("Check",this,100,1,this,0,iKiller);
  return true;
}

func FxCheckStart(object pTarget, int iIndex, int iTime, int iKiller)
{
  EffectVar(0,pTarget,iIndex) = iKiller;
  return true;
}

func FxCheckStop(object pTarget, int iIndex, int iReason)
{
  var iKiller = EffectVar(0,pTarget,iIndex);
  if(aValue[iKiller] >= 500)
    Reward(this,iKiller);
  return true;
}
