/*--- Waggon ---*/

#strict
local mode;
local train;

func Initialize()
{
    if(!FindObject(0,-80,-28,160,28,OCF_Alive()))if(FindObject(WAGN,-20,-14,40,28))RemoveObject();
    SetAction("Fly");
    if(!Random(28)) { SetMode(); }
}

public func NewSpeed(int iWagonSpeed) {
 train = 1;
 SetPhysical("Float", iWagonSpeed, PHYS_Temporary, this);
  }

public func IsNotTrainpart(){ if(!train){ return(1); } }

func Fade()
{
    AddEffect("Fade",this(),20,1,this());
    Set(dir);
}

func SetMode(imode)
{
if(!imode){
  mode = RandomX(1,4);
  SetGraphics(Format("%d",mode+1));
 }
}

func FadeIn()
{
    SetMode(2);
    if(!Random(2))SetMode(1);

    AddEffect("FadeIn",this(),20,1,this());
    SetSolidMask();
    Set(dir);
}

func FxFadeInTimer(pTarget,iNumber)
{
    EffectVar(1,this(),iNumber)+=23;

    if(mode==2)SetClrModulation(RGBa(100,100,250,253-EffectVar(1,this(),iNumber)),pTarget);
    else if(mode==1)SetClrModulation(RGBa(250,0,0,253-EffectVar(1,this(),iNumber)),pTarget);
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
    if(mode==1)Do3();
    if(mode==2)Do4();
    if(mode==3)Do();
    if(mode==4)Do2();
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
    CastObjects2(FLNT,7,15,0,0,GetController());
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
func Do4()
{
    CastObjects(COKI,5+Random(2),15);
    CastParticles("Splinter",3,70,0,0,70,120,RGB(250,250,250),RGB(250,250,250));
    Explode(15);
    for(var obj in FindObjects(Find_AtRect(-24,-18,48,36)))
        obj->Schedule(Format("SetKiller(%d)",GetController()),2,1);
}
func Do3()
{
    CastObjects2(QARW,7+Random(4),35);
    CastParticles("Splinter",3,70,0,0,70,120,RGB(250,250,250),RGB(250,250,250));
    Explode(15);
    for(var obj in FindObjects(Find_AtRect(-24,-18,48,36)))
        obj->Schedule(Format("SetKiller(%d)",GetController()),2,1);
}

func Crush()
{
    if(!Random(3)){
    if(mode==1)Do3();
    if(mode==2)Do4();
    if(mode==3)Do();
    if(mode==4)Do2();
    }
    if(!Random(8)){ CastObjects(_SPK,1+Random(2),15); }
    if(!Random(30)){ CastObjects(WIPF,1+Random(2),15); }
    if(!imod){
    Sound("CrateCrack.wav");
    CastParticles("Splinter",6,70,0,0,70,120,RGB(250,250,250),RGB(250,250,250));
    }
   if(imod){ if(!Random(4)){
    Sound("CrateCrack.wav");
    CastParticles("Splinter",6,70,0,0,70,120,RGB(250,250,250),RGB(250,250,250));
    }  } 
    RemoveObject();
    for(var obj in FindObjects(Find_AtRect(-24,-18,48,36)))
        obj->Schedule(Format("SetKiller(%d)",GetController()),2,1);
}

