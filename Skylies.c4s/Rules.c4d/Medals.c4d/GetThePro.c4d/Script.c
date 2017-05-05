/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 0;}
func MedalIndex() {return 29;}

func OnClonkDeath(object pClonk, int iKiller)
{
  if(GetOwner(pClonk) == NO_OWNER || iKiller == NO_OWNER) return false;
  if(GetOwner(pClonk) == iKiller) return false;
  
  if(IsPro(GetOwner(pClonk),iKiller))
    Reward(this,iKiller);
  return true;  
}

/* Stellt fest, ob iPlr1 im Vergleich zu iPlr2 ein Pro ist :D */
global func IsPro(int iPlr1, int iPlr2)
{
  var iScore1 = GetGeckoScore(iPlr1);
  var iScore2 = GetGeckoScore(iPlr2);

  //Doppelte Punktzahl und ein Mindestunterschied von 500 Punkten? Pro!
  if(iScore1 >= iScore2*2)
    if(iScore1 - iScore2 >= 500)
      return true;
  return false; 
}
