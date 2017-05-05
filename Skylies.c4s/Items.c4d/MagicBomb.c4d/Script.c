/*--- Magiebombe ---*/

#strict


protected func Hit()
{
  Sound("Crystal*");
  CastParticles("PxSpark", 20,30, 0,-3, 70, 100, RGBa(100,100,250,0));
  
    for(var i = 0; i <= 36; i++)
    {
    var dwClr;
    dwClr = RGB(RandomX(1,40),RandomX(1,40),200+RandomX(1,50));
    var dwClr1 = RGB(RandomX(1,50),RandomX(1,50),200+RandomX(1,50));
    CreateParticle("PxSpark", 0, 0, Sin(i*10,30),Cos(i*10,30), Random(150)+20,dwClr);
    CreateParticle("PxSpark", 0, 0, Cos(i*10,30), Sin(i*10,30), Random(150)+20,dwClr1);     
    }

  for(var pObj in FindObjects(Find_OCF(OCF_CrewMember), Find_OCF(OCF_Alive), Find_Distance(50), Find_Not(Find_Owner(-1))))
  {
    Fling(pObj, -3+6*(GetX(pObj)>GetX()), -2);
    DoEnergy(-RandomX(15,30), pObj);
  }
  RemoveObject();
  return (1);
}

/* Kann in der Chemiefabrik hergestellt werden */
public func IsChemicalProduct() { return(1); }
