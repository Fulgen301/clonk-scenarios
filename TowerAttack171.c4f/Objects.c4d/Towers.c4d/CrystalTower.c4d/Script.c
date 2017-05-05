/* Kristallturm */

#strict
//#include BSC1

func Initialize()
{
  CreateLight(40, LightClr(), this);
  SetGraphics("");
}

func Attack()
{
  if(GetCon()<100)
    return 0;
  var pTarget;
  if(pTarget=FindObject2(Find_NotHidden(),Find_OCF(OCF_CrewMember()),Find_Hostile(GetOwner()),Find_Distance(Range()),Sort_Distance()))
  {
    for(var cnt=1+Random(3);cnt;cnt--)
      DrawLightning(GetX(),GetY()+LightningOffset(),GetX(pTarget)+RandomX(-4,4),GetY(pTarget)-4+RandomX(-4,4));
    DoEnergy(-StrikeDamage(),pTarget);
  }
}

func StrikeDamage(){ return RandomX(3,5);}
func Range(){ return 130;}
func LightningOffset(){ return -35;}

func LightClr(){ return RGB(0,0,255);}

func CanBeBuild(pClonk)
{
  //if(GetID(pClonk)==MAGE)
    return true;
}

func IsLevel1(){return 1;}

func UpgradeTo()
{
  return TWM2;
}

func UpgradeCost()
{
  return 55;
}

protected func Incineration()
{
  var pLight;
  if(pLight=FindObject2(Find_Func("IsLight"),Find_ActionTarget(this)))
    RemoveObject(pLight);
  SetGraphics("Dmg");
}
