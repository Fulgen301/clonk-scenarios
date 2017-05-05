/*-- Licht --*/

#strict

local iColor,iCon;

// Licht initialisieren, Parameter setzen, etc.
protected func Init(int iSize, int dwColor, object pTarget, bool fPulse, int iYOff)
{
  // Werte
  if(!iSize)
    iSize = GetCon();  
  if(!pTarget)
    pTarget = GetActionTarget();

  SetOwner(GetController(pTarget));

  // Setzen und so
  SetAction("Attach",pTarget);
  SetPosition(GetX(pTarget),GetY(pTarget));
  iColor=dwColor;
  SetClrModulation(iColor);
  SetCon(iSize);
  iCon=iSize;
  // Pulsieren?
  if(fPulse)
  {
    if(!GetEffect("Pulse",this))
      AddEffect("Pulse",this,10,2+IsNetwork()*2,this);
  }
  else
  {
    var iEffect;
    if(iEffect = GetEffect("Pulse", this))
      RemoveEffect(0, this, iEffect);
  }
  SetObjDrawTransform(1000,0,0,0,1000,iYOff*1000);
}

public func FxPulseTimer()
{
  var Con=GetCon();
  SetCon(BoundBy(Con+RandomX(-20,+20),iCon/2,iCon+iCon/2));
}

// Wenn das Licht kein Ziel mehr hat -> weg damit.
protected func AttachTargetLost()
{
  RemoveObject();
}

global func CreateLight(int iSize, int iColor, object pTarget, bool fPulse, int iYOff)
{
  if(!pTarget)
    if(!(pTarget=this))
      return 0;
  var light = CreateObject(LIGH, 0, 0, GetController(pTarget));
  light->Init(iSize, iColor, pTarget, fPulse,iYOff);
  return(light);
}

func IsLight(){ return true;}
