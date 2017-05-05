/* TowerAttack */

#strict

static g_pConsoleBlood,g_pConsoleBone;

protected func Initialize()
{
  var cons=CreateObject(COBS,10*GetScenMapZoom(),37*GetScenMapZoom(),-1 );
  AddEffect("NoBurning", cons, 200, 0,cons);
  SetName("{{IBLO}}MainBase",cons);
  g_pConsoleBlood=cons;

  SetGraphics("2",cons=CreateObject(COBS,214*GetScenMapZoom(),37*GetScenMapZoom(),-1 ));
  AddEffect("NoBurning", cons, 200, 0,cons);
  SetName("{{BONE}}MainBase",cons);
  g_pConsoleBone=cons;
}

public func Script20()
{
  CheckAIJoin();
}

protected func InitializePlayer(int iPlr, int iX, int iY, object pBase, int iTeam)
{
  if(iTeam==1)
    SetOwner(iPlr,g_pConsoleBlood);
  if(iTeam==2)
    SetOwner(iPlr,g_pConsoleBone);
}

// Effekt: NoBurning

global func FxNoBurningEffect(szNewEffect, iEffectTarget, iEffectNumber, iNewEffectNumber, var1, var2, var3)
{
  // Feuer abblocken
  if (WildcardMatch(szNewEffect, "*Fire*")) return(-1);
  // Alles andere ist OK
  return();
}

/*---TowerAttack Callbacks---*/

/*
  SetRelaunchPos wird aufgerufen wenn ein Clonk wiederbelebt wird
  Hier sollte der entsperechende Clonk an die Startposition zur�ckgesetzt werden
*/
public func SetRelaunchPos(Target)
{
  SetPosition(200,300,Target);
  if(GetPlayerTeam(GetOwner(Target))==2)
    SetPosition(LandscapeWidth()-200,300,Target);
}

/*
  Szenariospezifische Einheiten-KI-Bewegung
  Sollte bei mehreren Wegen daf�r sorgen das sie den entsprechenden Weg gehen
*/
public func HardcodetBulkAIMovement(pBulkPart,&Param,iMode,&iWay,pTarget)
{
}

/*
  Szenariospezifische SpielerHelden-KI-Bewegung
  Sollte die Helden an die richtigen Positionen f�hren
*/
public func HardcodetAIMovement(pClonk)
{
}

/*
  Baupl�tze f�r die KI (X-Position)
  Sollte ein Array zur�ckgeben
*/
public func TA_AIBuildplacesX(iPlr,iMode)
{
  var aPosX=[
              LandscapeWidth()/6,
              LandscapeWidth()/5,
              LandscapeWidth()/4,
              LandscapeWidth()/3
            ];
  // Zus�tzlicher Punkt f�r Angreifer
  if(iMode==TWRATCK_AIMode_Attack||iMode==TWRATCK_AIMode_Expand)
  {
    aPosX[GetLength(aPosX)]=LandscapeWidth()/2;
  }
  // Wenn anderes Team unmdrehen
  if(GetPlayerTeam(iPlr)==2)
    for(var i = 0; i < GetLength(aPosX); i++)
      aPosX[i]=LandscapeWidth()-aPosX[i];
  return aPosX;
}

/*
  Baupl�tze f�r die KI (Y-Position)
  Sollte ein Array zur�ckgeben
*/
public func TA_AIBuildplacesY(iPlr,iMode)
{
  var lh=LandscapeHeight()/2;
  var aPosY=[
            lh,lh,lh,lh
            ];
  // Zus�tzlicher Punkt f�r Angreifer
  if(iMode==TWRATCK_AIMode_Attack||iMode==TWRATCK_AIMode_Expand)
  {
    aPosY[GetLength(aPosY)]=lh;
  }
  return aPosY;
}

/*
  Spawnposition f�r die Truppen
*/
public func GetCrapStartPosition(iTeam,fY)
{
  if(fY)
    return 300;
  if(iTeam==1)
    return RandomX(70,130);
  if(iTeam==2)
    return LandscapeWidth()-RandomX(70,130);
}

global func CopyRight()
{
  var obj2,i,i2;
  for(var obj in FindObjects(Find_Not(Find_Func("RejectCopy"))))
  {
    obj2=CreateObject(GetID(obj),0,0,GetOwner(obj));
    SetPosition(LandscapeWidth()-GetX(obj),GetY(obj),obj2);
    if(GetEffect("NoBurning",obj))
      AddEffect("NoBurning", obj2, 200, 0,obj2);
    if(GetR(obj))
      SetR(-GetR(obj),obj2);
    if(GetObjectBlitMode(obj))
      SetObjectBlitMode(GetObjectBlitMode(obj),obj2);
    if(GetDir(obj))
      SetDir(1,obj2);
    if(GetID(obj)==_EDG)
    {
      i=GetPhase(obj);
      i2=0;
      while(i>2)
      {
        i2+=2;
        i-=2;
      }
      i=!i;
      i+=i2;
      obj2->SetP(i);
    }
  }
}
