/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 0;}
func MedalIndex() {return 2;}

local aBridgeCount;

func Initialize()
{
  aBridgeCount = [];
  return true;
}

func OnBridgeFix(bool fFix, object pBridge)
{
  var iPlr=GetOwner(pBridge);
  if(iPlr != NO_OWNER)
  { 
    aBridgeCount[iPlr] = Max(aBridgeCount[iPlr] + fFix*2-1);
    
    if(aBridgeCount[iPlr] >= 10)
      Reward(this,iPlr);
  }
  return true;
}
