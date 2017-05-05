/*-- Minigun --*/

#strict

#include WEPN

// Anzeige in der Hand
public func HandSize() { return(900);  }
public func HandX()    { return(11000); }
public func HandY()    { return(-3000); }
public func BarrelYOffset(){return(-1000); }

// Daten für ersten Feuermodus
public func FMData1(int data)
{
  if(data == FM_Name)       return("Standard");
  if(data == FM_AmmoID)     return(STAM);
  if(data == FM_AmmoLoad)   return(50);

  if(data == FM_Reload)     return(260);
  if(data == FM_Recharge)   return(3);

  if(data == FM_AmmoUsage)  return(1);
  if(data == FM_AmmoRate)   return(2);
  if(data == FM_Auto)       return(true);
  if(data == FM_Aim)        return(-1);

  if(data == FM_Condition) return(!GetUpgrade(KSLM));

  if(data == FM_Damage)     return(3);

  return(Default(data));
}

public func BotData1(int data)
{
  if(data == BOT_Range)    return(500);
  if(data == BOT_Power)    return(BOT_Power_LongLoad);

  return(Default(data));
}

// Daten für ersten Feuermodus
public func FMData2(int data)
{
  if(data == FM_Name)       return("$Bouncing$");
  if(data == FM_AmmoID)     return(STAM);
  if(data == FM_AmmoLoad)   return(50);

  if(data == FM_Reload)     return(260);
  if(data == FM_Recharge)   return(3);

  if(data == FM_AmmoUsage)  return(1);
  if(data == FM_AmmoRate)   return(2);
  if(data == FM_Auto)       return(true);
  if(data == FM_Aim)        return(-1);

  if(data == FM_Condition) return(GetUpgrade(KSLM));

  if(data == FM_Damage)     return(3);

  return(Default(data));
}

public func BotData2(int data)
{
  if(data == BOT_Range)    return(500);
  if(data == BOT_Power)    return(BOT_Power_LongLoad);

  return(Default(data));
}

public func FMData3(int data)
{
  if(data == FM_Name)       return("Minigranaten");
  if(data == FM_AmmoID)     return(GRAM);
  if(data == FM_AmmoLoad)   return(25);

  if(data == FM_Reload)     return(260);
  if(data == FM_Recharge)   return(10);

  if(data == FM_AmmoUsage)  return(1);
  if(data == FM_AmmoRate)   return(1);
  if(data == FM_Auto)       return(true);
  if(data == FM_Aim)        return(-1);

  if(data == FM_Condition) return(GetUpgrade(KRFL));

  if(data == FM_Damage)     return(5);

  return(Default(data));
}

public func BotData3(int data)
{
  if(data == BOT_Range)    return(500);
  if(data == BOT_Power)    return(BOT_Power_LongLoad);

  return(Default(data));
}

// Feuern im ersten Feuermodus
public func Fire1()     // ungenaues aber heftiges Minigunfeuer
{ 
  var user = Contained();
  // Winkel: maximal 5° anvisieren, Streuung von 12°
  var angle = user->AimAngle(5)+RandomX(-6,+6);
  // Schuss an der Mündung der Waffe erstellen...
  var x,y;
  user->WeaponEnd(x,y);
  var ammo = CreateObject(SHT1,x,y,GetController(user));
  ammo->Launch(angle,300,600,4,100,GetFMData(FM_Damage, 1));
//public func Launch(int iAngle, int iSpeed, int iDist, int iSize, int iTrail, int iDmg, int iDmgPrec, int iGlowSize, int iAPrec, int iReflections)
  // Effekte
  MuzzleFlash(RandomX(20,50),user,x,y,angle);
  
  user->~WeaponBegin(x,y);
  var dir = GetDir(user)*2-1;
  BulletCasing(x,y,-dir*Cos(angle-35*dir,40+Random(20)),-dir*Sin(angle-35*dir,40+Random(20)),5);
}

