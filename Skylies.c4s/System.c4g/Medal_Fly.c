/*-- Universal-append --*/

#strict 2
#appendto *

/* ---------- Dieser Script managed fliegende Objekte ---------- *\

Folgende Effektvariabeln im Flugeffekt sind reserviert:
EffectVar(0) = Kills. Index: Verfeindete, Verbündete, Eigene.
EffectVar(1) = Die letzten 2 Rückschlagswolken, die es reflektiert haben.
EffectVar(2) = Das Objekt wurde mit einem normalen Rückschlag zurückgeschleudert.
EffectVar(3) = Die ID der Waffe, beim normalen Werfen ist es der Clonk.
EffectVar(4) = Der Spieler, der das Teil geschossen hat.

\* ------------------------------------------------------------- */

// Objekt wird aus einem anderen herausbefördert.
func Departure(object pContainer)
{
  //Das Objekt kann Lebewesen erschlagen? Prima. Effekt anhängen
  if(GetCategory(this) & C4D_Object)
    if(!Contained(pContainer) && GetAction(pContainer) != "Grab")
      AddEffect("Flight",this,100,5,this,0,GetID(pContainer),GetController(pContainer));
  return _inherited(...);
}

global func FxFlightStart(object pTarget, int iIndex, int iTemp, id idWpn, int iShooter)
{
  EffectVar(0,pTarget,iIndex) = [];
  EffectVar(1,pTarget,iIndex) = [];
  EffectVar(3,pTarget,iIndex) = idWpn;
  EffectVar(4,pTarget,iIndex) = iShooter;
  return true;
}

global func FxFlightTimer(object pTarget, int iIndex, int iTime)
{
  //Der Effekt endet, wenn das Objekt wieder liegt oder eingesammelt ist.
  if(!GetXDir(pTarget) && !GetYDir(pTarget) || Contained(pTarget)) return -1;
  return true;
}

global func FxFlightStop(object pTarget, int iIndex, int iReason)
{
  //Objekt ist fertig geflogen? Belohnen, wenn der Spieler toll war.
  EffectCall(pTarget,iIndex,"Medals");
  return true;
}

global func FxFlightKill(object pTarget, int iIndex, int iPlr)
{
  //Verfeindete Clonks umgenietet? Sehr schön.
  if(Hostile(GetController(pTarget),iPlr))
    EffectVar(0,pTarget,iIndex)[0]++;

  //Verbündete Clonks? Aua. Schäm dich!
  else
    EffectVar(0,pTarget,iIndex)[1]++;

  //Einer der ursprünglichen Clonks wurde getroffen?
  if(iPlr == EffectVar(4,pTarget,iIndex))
    EffectVar(0,pTarget,iIndex)[2]++;

  return true;
}

global func FxFlightReflection(object pTarget, int iIndex, object pSpell, bool fCloud)
{
  //Das Objekt wird zurückgeschlagen. Das bedeutet, dass im Prinzip ein neuer Flug beginnt
  //Also Medaillen vergeben und Werte zurücksetzen.
  
  EffectCall(pTarget,iIndex,"Medals");
  EffectVar(0,pTarget,iIndex) = [];

  if(!fCloud)
  {
    EffectVar(2,pTarget,iIndex) = true;
    SetController(GetOwner(pSpell),pTarget);
  }
  
  else
  {
    var aClouds = EffectVar(1,pTarget,iIndex);
    if(GetType(aClouds) != C4V_Array || !GetLength(aClouds))
      aClouds = [];
  
    //Wir haben einen Loop und es sind 2 unterschiedliche Spieler? Medaille!
    if(aClouds[1] == pSpell)
    {
      var iPlr1 = GetOwner(aClouds[0]);
      var iPlr2 = GetOwner(aClouds[1]);
      if(iPlr1 != iPlr2)
      {
        var pMedal = FindObject(PP_M);
        if(pMedal)
        {
          Reward(pMedal,iPlr1);
          Reward(pMedal,iPlr2);
        }
      }
    } 

    //Array weiterschieben.
    aClouds[1] = aClouds[0];
    aClouds[0] = pSpell;

    //Und speichern.
    EffectVar(1,pTarget,iIndex) = aClouds;
  }
}

global func FxFlightMedals(object pTarget, int iIndex)
{
  //Zum einen gibts Let's Rock
  if(EffectVar(0,pTarget,iIndex)[0] >= 3)
  {
    var pMedal = FindObject(LR_M);
    if(pMedal)
      Reward(pMedal,GetController(pTarget));
  }

  //Und zum anderen Uhm... Reflection?
  if(EffectVar(0,pTarget,iIndex) && EffectVar(2,pTarget,iIndex))
    if(EffectVar(0,pTarget,iIndex)[2])
      if(!(EffectVar(3,pTarget,iIndex) ->~ IsClonk()))
      {
        var pMedal = FindObject(UR_M);
        if(pMedal)
          Reward(pMedal,GetController(pTarget));
      }
  return true;
}
