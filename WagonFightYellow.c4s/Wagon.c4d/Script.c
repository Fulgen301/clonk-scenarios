/*--- Waggon ---*/

#strict
local mode;

func Initialize()
{
    if(!FindObject(0,-80,-28,160,28,OCF_Alive()))if(FindObject(WAGN,-20,-14,40,28))RemoveObject();
    SetAction("Fly");
   // if(!Random(10))  SetMode(3); 
   var a = Random(16);
   if(a<13) SetMode(3); 
   
   else {if(a==13 || a == 14)  {SetMode(2); } else  {SetMode(1); }}
}


func Fade()
{
    AddEffect("Fade",this(),20,1,this());
    Set(dir);
}

func SetMode(imode)
{
    if(imode==1)
    {
        mode=1; SetClrModulation(RGB(250,0,0));
    }

    if(imode==2)
    {
        mode=2; SetClrModulation(RGB(100,100,250));
    }
    
    if(imode==3)
    {
        mode=3; SetClrModulation(RGB(255,255,60));
    }
}

func FadeIn()
{
    var r = Random(3);
    if(r==0) SetMode(1);
    if(r==1) SetMode(2);
    if(r==2) SetMode(3);

    AddEffect("FadeIn",this(),20,1,this());
    SetSolidMask();
    Set(dir);
}

func FxFadeInTimer(pTarget,iNumber)
{
    EffectVar(1,this(),iNumber)+=23;

    if(mode==3)SetClrModulation(RGBa(250,250,60,253-EffectVar(1,this(),iNumber)),pTarget);
    else if(mode==1)SetClrModulation(RGBa(250,0,0,253-EffectVar(1,this(),iNumber)),pTarget);
    else if(mode==2)SetClrModulation(RGBa(100,100,250,253-EffectVar(1,this(),iNumber)),pTarget);
    else SetClrModulation(RGBa(250,250,250,253-EffectVar(1,this(),iNumber)),pTarget);

    if(253-EffectVar(1,this(),iNumber)==0) { SetSolidMask(0,0,40,28);  return(-1); }
}

func FxFadeTimer(pTarget,iNumber)
{
    EffectVar(1,this(),iNumber)++;
    SetClrModulation(RGBa(250,250,250,EffectVar(1,this(),iNumber)),pTarget);
    if(EffectVar(1,this(),iNumber)==255)RemoveObject(pTarget);
}

func Set(int iDir)
{
    if(iDir==0)SetComDir(COMD_Left());
    if(iDir==1)SetComDir(COMD_Right());
}

func Damage(iDmg, iTyp)
{
    SetController(iTyp);
    if(GetEffect("Fade",this()))return(1);
    if(mode==1)Do();
    if(mode==2)Do2();
    if(mode==3)Do3();
    if(GetDamage() > 29)
    {
        for(var obj in FindObjects(Find_AtRect(-24,-18,48,36)))
        obj->Schedule(Format("SetKiller(%d)",GetController()),2,1);
        //SetController(GetController(),obj);
        Incinerate();
    }
}



func Do()
{

    var pfeilospreng;
    for(var i = 0;i<5+Random(2);++i)
    {
	   pfeilospreng = CastObjects2(XARW,1,90,0,0,GetController());
	   pfeilospreng->Launch();
	  }
	
  //  CastObjects2(FLNT,7,15,0,0,GetController());
    CastParticles("Splinter",3,70,0,0,70,120,RGB(250,250,250),RGB(250,250,250));
    Explode(15);
    for(var obj in FindObjects(Find_AtRect(-24,-18,48,36)))
        obj->Schedule(Format("SetKiller(%d)",GetController()),2,1);
     
    //SetController(GetController(),obj);
}

func Do2()
{
    CastObjects(_SPK,5+Random(2),15);
    CreateObject(COKI,0,0,-1);
    CastParticles("Splinter",3,70,0,0,70,120,RGB(250,250,250),RGB(250,250,250));
    Explode(15);
    for(var obj in FindObjects(Find_AtRect(-24,-18,48,36)))
        obj->Schedule(Format("SetKiller(%d)",GetController()),2,1);
}

func Do3()
{
	//var pfeilospreng;
    CastObjects2(QARW,20+Random(8),120,0,0,GetController());
	//pfeilospreng = CastObjects2(XARW,Random(2),120); pfeilospreng[0]->Launch();
    CastParticles("Splinter",3,70,0,0,70,120,RGB(250,250,250),RGB(250,250,250));
    Explode(15);
    for(var obj in FindObjects(Find_AtRect(-24,-18,48,36)))
        obj->Schedule(Format("SetKiller(%d)",GetController()),2,1);
}