// Feuern im zweiten Feuermodus
public func Fire2()     // ungenaues aber heftiges Minigunfeuer mit Abpralleffekt
{ 
  var user = Contained();
  // Winkel: maximal 5° anvisieren, Streuung von 12°
  var angle = user->AimAngle(5)+RandomX(-6,+6);
  // Schuss an der Mündung der Waffe erstellen...
  var x,y;
  user->WeaponEnd(x,y);
  var ammo = CreateObject(SHT1,x,y,GetController(user));
  ammo->Launch(angle,300,600,2,100,GetFMData(FM_Damage, 1), 0,0,0, 3);
//public func Launch(int iAngle, int iSpeed, int iDist, int iSize, int iTrail, int iDmg, int iDmgPrec, int iGlowSize, int iAPrec, int iReflections)
  // Effekte
  MuzzleFlash(RandomX(20,50),user,x,y,angle);
  
  user->~WeaponBegin(x,y);
  var dir = GetDir(user)*2-1;
  BulletCasing(x,y,-dir*Cos(angle-35*dir,40+Random(20)),-dir*Sin(angle-35*dir,40+Random(20)),5);
}

public func Fire3() { LaunchGrenade(GREN, 90,Contained()->~AimAngle( 5)+RandomX( -5, 5),5); }

// verschießt eine Granate
// idg:   ID der Granate
// speed: Geschwindigkeit
// angle: Winkel
public func LaunchGrenade(id idg, int speed, int angle, int mode) {
  var user = Contained();
  var dir = GetDir(user)*2-1;

  // Adjust angle
  // special on jetpack...
  if(user->GetAction() ne "JetpackFlight")
    angle = BoundBy(angle+GetYDir(user)*dir,-360,360);
  // calculate speed
  var xdir = Sin(angle,speed);
  var ydir = -Cos(angle,speed);

  var x,y;
  user->WeaponEnd(x,y);

  // create and launch
  var grenade=CreateObject(idg, x+xdir/10, y+ydir/10, GetController(user));
  grenade->Launch(xdir+GetXDir(user)/2, ydir+GetYDir(user)/2, 10);

  // effect
  Sound("GrenadeFire");

  CreateParticle("Thrust",x,y,GetXDir(user),GetYDir(user),80,RGBa(255,200,200,0),0,0);

  for(var i=0; i<20; ++i) {
    CreateParticle("Smoke2",x+RandomX(-5,+5),y+RandomX(-5,+5),
                   GetXDir(user)+RandomX(0,xdir/4),GetYDir(user)+RandomX(0,ydir/4),
                   RandomX(80,140),RGBa(200,200,200,0),0,0);
  }
}


// Soundeffekte

public func OnReload()
{
  Sound("MiniLoad");
}

public func OnAutoStart(int i)
{
  if(i == 1) Sound("MiniGun",0,0,0,0,1);
  if(i == 2) Sound("MiniGun",0,0,0,0,1);
  Sound("MiniTurn",0,0,0,0,1);
}

public func OnAutoStop(int i)
{
  if(i == 1) Sound("MiniGun",0,0,0,0,-1);
  if(i == 2) Sound("MiniGun",0,0,0,0,-1);
  Sound("MiniTurn",0,0,0,0,-1);
}


/* Upgrade */

public func IsUpgradeable(id uid) {
  //wir haben das Upgrade schon, bah.
  if(GetUpgrade(uid))
    return(false);
  
  if(uid == KRFL) return("Nach der Aufrüstung können kleine Granaten verschossen werden.");
  if(uid == KSLM) return("$KSLMUpgradeDesc$");
}

public func OnUpgrade(id uid) {
  var own = GetOwner(Contained());
  if(uid == KRFL) {
    SetFireMode(3);
    if(Contained()) HelpMessage(own, "Nun können kleine Granaten verschossen werden.", Contained());
    return(true);
  }
  if(uid == KSLM) {
    SetFireMode(2);
    if(Contained()) HelpMessage(own, "$KSLMUpgraded$", Contained());
    return(true);
  }
}

public func OnDowngrade(id uid) {
  if(uid == KRFL) {
    SetFireMode(1);
    return(true);
  }
  if(uid == KSLM) {
    SetFireMode(1);
    return(true);
  }
}

