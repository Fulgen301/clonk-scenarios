/*-- Karmaenergie --*/

#strict 2

local iKarmaEnergy; // Die vorhandene Gunst
local iKarmaPrayer; // Die Gunst, die die Beter eigententlich produzieren
local iShow;
local iTime;
local iChurch;
local iChurchService;

global func MaxKarmaEnergy() { return 100000; }

func Create(iPlr, iNewChurch) {
  SetOwner(iPlr);
  if(FindObject(NTCH)) SetVisibility(VIS_Owner);
  else SetVisibility(VIS_Owner | VIS_Allies);
  SetPosition(-50,90);
  var szEnergy = "Energy";
  iChurch = iNewChurch;
  if(iChurch==scBloodchurch)
  {
    SetGraphics("DarkEmpty");
    SetGraphics("DarkFull",this, GetID(), 1, GFXOV_MODE_Action,"0");
  }
  UpdateGraphic();
  return 1;
}

public func AddChurchService()
{
  iChurchService+=36*60*5;
}

public func SetChurch(iNewChurch)
{
  // Grafik entleeren
  for(var i=0; i<10; i++)
    SetGraphics(0, this, 0, i);
  // Neue Kirche speichern
  iChurch = iNewChurch;
  // Grafik anpassen
  if(iChurch==scBloodchurch)
  {
    SetGraphics("DarkEmpty");
    SetGraphics("DarkFull",this, GetID(), 1, GFXOV_MODE_Action,"0");
  }
  UpdateGraphic();
  return 1;
}

protected func Timer(fNoTime)
{
  // Soll immer in Teambesitz bleiben
  CheckOwner();
  if(iShow!=iKarmaEnergy)
  {
    if(Abs(iKarmaEnergy-iShow)<250)
      iShow = iKarmaEnergy;
    else if(iShow<iKarmaEnergy)
      iShow+=250;
    else iShow-=250;
    UpdateGraphic();
  }
  if(iKarmaPrayer>iKarmaEnergy)
    DoMyKarmaEnergy(100,1);
  if(!iKarmaEnergy) return;
  // Effekt!!
  var iColor;
  iTime++;
  if(fNoTime) iTime--;
  if(MMGetChurch(GetOwner())==scBloodchurch)
  {
    iColor = RGB(200+Sin(iTime*2 ,50),150+Cos(iTime*3/2 ,50),0);
    for(var i=1; i<=3; i++)
    SetClrModulation(iColor, this, i);
  }
  else
  {
    iColor = RGB(220+Sin(iTime*2 ,30),220+Sin(iTime*2 ,30),100+Cos(iTime*2,100));
    for(var i=1; i<=9; i++)
    SetClrModulation(iColor, this, i);
  }
  // Automatischer Verlust
  if(!iChurchService && iKarmaPrayer<iKarmaEnergy && (!FindObject(NPRY) || Mod(GetActTime(), 100)))
    DoMyKarmaEnergy(-50,1);
  if(iChurchService) iChurchService--;
}

private func CheckOwner()
{
  // Selbst wenn ein Spieler entfernt wird, bleibt das Objekt in Teambesitz
  if(!Local(23))
    if(!(Local(23) = GetPlayerTeam(GetOwner())))
      return;
  if(GetOwner()==-1)
  {
    for(var i = 0; i < GetPlayerCount(); i++)
      if(GetPlayerTeam(GetPlayerByIndex(i)) == Local(23))
        return SetOwner(GetPlayerByIndex(i));
    // Kein Besitzer mehr gefunden? dann braucht mich die Welt nicht mehr.
    RemoveObject();
  }
  return;
}

public func AdjustOverlay(iAmount, iUnder, iUpper, szName, iIndex, iR, iStart, iEnd)
{
  iAmount = (iAmount-iUnder)*(iEnd-iStart)/(iUpper-iUnder)+iStart;
  iAmount += Mod(iAmount, 2);
  iAmount = BoundBy(iAmount, 0, 74);
  SetGraphics(szName,this, GetID(), iIndex, GFXOV_MODE_Action,Format("%d", iAmount));
  var fsin=-Sin(iR, 1000), fcos=Cos(iR, 1000);
  SetObjDrawTransform(+fcos, +fsin, 520*(75-iAmount)*fsin/1000, -fsin, +fcos, 520*(75-iAmount)*fcos/1000, 0, iIndex);
}

