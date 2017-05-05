/*-- Kamaenergie-Versorgung --*/

#strict

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

func CheckKarma()
{
  for(var i = 0; i < GetPlayerCount(); i++)
    if(MMGetChurch(GetPlayerByIndex(i))>0)
      DoKarmaEnergy(1, GetPlayerByIndex(i));
}
