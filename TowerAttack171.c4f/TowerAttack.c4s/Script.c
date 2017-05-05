/* TowerAttack */

#strict

static g_pConsoleBlood,g_pConsoleBone;

protected func Initialize()
{
  SetGamma(RGB(0,0,0),RGB(110,110,110),RGB(255,253,255));
  SetSkyParallax(1,50,50,0,0,SkyPar_Keep);
  
  var cons=CreateObject(COBS,10*GetScenMapZoom(),112*GetScenMapZoom(),-1 );
  AddEffect("NoBurning", cons, 200, 0, cons);
  SetName("{{IBLO}}MainBase",cons);
  g_pConsoleBlood=cons;
  
  SetGraphics("2",cons=CreateObject(COBS,266*GetScenMapZoom(),112*GetScenMapZoom(),-1 ));
  AddEffect("NoBurning", cons, 200, 0, cons);
  SetName("{{BONE}}MainBase",cons);
  g_pConsoleBone=cons;
}

protected func InitializePlayer(int iPlr, int iX, int iY, object pBase, int iTeam)
{
  if(iTeam==1)
    SetOwner(iPlr,g_pConsoleBlood);
  if(iTeam==2)
    SetOwner(iPlr,g_pConsoleBone);
}

public func OnClonkRecruitment(pCrew)
{
  // Licht verpassen wenn noch nicht da...
  if(!FindObject2(Find_Func("IsLight"),Find_ActionTarget(pCrew)))
    CreateLight(200, RGB(90,90,90), pCrew)->SetVisibility(VIS_Owner);
}

global func Eastern(iX,iY,iX2,iY2,&iXD,&iYD)
{
  //CastParticles("GSpark",5,80,iX,iY,50,100,RGB(255),RGB(0,0,255));
  CreateParticle("GSpark",iX,iY,RandomX(-25,25),RandomX(-25,25),RandomX(50,100),RGB(Random(255),Random(255),Random(255)));
  if(!Random(2))
    return 1;
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
  SetPosition(130,1130,Target);
  if(GetPlayerTeam(GetOwner(Target))==2)
    SetPosition(2700,1130,Target);
}

/*
  Szenariospezifische Einheiten-KI-Bewegung
  Sollte bei mehreren Wegen daf�r sorgen das sie den entsprechenden Weg gehen
*/
public func HardcodetBulkAIMovement(pBulkPart,&Param,iMode,&iWay,pTarget)
{
  if(Inside(GetX(pBulkPart),760,790))
    if(GetPlayerTeam(GetOwner(pBulkPart))==1)
      if(iWay)
        AddCommand(pBulkPart,"Jump");
  if(Inside(GetX(pBulkPart),2110,2140))
    if(GetPlayerTeam(GetOwner(pBulkPart))==2)
      if(iWay)
        AddCommand(pBulkPart,"Jump");
}

/*
  Szenariospezifische SpielerHelden-KI-Bewegung
  Sollte die Helden an die richtigen Positionen f�hren
*/
public func HardcodetAIMovement(pClonk)
{
  if(GetCommand(pClonk)S="MoveTo")
  {
    if(GetCommand(pClonk,3)<570)
    {
      if(GetY(pClonk)>570)
      {
        if(GetX(pClonk)<LandscapeWidth()/2)
          AddCommand(pClonk,"MoveTo",0,1470,630);
        else
          AddCommand(pClonk,"MoveTo",0,1420,630);
      }
    }
    else
      if(GetY(pClonk)<570)
      {
        if(GetX(pClonk)<LandscapeWidth()/2)
          AddCommand(pClonk,"MoveTo",,1205,543);
        else
          AddCommand(pClonk,"MoveTo",,1685,543);
      }
  }
}

/*
  Baupl�tze f�r die KI (X-Position)
  Sollte ein Array zur�ckgeben
*/
public func TA_AIBuildplacesX(iPlr,iMode)
{
  var aPosX=[
              /*Startposition*/0210,0700,
              /*Weg nach Oben*/940,1080,
              /*Vorraum oben*/1300,
              /*Oben*/1310,1440,
              /*Unten*/1100
            ];
  // Zus�tzlicher Punkt f�r Angreifer
  if(iMode==TWRATCK_AIMode_Attack||iMode==TWRATCK_AIMode_Expand)
  {
    aPosX[GetLength(aPosX)]=1540;
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
  var aPosY=[
            /*Startposition*/1130,1130,
            /*Weg nach Oben*/960,830,
            /*Vorraum oben*/710,
            /*Oben*/550,550,
            /*Unten*/1310
            ];
  // Zus�tzlicher Punkt f�r Angreifer
  if(iMode==TWRATCK_AIMode_Attack||iMode==TWRATCK_AIMode_Expand)
  {
    aPosY[GetLength(aPosY)]=710;
  }
  return aPosY;
}

/*
  Spawnposition f�r die Truppen
*/
public func GetCrapStartPosition(iTeam,fY)
{
  if(fY)
    return 106*GetScenMapZoom()+GetScenMapZoom()/2;
  if(iTeam==1)
    return RandomX(34*GetScenMapZoom(),57*GetScenMapZoom());
  if(iTeam==2)
    return RandomX(231*GetScenMapZoom(),254*GetScenMapZoom());
}

public func Script20()
{
  CheckAIJoin();
}
