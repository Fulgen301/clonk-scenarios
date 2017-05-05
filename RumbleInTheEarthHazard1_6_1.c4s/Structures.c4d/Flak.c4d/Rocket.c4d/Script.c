/* Rakete */

#strict

func Initialize()
{
  SetAction("Fly");
  return(1);
}

func Flying()
{ 
  for (var victim in FindObjects(Find_InRect(-5, -10, 10, 20), Find_NoContainer()))
  {
    var b1 = !ObjectCount(NF5B) || Hostile(GetController(), GetController(victim), 1);
    var b2 = GetOCF(victim) & OCF_Alive();
    var b3 = GetOCF(victim) & OCF_Container();
    var b4 = GetOCF(victim) & OCF_Grab();
 
    if ((b1 && b2) || b3 || b4) return(Damage());
  }
  var dir = GetDir();

  var x1 = -16 * dir + 8;
  var y1 = 6;
  var s1 = 5;

  Smoke(x1, y1, s1);

  if (Random(2))
  {
    var x2 = -36 * dir + 18;
    var y2 = -1 + dir;
    var s2 = 150;

    var xDir = Sin(180 * dir - 90, 1000);
    var yDir = -Cos(180 * dir - 90, 1000);

    var c = RGBa(255, RandomX(100, 200), 100, 150);

    CreateParticle("EkeAfterburner2", x2, y2, xDir, yDir, s2, c, this());
  }
  return(1);
}

func Damage()
{
  if (GetDamage() < 1) return(1);
  return(Hit());
}

func Hit()
{
  Schedule("Explode(20)", 1);
  return(1);
}