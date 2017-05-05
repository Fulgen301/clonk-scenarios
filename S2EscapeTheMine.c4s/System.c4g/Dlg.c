/* Intro message functions (OC has all this in the original pack...) */

#strict 2

static g_speaker_index;

// Get a default speaker; alternating through multiple players if they exist
// (For intro messages)
global func GetNextSpeaker()
{
	return GetCursor(GetPlayerByIndex(g_speaker_index++ % GetPlayerCount(C4PT_User)));
}

// Global message shown to all players in a nice decoration box
global func GlobalMsg(string sMessage, object pSpeaker, string szPortrait)
  {
  // Defaults
  if (!pSpeaker) if (!(pSpeaker = GetNextSpeaker())) return false;
  if (!sMessage) return false;
  if (!szPortrait) if (!(szPortrait = pSpeaker->~GetMsgPortrait())) szPortrait = "1";
  // Portrait ermitteln
  var c,i,p2="";
  if (GetChar(szPortrait) == GetChar("@"))
    {
    // @Portrait: Aus dieser Definition holen
    while (c=GetChar(szPortrait, ++i)) p2 = Format("%s%c", p2, c);
    szPortrait = Format("Portrait:%i::%x::%s", DG69, GetColorDw(pSpeaker), p2);
    }
  else
    {
    var id = GetPortrait(pSpeaker, 1);//GetID(pSpeaker);
    if(!id) id = GetID(pSpeaker);
    // Manche Clonks haben kein eignes Portrait und verwenden Standartportraits
    if(id==ACLK || id==_ACK) id = CLNK;
    if(id==WDSK) id = MAGE;
    // Ansonsten direkt vom Sprecher
    szPortrait = Format("Portrait:%i::%x::%s", id, GetColorDw(pSpeaker), szPortrait);
    }
  var iSpeakerNameLen = 0;
  while (GetChar(GetName(pSpeaker), iSpeakerNameLen)) ++iSpeakerNameLen;
  // Farbe ermitteln
  var dwClr = pSpeaker->~GetDlgMsgColor();
  if (!dwClr) dwClr = GetColorDw(pSpeaker);
  if (!dwClr) dwClr = 255;
  // Nachricht als reguläre Message; Spieler nicht stoppen
  CustomMessage(Format("<c %x>%s:</c> %s", dwClr, GetName(pSpeaker), sMessage), 0, NO_OWNER, 90,70, 0xffffff, MD69, szPortrait);
  return true;
  }
