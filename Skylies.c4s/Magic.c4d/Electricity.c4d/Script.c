/*-- Restless! --*/

#strict 2

static const EL0D_Timer = 1150; //30 Sekunden

func Activate(object pClonk)
{
  for(var pBuilding in FindObjects(Find_Distance(150),Find_Category(C4D_Structure)))
    if(GetDefCoreVal("LineConnect","DefCore",GetID(pBuilding)) & C4D_PowerInput)
    {
      AddEffect("MoarEnergy",pBuilding,100,10,0,GetID(this));  
      
      //Strompartikel, die zu den Gebäuden fliegen.
      var iAngle = Angle(GetX(pClonk),GetY(pClonk),GetX(pBuilding),GetY(pBuilding))-90;
      var iSpeed = Distance(GetX(pClonk),GetY(pClonk),GetX(pBuilding),GetY(pBuilding));

      DrawLightning(AbsX(GetX(pClonk)),AbsY(GetY(pClonk)),AbsX(GetX(pBuilding)),AbsY(GetY(pBuilding)),30,0xff0000);
    }
  RemoveObject(this);
  return true;
}

func FxMoarEnergyTimer(object pTarget, int iIndex, int iTime)
{
  if(iTime >= EL0D_Timer)
    return -1;
  //Bzzz!
  DoEnergy(10,pTarget);
  return true;
}

//Nehmen wir den Billigblitz, da der komplexere zu einer Endlosschleife geführt hat.
global func DrawLightning(int iX1, int iY1, int iX2, int iY2, int iDeviation, int iColor)
{
  CreateParticle("Flash",iX1,iY1,0,0,50,iColor);
  while(Distance(iX1,iY1,iX2,iY2) > 10)
  {
    var iAngle = Angle(iX1,iY1,iX2,iY2)-90-Abs(iDeviation%180)+Random(Abs(iDeviation%180)*2);
    iX1 += Cos(iAngle,5);
    iY1 += Sin(iAngle,5);
    CreateParticle("Flash",iX1,iY1,0,0,50,iColor);
  }
  return true;
}
