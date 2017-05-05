/*-- Pfeil --*/

#strict

local lastX,lastY,estX,estY;

/* Pfeileigenschaften */
public func PackTo() { return(ARWP); }
public func IsArrow() { return(1); }
public func ArrowStrength() { return(5); }
public func ArrowTumbleRandom() {return(2);}
public func ArrowStopsOnHit() { return(1); }

/* Produkteigenschaften */

// Abwärtskompatibilität. Neuerdings ist der Pfeil eh kein Bauplan mehr
// und kann daher so oder so nicht mehr hergestellt werden.
public func IsAnvilProduct() { return(1); }

/* Wird abgefeuert */
public func Initialize()
{
  SetAction("Shot");
  
  // Es gibt jetzt eine extra Trefferpruefung
  SetCategory(C4D_Vehicle(),this());
}

/* Aufschlag */
protected func Hit(int oldX, int oldY)
{
  if(GetAction() eq "Shot")
  {
   // Damit es zu keiner Endlosrekursion kommt wenn InFlight nochmal Hit()
   // aufruft (z.B. Golem, siehe auch #2104) wird die Action hier zurückgesetzt
   // bevor InFlight() aufgerufen wird.
   SetAction("Idle");
   
   // Wenn geschossen noch einmal die Ueberpruefung durchfuehren
   InFlight();
   
   // Kurzzeitiges Stecken in festen Dingen
   var angle=Angle(GetX(),GetY(),GetX()+oldX,GetY()+oldY)-90;
   var iX=Cos(angle,5);
   var iY=Sin(angle,5);
   if(GBackSolid(iX,iY))
   {    
    SetVertex(2,0,Cos(angle-GetR(),7),this(),1);
    SetVertex(2,1,Sin(angle-GetR(),7),this(),1);
   
    SetSpeed();
    SetRDir();
    AddEffect("IntStickInMaterial",this(),1,10,0,GetID());
   }
  }
  
  // Wieder zu einem Objekt machen
  if(!(GetCategory() & C4D_Object()))
   SetCategory(C4D_Object(),this());
}

/* Effekt fuers Stecken in Material */

public func FxIntStickInMaterialStart()
{
 return(1);
}

public func FxIntStickInMaterialTimer(pTarget,iEffectNumber,iEffectTime)
{
 if(iEffectTime > 36*5 || Contained(pTarget))
 {
  SetVertex(2,0,GetDefCoreVal("VertexX","DefCore",GetID(pTarget),2),pTarget,1);
  SetVertex(2,1,GetDefCoreVal("VertexY","DefCore",GetID(pTarget),2),pTarget,1);
  return(-1);
 }
 
 return(1);
}

/* Effekt fuer Stillstand */

func FxPendingToRemoveTimer(pTarget,iEffectNumber,iEffectTime)
{
 // Pfeil bewegt sich wieder?
 if(GetXDir(pTarget) || GetYDir(pTarget))return -1;
 
 // Pfeiltrefferueberpruefung entfernen (nach knapp einer Sekunde)?
 if(iEffectTime > 36*1)
 {
  pTarget->SetSpeed(0,0);
  if(GetAction(pTarget) eq "Shot")
   pTarget->SetAction("Idle");
  return -1;
 }
}

/* Treffer */
public func HitTarget(pObject)
{
  Sound("ArrowHit");
  
  // Ruestungsritter zB wollen nicht immer getroffen werden
  if(pObject->~QueryCatchBlow(this()))return(0);
  
  // Ziel wird getroffen
  pObject->~OnArrowHit(this());
  
  if(GetAlive(pObject))
  {
   var iDmg=(ArrowStrength()*(Max(Abs(GetXDir()),Abs(GetYDir()))+1))/50;
   DoEnergy(-iDmg,pObject);

   // Objekt wurde getroffen. Damit Schild des Ritters noch vor Pfeilen schuetzt
   if(pObject && GetAlive(pObject))
    pObject->~CatchBlow(-iDmg,this());

   // Ziel koennte irgendwas mit dem Pfeil gemacht haben
   if(!this())
    return();

   // Schleudern nur einmal / Sekunde erlaubt
   var bTumble=true;
   var iEffect;
   if(pObject)
   for(var i=0;iEffect=GetEffect("IntNoArrowTumble",pObject,i);i++)
   {
    if(EffectVar(0,pObject,GetEffect("IntNoArrowTumble",pObject,i)) != this())continue;
    bTumble=false;
    break;
   }

   // Zielobjekt auch sichtbar treffen
   if(pObject)
   if(bTumble)
   if(!Random(ArrowTumbleRandom()))
   {
    var xDir=(GetXDir(this())/3);
    var yDir=(GetYDir(this())/3);
    
    if(GetAlive(pObject))
    {
     pObject->SetAction("Tumble");
     AddEffect("IntNoArrowTumble",pObject,1,30,0,ARRW,this());
    } 
    pObject->SetSpeed(GetXDir(pObject)+xDir,GetYDir(pObject)+yDir-1);    
   }
  }

  // Wenn sich das Objekt nicht entfernt hat noch festhaengen (Zielscheibe zB)
  if(pObject)
  if(pObject->~IsArrowTarget(this()))
  {
   SetXDir(0); SetYDir(0); SetRDir(0);
   Local(2) = pObject;
   Local(3) = GetX() - GetX(pObject);
   Local(4) = GetY() - GetY(pObject);
   SetAction("Stick");
  }

  // Pfeil stoppen?
  if(ArrowStopsOnHit())
  {
   SetSpeed(GetXDir(pObject),GetYDir(pObject));
   if(GetAction() eq "Shot")
    SetAction("Idle");
   // Nicht sofort einsammeln
   AddEffect("CannotBeCollected",this(),1,36*2,0,ARRW);
  }

 
 return(1);
}
local iA;