public func DoMyKarmaEnergy(iAmount, fExact)
{
  if(!fExact) iAmount *= 1000;
  if(iKarmaEnergy+iAmount > MaxKarmaEnergy())
    iAmount = MaxKarmaEnergy()-iKarmaEnergy;
  if(iKarmaEnergy+iAmount < 0)
    iAmount = iKarmaEnergy;
  iKarmaEnergy += iAmount;
  UpdateGraphic();
  return iAmount;
}

public func UpdateGraphic()
{
  if(iChurch==scBloodchurch)
  {
    AdjustOverlay(iShow,     0, 38000, "DarkFull1", 1, 0, 12, 50); // 12+iShow*100/MaxKarmaEnergy()
    AdjustOverlay(iShow, 38000, 72000, "DarkFull2", 2, 0, 28, 62); // 28+iShow*100/MaxKarmaEnergy()-38
    AdjustOverlay(iShow, 72000,100000, "DarkFull3", 3, 0, 42, 70); // (42+iShow*100/MaxKarmaEnergy()-72
  }
  else
  {
    SetGraphics("LightFullCenter",this, GetID(), 1, GFXOV_MODE_Base);
    var iValue = Min(iShow*100/MaxKarmaEnergy(),36);
    SetObjDrawTransform(880*iValue/36+120, 0, 0, 0, 880*iValue/36+120, 0, 0, 1);
    AdjustOverlay(iShow, 36000, 44000, "LightFullRing", 2,   0, 52, 74); // 52+(iShow*100/MaxKarmaEnergy()-36-8*0)*275/100
    AdjustOverlay(iShow, 44000, 52000, "LightFullRing", 3, -45, 52, 74);
    AdjustOverlay(iShow, 52000, 60000, "LightFullRing", 4, -90, 52, 74);
    AdjustOverlay(iShow, 60000, 68000, "LightFullRing", 5,-135, 52, 74);
    AdjustOverlay(iShow, 68000, 76000, "LightFullRing", 6,-180, 52, 74);
    AdjustOverlay(iShow, 76000, 84000, "LightFullRing", 7,-225, 52, 74);
    AdjustOverlay(iShow, 84000, 92000, "LightFullRing", 8,-270, 52, 74);
    AdjustOverlay(iShow, 92000,100000, "LightFullRing", 9,-315, 52, 74);
  }
  return;
}

global func DoKarmaEnergy(int iAmount, int iPlr, int fExact)
{
  // Hat da jemand fälschlicher Weise ein Objekt angegeben?
  if(GetType(iPlr)==C4V_C4Object) iPlr = GetOwner(iPlr);
  // Gibt es den Spieler nicht?
  if(!GetPlayerName(iPlr)) return 0;
  var pObj;
  if(pObj = GetKarmaHelper(iPlr))
    return pObj->DoMyKarmaEnergy(iAmount, iPlr, fExact);
}

global func SetKarmaEnergy(int iValue, int iPlr, int fExact)
{
  return DoKarmaEnergy(iValue-GetKarmaEnergy(iPlr,fExact),fExact);
}

global func GetKarmaEnergy(int iPlr, int fExact)
{
  var pObj;
  var iFaktor = 1000;
  if(fExact) iFaktor = 1;
  if(pObj = GetKarmaHelper(iPlr))
    return LocalN("iKarmaEnergy", pObj)/iFaktor;
}

global func GetKarmaHelper(int iPlr)
{
  var pObj;
  // Eigenen Helfer mit passender Kirche suchen
  pObj = FindObject2(Find_ID(KRME), Find_Owner(iPlr));
  // Bei Teamkirchen auch verbündete suchen
  if(!pObj && !FindObject(NTCH))
    pObj = FindObject2(Find_ID(KRME), Find_Allied(iPlr));
  // Keinen gefunden? -> keine Kirche
  if(!pObj)
    return 0;
  return pObj;
}

static const scBloodchurch=1;
static const scLightchurch=2;

global func MMGetChurch(int iPlr) // Entweder Spieler oder Teamkriche, zu empfehlen
{
  var pObj;
  if(pObj = GetKarmaHelper(iPlr))
    return LocalN("iChurch", pObj);
}

global func MMGetPlayerChurch(int iPlr) // Nur SPielerkirche, Teams werden ignoriert
{
  return MMGetChurch(iPlr);
}

