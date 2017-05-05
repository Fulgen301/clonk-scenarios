#strict 2
#appendto MGLD

//Killverfolgung, Anti-Contained-Hack

func FxMagicLifeDepletionFlightTimer(pTarget, iEffectNumber, iEffectTime)
  {
  if(iEffectTime > 35*30*1)return -1;
  

  
  //Effekte
  //if(iEffectTime % 2 == 0)
  {
   var x1=Cos(iAngle,Cos(iEffectTime*6,10));
   var y1=Sin(iAngle,Cos(iEffectTime*6,10));
   
   var x2=Cos(iAngle-180,Cos(iEffectTime*6,10));
   var y2=Sin(iAngle-180,Cos(iEffectTime*6,10));
   
   CreateParticle("PSpark",x1,y1,0,0,40,RGB(255,10,10));
   CreateParticle("PSpark",x2,y2,0,0,40,RGB(255,10,10));
  }
  
  if(iEffectTime % 2==0)return 1;
  
  SetXDir(Cos(iAngle-90,MGLD_Speed),this);
  SetYDir(Sin(iAngle-90,MGLD_Speed),this);
  
  if(!pEnemy)
  {
   var enemies=FindObjects(Find_OCF(OCF_CrewMember), Find_Layer(GetObjectLayer()), Find_Hostile(GetOwner(pCaster)), Find_Distance(MGLD_SearchingRange), Find_NoContainer());
   for(var clnk in enemies)
   {
    if(!PathFree(GetX(),GetY(),GetX(clnk),GetY(clnk)))continue;
    
    pEnemy=clnk;
    break;
   }
     //Targetsuche aus
  }
  //Target aussortieren?
  
  var iNeededAngle=Angle(GetX(),GetY(),GetX(pEnemy),GetY(pEnemy));
  if(iNeededAngle > 180) iNeededAngle=iNeededAngle-360;
  if(pEnemy)
  {
    if(!GetAlive(pEnemy))pEnemy=0;
    if(!PathFree(GetX(),GetY(),GetX(pEnemy),GetY(pEnemy)))pEnemy=0;
    if(Contained(pEnemy))pEnemy=0;
  }
  
  //Target verfolgen
  if(pEnemy)
  {
   iAngle=BoundBy(iNeededAngle,iAngle-6,iAngle+6);
  }
  
  //Target hauen!
  if(pEnemy)
   if(ObjectDistance(this,pEnemy) < 10)
   {
   AddEffect("DrainLives",pEnemy,20,2,0,GetID(),pCaster);
   return -1;
      }
  // OK; weiter existieren
  return 1;
  }

//Altaaah... und ich wollte nur einen Parameter ändern >.<
//Notiz: Killverfolgung suckt

protected func FxDrainLivesTimer(pTarget,iEffectNumber,iEffectTime)
{
 var pClonk=EffectVar(0,pTarget,iEffectNumber);
 if(!GetAlive(pClonk))return -1;
 if(!GetAlive(pTarget))return -1;
 
 if(!pClonk || !pTarget)return -1;
 
 
 if(iEffectTime > 40)return -1;
 
 DoEnergy(-1, pTarget, false, 0, GetOwner(pClonk) + 1);
 DoEnergy(1, pClonk);
 
 if(Random(3))return 0;
 
    var lastX,lastY;
    var x1=GetX(pTarget);
    var y1=GetY(pTarget);
    var x2=GetX(pClonk);
    var y2=GetY(pClonk);
    
    lastX=x1;
    lastY=y1;
    
    var i, deltax, deltay, numpixels;
    var d, dinc1, dinc2;
    var x, xinc1, xinc2;
    var y, yinc1, yinc2;

    deltax = Abs(x2 - x1);
    deltay = Abs(y2 - y1);

    if(deltax >= deltay) {
        numpixels = deltax + 1;
        d = (2 * deltay) - deltax;
        dinc1 = deltay << 1;
        dinc2 = (deltay - deltax) << 1;
        xinc1 = 1;
        xinc2 = 1;
        yinc1 = 0;
        yinc2 = 1;
    } else {
        numpixels = deltay + 1;
        d = (2 * deltax) - deltay;
        dinc1 = deltax << 1;
        dinc2 = (deltax - deltay) << 1;
        xinc1 = 0;
        xinc2 = 1;
        yinc1 = 1;
        yinc2 = 1;
    }

    if(x1 > x2) {
        xinc1 = -xinc1;
        xinc2 = -xinc2;
    }
    if(y1 > y2) {
        yinc1 = -yinc1;
        yinc2 = -yinc2;
    }

    x=x1;
    y=y1;

    for(i = 1; i < numpixels; i++) {
        if(!Random(25)){
          
          var aX=x+RandomX(-10,10);
          var aY=y+RandomX(-10,10);
          
          var l=DrawLightning(lastX,lastY,aX,aY);
          SetClrModulation(RGB(255,10,10),l);
          if(l)l->ActivateColor(205+Random(50),Random(50),Random(50));
          
          lastX=aX;
          lastY=aY;
        }

        if(d < 0) {
            d = d + dinc1;
            x = x + xinc1;
            y = y + yinc1;
        } else {
            d = d + dinc2;
            x = x + xinc2;
            y = y + yinc2;
        }
    }
}