/*-- Funktionen --*/

#strict 2

static const SBRD_Kill = 0;
static const SBRD_Score= 1;
static const SBRD_Gecko= 2;
static const SBRD_Change= 3;

global func UpdateScoreboard(int iPlr)
{
  SetScoreboardData(iPlr,SBRD_Caption,GetTaggedPlayerName(iPlr));
  SetScoreboardData(iPlr,SBRD_Kill,Format("%d",aKills[iPlr]));
  SetScoreboardData(iPlr,SBRD_Score,Format("%d",aValue[iPlr]));
  SetScoreboardData(iPlr,SBRD_Gecko,Format("%d",GetGeckoScore(iPlr)) );
  SetScoreboardData(iPlr,SBRD_Change,Format("%d",aLastChange[iPlr]) );
  SetScoreboardData(SBRD_Caption,SBRD_Caption,"Scoreboard");
  SetScoreboardData(SBRD_Caption,SBRD_Kill,Format("{{MELE}}"));
  SetScoreboardData(SBRD_Caption,SBRD_Score,"{{GLDM}}");
  SetScoreboardData(SBRD_Caption,SBRD_Gecko,"{{SCOR}}");
  SetScoreboardData(SBRD_Caption,SBRD_Change,"{{SCCH}}");
  //  SetScoreboardData(SBRD_Caption,SBRD_Relaunches,"{{MGHL}}");
  SortScoreboard(SBRD_Kill);
// AddEvaluationData(Format("", GetGeckoScore(iPlr),GetGeckoScore(iPlr)-aOldScore[iPlr]),GetPlayerID(iPlr));
  return true;
}

global func Fail() {return false;}