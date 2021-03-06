/* Wiederbelebung */

#strict
#appendto MRVL

func Activate(pCaster,pRealcaster)
{
  var pClonk=pRealcaster;
  if(!pClonk) pClonk=pCaster;

  var iCount;
  for(var clnk in FindObjects(Find_Distance(ReviveWidth,0,0),Find_Action("Dead")))
  {
    if(iCount>=10) break;
    // Lebende und nicht-Clonks ignorieren
    if(GetAlive(clnk))continue;
    if(!clnk ->~IsClonk())continue;

    // Wird schon belebt?
    if(GetEffect("SummonSkeletons",clnk) || GetEffect("Revival",clnk))continue;

    // In der Nähe?
    var length=GetPathLength(GetX(),GetY(),GetX(clnk),GetY(clnk));
    if(!length || length > ReviveWidth || (!PathFree(GetX(),GetY(),GetX(clnk),GetY(clnk)) && length > ReviveWidth/2))continue;

    // Beleben!
    AddEffect("Revival",clnk,20,5,0,GetID(),GetOwner(pClonk));
    iCount++;
  }

  // Fertig!
  return(1,RemoveObject());
}


public func FxRevivalStart(pTarget,iEffectNumber,fTmp,iPlr)
{
  if(fTmp) return();

  // Spieler sichern
  EffectVar(0,pTarget,iEffectNumber) = iPlr;
  EffectVar(1,pTarget,iEffectNumber) = 0;

  return(1);
}

public func FxRevivalTimer(pTarget,iEffectNumber,iEffectTime)
{
  var x = GetX(pTarget), y = GetY(pTarget);

  // Noch warten?
  if(iEffectTime < 300)
  {
    CreateParticle("PSpark",x,y-20,RandomX(-3,3),RandomX(-3,3),iEffectTime/3,RGB(255,10,10),pTarget);
    return(1);
  }

  // Effekt!
  CastParticles("PSpark",50,20,x,y,50,150,RGB(200,10,10),RGB(255,20,20),pTarget);

  // Spieler nicht mehr vorhanden?
  if(!GetPlayerName(EffectVar(0,pTarget,iEffectNumber))) return(-1);

  // ID herausfinden
  var id = GetID(pTarget);
  if(id == PLDN) id = KNIG;// Paladine wiederbeleben w�re ja hack!

  // Geist erschaffen
  var pClonk = CreateObject(id,x,y+10,EffectVar(0,pTarget,iEffectNumber));
  pClonk->SetAction("KneelUp");
  pClonk->SetBulkAI();
  SetName(GetName(pTarget),pClonk);
  SetPhysical("Energy",30000,2,pClonk);
  DoEnergy(30,pClonk);

  // Effekt anhängen
  AddEffect("Ghost",pClonk,1,0,0,GetID());

  // Geister sind etwas transparent
  SetObjectBlitMode(GFX_BLIT_ClrSfc_OwnClr,pClonk);
  SetClrModulation(RGBa(200,225,255,150),pClonk);
  SetColorDw(GetColorDw(pTarget),pClonk);

  // Leiche wegschaffen
  RemoveObject(pTarget,1);
  return(-1);
}