public func FadeOut(){
SetR(Angle(GetX(),GetY(),GetX()+GetXDir(),GetY()+GetYDir()),this());

iA++;
if(iA > 253){ RemoveObject(); }
SetClrModulation(RGBa(255,255,255,iA));
 return(1);
}
/* Direkt nach dem Treffer nicht einsammelbar */

public func FxCannotBeCollectedStart()
{
 return(1);
}

public func FxCannotBeCollectedTimer()
{
 return(-1);
}

/* Effekt gegen mehrfach wegschleudern */

public func FxIntNoArrowTumbleStart(pTarget,iEffectNumber,temp,par1)
{
 if(temp)return();
 EffectVar(0,pTarget,iEffectNumber)=par1;
 return(1);
}

public func FxIntNoArrowTumbleTimer(pTarget)
{
 // Effekt loescht sich sofort
 return(-1);
}

public func NoArrowHit(pObject,iFrames)
{
 AddEffect("IntNoArrowHit",this(),1,iFrames,0,ARRW,pObject);
}

/* Effekt gegen Treffen (Armbrustschuetze) */

public func FxIntNoArrowHitStart(pTarget,iEffectNumber,temp,par1)
{
 if(temp)return();
 EffectVar(0,pTarget,iEffectNumber)=par1;
 return(1);
}

public func FxIntNoArrowHitTimer(pTarget)
{
 // Effekt loescht sich sofort
 return(-1);
}

/* Ziel pruefen */
private func InFlight()
{
 
 // Wenn der Pfeil keine Geschwindigkeit mehr hat (schwimmt oder so?) dann nicht mehr ueberpruefen
 if(!GetXDir() && !GetYDir())
 if(!GetEffect("PendingToRemove",this))
  AddEffect("PendingToRemove",this,1,10,this);
 
 if(lastX || lastY)
 {
   // Wenn der Pfeil durch irgendwas gebeamt wurde oder Aehnliches muss eine Sicherheit her
   var bSkip=false;
   if(estX || estY)
   if(Distance(GetX(),GetY(),estX,estY) > Max(1,Max(Abs(GetXDir()),Abs(GetYDir())))*2){bSkip=true;}
   
   if(!bSkip)
   for(var obj in FindObjects(Find_OnLine(lastX-GetX(),lastY-GetY(),0,0),
                     Find_Exclude(this()),
                     Find_NoContainer(),
                                         Find_Layer(GetObjectLayer()),
                     Find_Or(Find_OCF(OCF_Alive()),Find_Func("IsArrowTarget",this())))){   
      // In der Trefferzone?
      if (obj->~IsOutsideArrowHitZone(this)) continue;
      
      // Darf das Objekt getroffen werden?     
      var iSkip=false;
      var iEffect;
      for(var i=0;iEffect=GetEffect("IntNoArrowHit",this(),i);i++)
      {
       if(EffectVar(0,this(),GetEffect("IntNoArrowHit",this(),i)) != obj)continue;
       iSkip=true;
       break;
      }
      
      if(iSkip)continue;
      
      HitTarget(obj);
      break;
    }
 }
 lastX=GetX();
 lastY=GetY();
 estX=GetX()+GetXDir();
 estY=GetY()+GetYDir();
 return(1);
}

/* Steckt in Zielobjekt */

private func Sticking()
{
  // Ziel verloren?
  if (Contained() || !Local(2)) 
    return SetAction("Idle");
  // Lange genug gesteckt?
  var iMaxStickTime = Local(2)->~GetArrowStickTime();
  if (iMaxStickTime && GetActTime() > iMaxStickTime)
    return SetAction("Idle");
  // Weiter stecken
  SetPosition(GetX(Local(2)) + Local(3), GetY(Local(2)) + Local(4));
  
}

/* Einsammeln */



