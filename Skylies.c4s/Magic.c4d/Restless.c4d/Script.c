/*-- Restless! --*/

#strict 2

static const RL0D_MAXTIME = 500;

func Activate(object pClonk)
{
  //Vorgefertigte Suchabfrage
  var aCrit = [C4FO_And,Find_Distance(100),Find_Not(Find_Func("IsTree")),Find_Not(Find_Category(C4D_Structure)),Find_NoContainer()];

  //Mit Kombo! omgomg!
  var pCombo = FindContents(HTBM,pClonk);
  if(pCombo)
  {
    aCrit[GetLength(aCrit)] = Find_Exclude(pClonk);
    RemoveObject(pCombo);
  }

  else aCrit[GetLength(aCrit)] = Find_Not(Find_OCF(OCF_Living));

  for(var obj in FindObjects(aCrit))
  {
    AddEffect("Restless",obj,100,Random(20)+30,0,GetID());
    if(GetID(obj) == HTBM)
      AddEffect("MedalShake",obj,100,0,this,0,this);
  }
  
  AddEffect("Remove",this,100,RL0D_MAXTIME,this);
  return true;
}

func FxRemoveStop(object pTarget, int iIndex, int iReason)
{
  if(GetEffectCount("MedalCount",pTarget) >= 3)
  var pMedal = FindObject(SI_M);
  if(pMedal)
    Reward(pMedal,GetController(pTarget));
  RemoveObject(pTarget);
  return true;
}

func FxRestlessTimer(object pTarget, int iIndex, int iTime)
{
  var iMax = RL0D_MAXTIME;
  if(iTime > iMax) return -1;
  if(GetAlive(pTarget)) ObjectSetAction(pTarget,"Tumble");
  SetAngleDir(Random(360),iMax/10-Abs(iMax/2-iTime)/5,pTarget);
  return true;
}

func SetAngleDir(int iAngle, int iSpeed, object pObject, int iPrecision)
{
  SetXDir(Cos(iAngle+90,iSpeed,iPrecision),pObject,iPrecision);
  SetYDir(Sin(iAngle+90,iSpeed,iPrecision),pObject,iPrecision);
  return true;
}

//Für die Medaille
func FxMedalShakeStart(object pTarget, int iIndex, int iTemp, object pMagic)
{
  EffectVar(0,pTarget,iIndex) = pMagic;
  return true;
}

//Inklusive Callback
func AddStrike() {return AddEffect("MedalCount",this,100,0);}

public func GetSpellClass(object pMage) { return(AIR1); }
public func GetSpellCombo(pMage) { return ("252"); } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
