/* Puls */

#strict

func Initialize()
{
  SetAction("Fly");
  Sound("PC_Shoot*");
  return(1);
}

func Flying()
{
  var flightTime = GetActTime();

  if (!flightTime) return;
  if (flightTime > 5) SetYDir(GetYDir() + 2 - Random(4));
  if (flightTime > 25 + Random(25)) RemoveObject();

  var a1 = Find_Distance(10);
  var a2 = Find_NoContainer();
  var a3 = Find_OCF(OCF_Alive);
  var a4 = Find_Hostile(GetController());
  
  var victim;
  if (victim = FindObject2(a1, a2, a3, a4)) return(HitLiving(victim));

  CreateFX();
  return(1);
}

func CreateFX()
{
  var i = 10;
  while (--i)
  {  
    var x = -Sin(GetR(), -i * 2);
    var y = +Cos(GetR(), -i * 2);

    var xDir = GetXDir() / 2;
    var yDir = GetYDir() / 2;

    var size = 25 + Random(50); 
    var color = RGBa(255, 155 + Random(100), 0, Random(50));
    
    CreateParticle("EkePulse", x, y, xDir, yDir, size, color);
  }
  return(1);
}

func Splashing()
{
  RemoveObject();
  return(1);
}

func Hit()
{
  RemoveObject();
  return(1);  
}

func HitLiving(victim)
{
  var xDir = GetXDir();
  if (!xDir) xDir++;

  var x = xDir / Abs(xDir) * 5;
  var y = -1;

  //DoEnergy(-1, victim);
  Fling(victim, x, y);

  RemoveObject();
  return(1);
}