/* Heilungskristall */

#strict

func Range(){ return 100;}

func Initialize()
{
  CreateLight(60, LightClr(), this);
}

func Heal()
{
  if(GetCon()<100)
    return 0;
  var Healed;
  for(var obj in FindObjects(Find_Allied(GetOwner()),Find_OCF(OCF_Alive),Find_Distance(Range())))
  {
    // Volle Energie? überspringen
    if(GetEnergy(obj)>=GetPhysical("Energy", 0, obj)*99/100000) continue;
    // Heilen
    if(!Random(16))
    {
      DoEnergy(1,obj);
      obj->CreateParticle("NoGravSpark",RandomX(-8,8),RandomX(-12,8),0,-5,RandomX(18,28),RGB(255),obj);
    }
    if(!Random(14))
      obj->CreateParticle("NoGravSpark",RandomX(-8,8),RandomX(-12,8),0,-5,RandomX(18,28),RGB(255),obj);
    Healed=true;
  }
  if(Healed)
    CreateParticle("Aura",0,0,RandomX(-1,1),RandomX(-1,1),Range()*11+Sin(FrameCounter()*2,Range()*2),RGB(200,255,0));
}

func LightClr(){ return RGB(255,0,0);}

func UpgradeTo()
{
  return PGAT;
}

func UpgradeCost()
{
  return 25;
}

func CanBeBuild(pClonk)
{
  //if(GetID(pClonk)==MAGE)
    return true;
}

protected func Incineration()
{
  var pLight;
  if(pLight=FindObject2(Find_Func("IsLight"),Find_ActionTarget(this)))
    RemoveObject(pLight);
}

func NoAIBuild()
{
  return Random(3);
}

func IsLevel1(){return 1;}
