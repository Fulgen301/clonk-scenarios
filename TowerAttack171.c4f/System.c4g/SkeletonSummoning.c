/* Skelette! */

#strict
#appendto MSMN

func Activate(pCaster,pRealcaster)
{
  var pClonk=pRealcaster;
  if(!pClonk) pClonk=pCaster;

  var iCount;
  // Tote Clonks in der Nähe absuchen
  for(var clnk in FindObjects(Find_Distance(ReviveWidth,0,0),Find_Action("Dead")))
  {
    if(iCount>=10)
      break;
    // Lebende und nicht-Clonks ignorieren
    if(GetAlive(clnk)) continue;
    if(!clnk ->~IsClonk()) continue;

    // Wird schon belebt?
    if(GetEffect("SummonSkeletons",clnk) || GetEffect("Revival",clnk)) continue;

    // In der Nähe?
    var length = GetPathLength(GetX(),GetY(),GetX(clnk),GetY(clnk));
    if(!length || length > ReviveWidth || (!PathFree(GetX(),GetY(),GetX(clnk),GetY(clnk)) && length > ReviveWidth/2)) continue;

    // Beleben!
    AddEffect("SummonSkeletons",clnk,20,5,0,GetID(),GetOwner(pClonk));
    iCount++;
  }

  // Fertig!
  return(1,RemoveObject());
}

public func FxSummonSkeletonsStart(pTarget,iEffectNumber,fTmp,iPlr)
{
  if(fTmp) return();

  // Spieler sichern
  EffectVar(0,pTarget,iEffectNumber) = iPlr;
  EffectVar(1,pTarget,iEffectNumber) = 0;

  return(1);
}

public func FxSummonSkeletonsTimer(pTarget,iEffectNumber,iEffectTime)
{
  var x=GetX(pTarget), y=GetY(pTarget);

  // Effekt!
  CreateParticle("PxSpark",x+RandomX(-10,10),y+7+RandomX(-6,2),0,-3,40+Random(20),RGB(255,255,255));
  // Noch warten
  if(iEffectTime < 90)return(1);

  // Spieler nicht mehr da?
  if(!GetPlayerName(EffectVar(0,pTarget,iEffectNumber))) return(-1);

  // Skelett erschaffen
  var pClonk = CreateObject(SKLT,x,y+10,EffectVar(0,pTarget,iEffectNumber));
  pClonk->SetAction("KneelUp");
  pClonk->SetBulkAI();

  // Leiche beseitigen
  RemoveObject(pTarget,1);
  return(-1);
}
