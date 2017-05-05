/* Wer dies ließt, ist doof! */

#strict 2

func Initialize() 
{
  AddEffect("Blah",this,100,100,this);
  return true;
}

func RejectEntrance(object pClonk)
{
  return pClonk->~IsClonk() && Hostile(GetOwner(this),GetOwner(pClonk));
}

func FxBlahTimer(object pTarget, int iIndex, int iTime)
{
  var iPlr = GetOwner(pTarget);
  if(!GetPlayerName(iPlr) || Random(3)) return false;

  var aClonks = FindObjects(Find_Distance(100),Find_Hostile(iPlr),Find_OCF(OCF_CrewMember|OCF_Alive));

  if(GetLength(aClonks))
  {
    var pClonk = aClonks[Random(GetLength(aClonks))];
    Message("<c b0ffffff>%s</c>",pTarget,AbusePlayer(GetOwner(pClonk)));
  }

  return true;
}

global func AbusePlayer(int iPlr)
{
  if(!GetPlayerName(iPlr)) return "";
  
  var a1 = $Part1$;
  var a2 = $Part2$;
  
  var szMessage = Format("%s, $You$%s %s!",GetPlayerName(iPlr),a1[Random(GetLength(a1))],a2[Random(GetLength(a2))]);

  return szMessage;
}

/* Der Stein wurde von pCaster hergezaubert */
func CreatedByMagic(object pCaster)
{
  if(!GetAlive(pCaster) || GetOwner(pCaster) == NO_OWNER) return false;
  var pMedal = FindObject(SW_M);
  if(pMedal)
    Reward(pMedal,GetOwner(pCaster));

  return true;
}
