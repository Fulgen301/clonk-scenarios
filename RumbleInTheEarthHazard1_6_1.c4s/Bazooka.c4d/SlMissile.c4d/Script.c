/* Rakete */

#strict

public func Acceleration() { return(10); }
public func MaxTime() { return(100); }
public func MaxSpeed() { return(200); }

local iSpeed, iDamage, exploding;
local shooter;

func Initialize() {
  _inherited();
  AddAlienFlareEffect(this(),300);
}

func Construction(object byObj) {
  // nichts? :C
  if(!byObj)
    return();
  // Waffe?
  shooter = GetShooter(byObj);
}

public func Launch(int iAngle, int iDmg, int speed)
{
  if(!speed) speed = 20;
  iSpeed = speed;
  iDamage = iDmg;
  if(!iDamage) iDamage = 35;

  SetR(+iAngle);
  SetXDir(+Sin(iAngle,iSpeed));
  SetYDir(-Cos(iAngle,iSpeed));
  SetAction("Travel");

  AddLight(100,RGB(255,127,0),this(),GLOW);

  AddEffect("HitCheck", this(), 1,1, 0, SHT1,shooter,true);
}

/* Timer */

private func Accelerate() {
  if(iSpeed < MaxSpeed())
    iSpeed += Acceleration();

  SetXDir(+Sin(GetR(),iSpeed));
  SetYDir(-Cos(GetR(),iSpeed));
}

private func Smoking() {

  var dist = Distance(0,0,GetXDir(),GetYDir());
  var maxx = +Sin(GetR(),dist/10);
  var maxy = -Cos(GetR(),dist/10);
  var ptrdist = 50;

  for(var i=0; i<dist; i+=ptrdist) {

    var x = -maxx*i/dist;
    var y = -maxy*i/dist;


    var rand = RandomX(-30,30);
    var xdir = +Sin(GetR()+rand,20);
    var ydir = -Cos(GetR()+rand,20);

    CreateParticle("Thrust",x,y,GetXDir()/2,GetYDir()/2,RandomX(80,100),RGBa(255,200,200,60),0,0);
    CreateParticle("Smoke2",x,y,xdir,ydir,RandomX(100,120),RGBa(220,200,180,0),0,0);
  }
}

private func Traveling()
{
  // kommt nich weiter
  if(GetActTime() >= MaxTime()) return(Hit());

  // beschleunigen
  Accelerate();

  // Effekte
  Smoking();
}

/* Treffer */

private func Hit() {
  HitObject();
}

private func HitObject(object pObject) {
  exploding = true;
  BlastObjects(GetX(), GetY(), iDamage/2);
  for(var i = 4+Random(3), glob ; i ; i--)
    {
    glob = CreateObject(SLST, 0, 0, GetOwner());
    glob ->~ Launch(RandomX(-40,40), RandomX(-40,40), iDamage);
    }
  CastParticles("SlimeGrav", 10, 25, 0, 0, 20, 40, RGBa(0, 240, 0, 10), RGBa(20, 255, 20, 75));
  CastParticles("FrSprk", 30, 5, 0, 0, 70, 130, RGBa(0, 240, 0, 10), RGBa(20, 255, 20, 75));
  Sound("SlimeHit");
  Sound("Poff");
  Explode(iDamage,0,0,0,1);
}

public func Damage() {
  if(GetDamage() > 20 && !exploding)
    Hit();
}

public func EMPShock() {
  SetAction("Idle");
}

public func IsBulletTarget() { return(true); }
public func NoDecoDamage() { return(true); }
public func IsMachine() { return(true); }
