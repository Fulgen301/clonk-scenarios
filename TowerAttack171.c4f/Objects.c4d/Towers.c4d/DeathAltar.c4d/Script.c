/* Seuchenaltar */

#strict

local iEffect;

func Initialize()
{
  SetGraphics("");
}

protected func Incineration()
{
  SetGraphics("Dmg");
}


func Range(){ return 100;}

func Kill()
{
  if(GetCon()<100)
    return 0;
  var Damaged;
  for(var obj in FindObjects(Find_Hostile(GetOwner()),Find_OCF(OCF_Alive),Find_Distance(Range())))
  {
    // Schaden machen
    if(!Random(6))
    {
      DoEnergy(-1,obj);
      obj->CreateParticle("Blast",RandomX(-8,8),RandomX(-12,8),0,0,RandomX(48,68),RGB(0,255,0),obj);
    }
    Damaged=true;
  }
  if(Damaged)
    if(Random(2))
      CreateParticle("ShortFog",RandomX(-Range(),Range()),RandomX(-Range(),Range()),0,0,RandomX(168,508),RGB(0,255,0));
  if(iEffect++==4)
  {
    CreateParticle("PSpark",+7,-13,0,-3,RandomX(50,60),RGB(0,255,0));
    CreateParticle("PSpark",-3,-13,0,-3,RandomX(50,60),RGB(0,255,0));
    iEffect=0;
  }
}

func UpgradeTo()
{
  return false;
}

func UpgradeCost()
{
  return 0;
}

func CanBeBuild(pClonk)
{
  //if(GetID(pClonk)==LICH)
    return true;
}

func NoAIBuild()
{
  return Random(2);
}

func IsLevel1(){return 0;}
