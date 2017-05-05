/*-- SCORE --*/

#strict

 static aScore; // Score (iPlr)
 static aKillsSerie; // Mehr Kills bei ein Leben? Na das ist doch Wunderbar!
 static aKillsBonusTime; // Omg der ist richtig krank, das gefaellt Scory!
 static aLastChange; // Letzte Änderung
 static const Sz_GeckoScoreObject = "SKYM_Score"; // Naja diesmal sind wir Skymayhem spielen und so.

 func Initialize(){
 aScore = [];
 aKillsSerie = [];
 aKillsBonusTime = [];
 aLastChange = [];
 AddMsgBoardCmd("resetscore","ResetScore(%player%)");
 return(1);
}
global func ScoreInitPlayer(int iPlr) {
  aOldScore[iPlr] = GetPlrExtraData(iPlr, Sz_GeckoScoreObject);
 aScore[iPlr] = GetPlrExtraData(iPlr, Sz_GeckoScoreObject);
 aKillsSerie[iPlr] = 0;
 aKillsBonusTime[iPlr] = 0;
 aLastChange[iPlr] = 0;
  return(1);
}
func Check() {
 var countPlr = GetPlayerCount(); // Alle Spieler

 // ... abklappern
 for(var i = 0; i < countPlr; i++){
  // Hast du i Killzeitbonus? Naja der wird aber auch weniger.
  if(aKillsBonusTime[GetPlayerByIndex(i)] > 0){
  aKillsBonusTime[GetPlayerByIndex(i)]--;
  PlayerMessage(i,"<c ff0000>!</c>",GetCursor(i));
   }
  }
  return(1);
}
global func AddKill(int iKiller, int iOpfer) { // Fügt ein Kill hinzu und rechnet die Punkte
AddKillToKillSerie(iKiller);
var iUltra = aKillsSerie[iKiller];
if(iUltra == 0){ iUltra = 1; }
var iGround = (3+RandomX(1,5)*(aScore[iOpfer]/50))+(aKillsBonusTime[iKiller]/10);
var iScore = iGround * iUltra;
aLastChange[iKiller] = iScore;
aKillsBonusTime[iKiller] = 200;
AddScore(iScore,iKiller);
return(1);
}
global func GetKillToKillTime(int iPlr){ return(aKillsBonusTime[iPlr]); }

global func AddKillToKillSerie(int iPlr) {
aKillsSerie[iPlr] = aKillsSerie[iPlr]+1;
return(aKillsSerie[iPlr]);
}
global func AddScore(int iScore, int iPlr)
{
  var pClonk = GetCursor(iPlr);
  // So wechselt der Score
  ExtraMessage(Format("%d",iScore),SCOR,GetColorDw(pClonk),pClonk);
  aScore[iPlr] = aScore[iPlr]+iScore;
  if(iScore > 500) {
    var pMedal = FindObject(UB_M);
    if(pMedal && iPlr != NO_OWNER)
    Reward(pMedal,iPlr);
  }
  if(aScore[iPlr] < 0){ aScore[iPlr] = 0; }
  SetPlrExtraData(iPlr,Sz_GeckoScoreObject,aScore[iPlr]);
  UpdateScoreboard(iPlr);
  return(aScore[iPlr]);
}

global func GetGeckoScore(int iPlr) { // Musste ich so nennen, GetScore gabs schon. Gibt Score Iplr Wiedr
 return(aScore[iPlr]);
}

global func AddTot(int iPlr) { // Der Tot kostet Punkte. Je mehr man hat, desto mehr kostet er.
var multi = aScore[iPlr]/100;
if(multi < 0) multi = 1; // Damit man auch 0 Punkte kriegen kann.
var iGround = -RandomX(2,4)*(multi)-(aScore[iPlr]/75);            // Verextremt
aLastChange[iPlr] = iGround;
var iScore = iGround;
aKillsSerie[iPlr] = 0;
AddScore(iScore,iPlr);
return(1);
}
/*
global func ResetGeckoScore(int iPlr)
{
  SetPlrExtraData(iPlr,GeckoScoreObject,0);
  PlrMessage("Geckoscore reset.",iPlr);
  Sound("Ding",true,0,100,iPlr);
  return (1);
} */
global func ResetScore(int iPlr)
{
  aScore[iPlr] = 0;
  SetPlrExtraData(iPlr,Sz_GeckoScoreObject,0);
  Sound("Ding",true,0,100,iPlr);
  ShowMessage(Format("{{SCCH}} $ResetMessage$",GetTaggedPlayerName(iPlr)));
  return true;
}