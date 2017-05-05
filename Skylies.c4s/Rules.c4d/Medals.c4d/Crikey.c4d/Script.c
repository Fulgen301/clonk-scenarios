/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 1;}
func MedalIndex() {return 11;}

func OnClonkDeath(object pClonk, int iKiller)
{
  var iPlr = GetOwner(pClonk);
  if(iKiller == NO_OWNER || iPlr == NO_OWNER) return false;

  var pHostileFlag = pClonk->FindObject2(Find_ID(FLAG),Find_Owner(iKiller),Find_Hostile(iPlr),Find_Distance(100));
  if(pHostileFlag)
  {
    var pMedal = FindObject(CY_M);
    if(pMedal)
      Reward(pMedal,iKiller);
  }
}
