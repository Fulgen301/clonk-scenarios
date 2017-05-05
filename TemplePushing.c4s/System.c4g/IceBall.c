/*-- Make Ice Ball compatible with scrolls and aimer --*/
/*-- Prevent Ice Ball from being held indefinitely --*/

#strict 2

#appendto ICEB

public func ControlLeft() {}

public func ControlRight() {}

// Die restlichen Tasten mit Stop belegen, damit Klassisch auch gerade fliegen kann
public func ControlDig() {}

public func ControlUp() {}

public func ControlDown() {}

// Bei JnR wenn die Taste losgelassen wird auch keine Drehung mehr
public func ControlLeftReleased() {}

public func ControlRightReleased() {}

// Werfen löst den Eisschlag aus
public func ControlThrow() {}

func FxIceStrikeFlightTimer(pTarget, iEffectNumber, iEffectTime)
  {
  var iSize=EffectVar(0, pTarget, iEffectNumber);
  var iMaxSize=EffectVar(1, pTarget, iEffectNumber);
  var iAngle=EffectVar(2, pTarget, iEffectNumber)+=EffectVar(5, pTarget, iEffectNumber);
  var iLaunchFree=EffectVar(3, pTarget, iEffectNumber);
  var pCaster = EffectVar(4, pTarget, iEffectNumber);
  if(iSize<=0) return(RemoveObject());
  
  // Effekt
  for( var i=1; i>0; --i)
    {
    CreateParticle("NoGravSpark",RandomX(-iSize/50,iSize/50), RandomX(-iSize/50,iSize/50), +RandomX(-2,2), +RandomX(-2,2), iSize*60/100+Random(15), RGB(10,RandomX(40,140),RandomX(250, 100)));  
    CreateParticle("Freeze",RandomX(-iSize/50,iSize/50), RandomX(-iSize/50,iSize/50), +RandomX(-2,2), +RandomX(-2,2), iSize*60/100+Random(15), RGB(10,RandomX(250,100),RandomX(40,140)));  
    }
	
  // Ausrichtung nach Caster
  if (!iLaunchFree && pCaster)
    {
      if(iEffectTime > 180)
      {
        var aimer = LocalN("pAimer", pCaster) || LocalN("pAimer", LocalN("pAimingClonk", pCaster));
        if(aimer)
        {
          aimer->ControlThrow();
        }
        return Hit();
      }
      else
      {
        var x=GetX(pCaster)+Sin(iAngle, 25), y=GetY(pCaster)-Cos(iAngle, 25);
        if (GetX()!=x || GetY()!=y)
          {
          DrawParticleLine("Snow", x-GetX(), y-GetY(), 0, 0, 5, 40, 16777215, 16777215, 0);
          SetPosition(x, y);
        }
      }
    }
	
  // Noch nicht voll aufgeladen?
  if (iSize < iMaxSize)
    {
    for( var i=5; i>0; --i)
      {
      var iR, iD;
      var iX=Sin(iR=Random(360), iD=RandomX(iSize/10,iSize/5));
      var iY=Cos(iR, iD);
      CreateParticle("Snow", iX, iY, -iX/3, -iY/3, Random(25), RGBa(Random(255),0,0,90));
      CreateParticle("Snow", iX, iY, -iX/3, -iY/3, Random(35));
      }
	  
    // Vergrößern
    EffectVar(0, pTarget, iEffectNumber) = iSize+=10;
	
    // Nichts weiter während des Wachsens
    return(1);
    }
	
  // Abschuss noch nicht freigegeben?
  if (!iLaunchFree) return(1);
  
  // Maximale Laufzeit
  if(iEffectTime-iLaunchFree>550) return(RemoveObject());
  
  // Geschwindigkeit anpassen
  SetXDir(Sin(iAngle, ICEB_Speed));
  SetYDir(-Cos(iAngle, ICEB_Speed));
  
  // Suche nach Zielen
  var pObj;
  for(pObj in FindObjects(Find_AtPoint(0,1),Find_OCF(OCF_CrewMember),Find_NoContainer(),Find_Layer(GetObjectLayer())))
    {
    if(GetOCF(pObj) & OCF_CrewMember) if (GetAlive(pObj)) return(Hit());
    }
	
  // OK; weiter existieren
  return(1);
  }
 
func FxIceStrikeFlightStop(object pTarget, int iEffectNumber, int iReason, bool fTemp)
  {
  if (!fTemp) RemoveObject(pTarget);
  return(1);
  }