global func MMSetPlayerChurch(int iPlr,int iChurch) // Spielerkirche setzen
{
  var pObj;
  if(!(pObj=GetKarmaHelper(iPlr)))
    CreateObject(KRME, 0, 0, iPlr)->Create(iPlr, iChurch);
  else
    pObj->SetChurch(iChurch);
 
  var aAllied = Find_Allied(iPlr);
  if(FindObject(NTCH)) aAllied = Find_Owner(iPlr);
  // Allen Objekten vom Spieler den Wechsel mitteilen
  for(var pObj in FindObjects(aAllied))
    pObj->~OnChurchChange(iChurch);
 
  return 1;
}

global func MMStartPraying(int iAmout, object pPrayer)
{
  if(!pPrayer) pPrayer = this;
  if(!pPrayer) return;
  MMShowHelpMessage("OnStartPraying",GetOwner(pPrayer));
  var pObj;
  if(pObj = GetKarmaHelper(GetOwner(pPrayer)))
    return pObj->StartPraying(pPrayer, iAmout);
}

global func MMStopPraying(object pPrayer)
{
  if(!pPrayer) pPrayer = this;
  if(!pPrayer) return;
  var pObj;
  if(pObj = GetKarmaHelper(GetOwner(pPrayer)))
    return pObj->StopPraying(pPrayer);
}

public func StartPraying(pPrayer, iAmout)
{
  if(!GetEffect("Praying", this))
    AddEffect("Praying", this, 1, 5, this);
  return EffectCall(this, GetEffect("Praying", this), "AddPrayer", pPrayer, iAmout);
}

public func StopPraying(pPrayer, iAmout)
{
  if(!GetEffect("Praying", this))
    return;
  return EffectCall(this, GetEffect("Praying", this), "RemPrayer", pPrayer, iAmout);
}

func FxPrayingStart(pTarget, iNumber, fTmp)
{
  if(fTmp) return;
  EffectVar(2, pTarget, iNumber) = [];
  EffectVar(3, pTarget, iNumber) = [];
}

// 0: Anzahl an Betenden
func FxPrayingAddPrayer(pTarget, iNumber, pPrayer, iAmount)
{
  // Alle Werte anpassen und Clonk in Liste eintragen
  var iIndex = EffectVar(0, pTarget, iNumber);
  EffectVar(0, pTarget, iNumber) += 1;
  EffectVar(1, pTarget, iNumber) += iAmount;
  EffectVar(2, pTarget, iNumber)[iIndex] = pPrayer;
  EffectVar(3, pTarget, iNumber)[iIndex] = iAmount;
  // Gunst neu berechnen
  var iCount = EffectVar(0, pTarget, iNumber);
  var iFaktor = 2000 - 1000/(2**(iCount-1));
  var iKarma = EffectVar(1, pTarget, iNumber)*iFaktor/iCount*3;
  iKarmaPrayer = iKarma;
  return 1;
}

func FxPrayingRemPrayer(pTarget, iNumber, pPrayer)
{
  var pObj, iIndex;
  while(pObj = EffectVar(2, pTarget, iNumber)[iIndex])
  {
    if(pObj == pPrayer)
    {
      // Werte senken
      EffectVar(0, pTarget, iNumber) -= 1;
      EffectVar(1, pTarget, iNumber) -= EffectVar(3, pTarget, iNumber)[iIndex];
      // und aus Liste löschen
      DeleteArrayItem(iIndex, EffectVar(2, pTarget, iNumber));
      DeleteArrayItem(iIndex, EffectVar(3, pTarget, iNumber));
      // Gunst neu berechnen
      var iCount = EffectVar(0, pTarget, iNumber);
      var iFaktor = 2000 - 1000/(2**(iCount-1));
      var iKarma = EffectVar(1, pTarget, iNumber)*iFaktor/iCount*3;
      iKarmaPrayer = iKarma;
      // Effekt löschen wenn keiner mehr betet
      if(!EffectVar(0, pTarget, iNumber)) RemoveEffect("Praying", this);
      return 1;
    }
    iIndex++;
  }
  return 0;
}

func FxPrayingTimer(pTarget, iNumber, iTime)
{
  if(iChurch==scBloodchurch)
    for(var pObj in EffectVar(2, pTarget, iNumber))
      pObj->CreateParticle("PSpark",RandomX(-7,7),RandomX(-7,7),0,-1,15,RGB(180,10,10),pObj,Random(2));
  else
    for(var pObj in EffectVar(2, pTarget, iNumber))
      pObj->CreateParticle("PSpark",RandomX(-7,7),RandomX(-7,7),0,-1,15,RGB(255,255,10),pObj,Random(2));
}
