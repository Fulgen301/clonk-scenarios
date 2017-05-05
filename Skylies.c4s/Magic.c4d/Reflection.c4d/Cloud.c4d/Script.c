/* Rückschlagswolke */

#strict 2

local iXDir, iYDir, iXDir2, iYDir2;

func Start(int iXDir, int iYDir)
{
  AddEffect("StrikeBack",this,100,1,this,0,iXDir,iYDir);
  return true;
}

func FxStrikeBackStart(object pTarget, int iIndex, int iTemp, int iXDir, int iYDir)
{
  EffectVar(0,pTarget,iIndex) = iXDir;
  EffectVar(1,pTarget,iIndex) = iYDir;
  return true;
}

func FxStrikeBackTimer(object pTarget, int iIndex, int iTime)
{
  if(iTime >= 500)
  {
    RemoveObject(pTarget);
    return -1;
  }

  var iXDir  = EffectVar(0,pTarget,iIndex);
  var iYDir  = EffectVar(1,pTarget,iIndex);

  //CreateParticle("PSpark",Random(16)-8,Random(16)-8,0,0,Random(100)+40,RGB(25,25,255));
  CreateParticle("SSpark",Random(16)-8,Random(16)-8,0,0,Random(100)+40,RGB(25,25,255));
  for(var obj in FindObjects(Find_Distance(23),Find_OCF(OCF_HitSpeed2),Find_Not(Find_OCF(OCF_Alive)),Find_NoContainer()))
  {
    if(iXDir) SetXDir(iXDir,obj);
    if(iYDir) SetYDir(iYDir,obj);
    
    if(iXDir || iYDir)
    {
      var iEffect = GetEffect("Flight",obj);
      EffectCall(obj,iEffect,"Reflection",this,true);
    }
  }
  return true;
}
