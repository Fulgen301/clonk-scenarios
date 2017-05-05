#strict 2
#appendto MGPH

//Anti-Contained-Hack, die M&Mler habens wohl nicht so mit Find_NoContainer()...

func FxMagicSphereFlightTimer(pTarget, iEffectNumber, iEffectTime)
{
  // Zu spät...
  if(iEffectTime > 35*60*1)return -1;
  
  // Tolle Partikel
  if(iEffectTime%5==1) 
    CreateParticle("PSpark",0,0,RandomX(-4,4),RandomX(-4,4),100,RGB(10,10,255),this);
  if(iEffectTime%3==1)
    CreateParticle("FSpark",0,0,GetXDir()/2+RandomX(-3,3),GetYDir()/2+RandomX(-3,3),140,RGB(250,250,255),this); 
 
  // Am Anfang erstmal hochfliegen
  if(iEffectTime < MGPH_StartTime-MGPH_StartTime/3 && !bActivated)
  {
   SetXDir(BoundBy(GetXDir()+RandomX(-2,2),-10,10));
   SetYDir(-MGPH_Speed);
   // Alles toll³
   return 1;
  }
  if(iEffectTime < MGPH_StartTime && !bActivated)
  {
    SetXDir(MGPH_Speed/3*iStartingDir);
    SetYDir(0);
    iAngle=Angle(GetX(),GetY(),GetX()+GetXDir(),GetY()+GetYDir()-1);
    // Alles toll²
    return 1;
  }
  
  if(iEffectTime==MGPH_StartTime)
  {
    SetXDir(0);
    SetYDir(0);
  }
  
  if(!Random(10))
  {
    var rand=Random(360);
    var rand2=20+Random(10);
    DrawLightning(GetX(),GetY(),GetX()+Cos(rand,rand2),GetY()+Sin(rand,rand2));
  }
  
  if(EffectVar(0,pTarget,iEffectNumber))
  if(Contained(EffectVar(0, pTarget, iEffectNumber)) || !GetAlive(EffectVar(0,pTarget,iEffectNumber)) || !PathFree(GetX(),GetY(),GetX(EffectVar(0,pTarget,iEffectNumber)),GetY(EffectVar(0,pTarget,iEffectNumber))))
  EffectVar(0,pTarget,iEffectNumber)=0;
  
  // Targetsuchen?
  if(!EffectVar(0,pTarget,iEffectNumber))
  {
    var enemy = FindObject2(Find_Hostile(GetOwner()), Find_Layer(GetObjectLayer()), Find_OCF(OCF_CrewMember), Find_NoContainer(), Sort_Distance());
    if(ObjectCount(NTMG)) enemy = FindObject2(Find_OCF(OCF_CrewMember),Find_Layer(GetObjectLayer()), Find_NoContainer(), Sort_Distance());
    //Anm.: Sort_Distance() kannten sie auch nicht :O
    // Target gefindet!1
    EffectVar(0,pTarget,iEffectNumber) = enemy;
  }
  
  // Kein Target?
  if(!EffectVar(0,pTarget,iEffectNumber))
  {
   if(Random(2))SetXDir(GetXDir()+RandomX(-2,2));
   if(Random(2))SetYDir(GetYDir()+RandomX(-2,2));
   return 0;
  }
  
  //Nun auf Target zielen
  //SetXDir(BoundBy(BoundBy(GetXDir()+GetX(EffectVar(0,pTarget,iEffectNumber))-GetX(),GetXDir()-3,GetXDir()+3),-MGPH_Speed,MGPH_Speed));
  //SetYDir(BoundBy(BoundBy(GetYDir()+GetY(EffectVar(0,pTarget,iEffectNumber))-GetY(),GetYDir()-3,GetYDir()+3),-MGPH_Speed,MGPH_Speed));

 /* var angle=Angle(GetX(),GetY(),GetX(EffectVar(0,pTarget,iEffectNumber)),GetY(EffectVar(0,pTarget,iEffectNumber)))-90;
  var angle2=Angle(GetX(EffectVar(0,pTarget,iEffectNumber)),GetY(EffectVar(0,pTarget,iEffectNumber)),GetX(),GetY())-90;
  var fAngle=angle;//Max(angle,angle2);
  iAngle=BoundBy(fAngle,iAngle-12,iAngle+12);
  SetXDir(Cos(iAngle,MGPH_Speed));
  SetYDir(Sin(iAngle,MGPH_Speed));*/
  
  //SetXDir(BoundBy(GetXDir()+BoundBy(GetX(EffectVar(0,pTarget,iEffectNumber))-GetX(),-1,1),-MGPH_Speed,MGPH_Speed));
  //SetYDir(BoundBy(GetYDir()+BoundBy(GetY(EffectVar(0,pTarget,iEffectNumber))-GetY(),-1,1),-MGPH_Speed,MGPH_Speed));
  var x=2;  if(GetX(EffectVar(0,pTarget,iEffectNumber))-GetX()>0)x=-2;
  var y=2;  if(GetY(EffectVar(0,pTarget,iEffectNumber))-GetY()>0)y=-2;
  
 
  SetXDir(BoundBy(GetXDir()-x,-MGPH_Speed,MGPH_Speed));
  SetYDir(BoundBy(GetYDir()-y,-MGPH_Speed,MGPH_Speed));
  
  if(Inside(GetX(EffectVar(0,pTarget,iEffectNumber))-GetX(),-4,4))SetXDir();
  if(Inside(GetY(EffectVar(0,pTarget,iEffectNumber))-GetY(),-4,4))SetYDir();
  
  // Das war ja einfach, getroffen?
  if(ObjectDistance(this,EffectVar(0,pTarget,iEffectNumber))<Min(GetDefCoreVal("Width","DefCore",GetID(EffectVar(0,pTarget,iEffectNumber)))/2,
                                                                   GetDefCoreVal("Height","DefCore",GetID(EffectVar(0,pTarget,iEffectNumber)))/2))
  {Punch(EffectVar(0,pTarget,iEffectNumber),MGPH_AverageStrength+RandomX(-5,5));RemoveObject(pTarget);}
  // OK; weiter existieren
  return 1;
}