/*-- Bazooka --*/

#strict

#include WEPN

// Anzeige in der Hand
public func HandSize() { return(850); }
public func HandX()    { return(3000); }
public func HandY()    { return(0);  }

public func FMData1(int data)
{
  if(data == FM_Name)   return("$Missile$");
  if(data == FM_Icon)     return(MISS); 
  if(data == FM_AmmoID)   return(MIAM);
  if(data == FM_AmmoLoad) return(1);

  if(data == FM_Reload)   return(160);
  if(data == FM_Recharge)   return(1);

  if(data == FM_Aim)    return(1);

  if(data == FM_Condition) return(!GetUpgrade(KLAS));

  if(data == FM_Damage) return(40);

  return(Default(data));
}

public func BotData1(int data)
{
  if(data == BOT_Range)    return(600);
  if(data == BOT_DmgType)  return(DMG_Explosion);
  if(data == BOT_Power)    return(BOT_Power_LongLoad);

  return(Default(data));
}

public func FMData2(int data)
{
  if(data == FM_Name)   return("$HMissile$");
  if(data == FM_Icon)     return(HMIS); 
  if(data == FM_AmmoID)   return(MIAM);
  if(data == FM_AmmoLoad) return(1);

  if(data == FM_Reload)   return(160);
  if(data == FM_Recharge)   return(1);

  if(data == FM_Aim)    return(1);

  if(data == FM_Condition) return(GetUpgrade(KLAS));

  if(data == FM_Damage) return(35);

  return(Default(data));
}

public func BotData2(int data)
{
  if(data == BOT_Range)    return(700);
  if(data == BOT_DmgType)  return(DMG_Explosion);
  if(data == BOT_Power)    return(BOT_Power_LongLoad);

  return(Default(data));
}

public func FMData3(int data)
{
  if(data == FM_Name)   return("$MissileX$");
  if(data == FM_Icon)     return(MISX); 
  if(data == FM_AmmoID)   return(MIAM);
  if(data == FM_AmmoLoad) return(1);

  if(data == FM_Reload)   return(160);
  if(data == FM_Recharge)   return(1);

  if(data == FM_Aim)    return(1);

  if(data == FM_Condition) return(GetUpgrade(KRFL));

  if(data == FM_Damage) return(35);

  return(Default(data));
}

public func BotData3(int data)
{
  if(data == BOT_Range)    return(700);
  if(data == BOT_DmgType)  return(DMG_Explosion);
  if(data == BOT_Power)    return(BOT_Power_LongLoad);

  return(Default(data));
}

public func FMData4(int data)
{
  if(data == FM_Name)   return("$SMissile$");
  if(data == FM_Icon)     return(SMIS); 
  if(data == FM_AmmoID)   return(MIAM);
  if(data == FM_AmmoLoad) return(1);

  if(data == FM_Reload)   return(160);
  if(data == FM_Recharge)   return(1);

  if(data == FM_Aim)    return(1);

  if(data == FM_Condition) return(GetUpgrade(KRFL));

  if(data == FM_Damage) return(35);

  return(Default(data));
}

public func BotData4(int data)
{
  if(data == BOT_Range)    return(700);
  if(data == BOT_DmgType)  return(DMG_Explosion);
  if(data == BOT_Power)    return(BOT_Power_LongLoad);

  return(Default(data));
}

public func FMData5(int data)
{
  if(data == FM_Name)   return("$SlMissile$");
  if(data == FM_Icon)     return(SLMI); 
  if(data == FM_AmmoID)   return(MIAM);
  if(data == FM_AmmoLoad) return(1);

  if(data == FM_Reload)   return(160);
  if(data == FM_Recharge)   return(1);

  if(data == FM_Aim)    return(1);

  if(data == FM_Condition) return(GetUpgrade(KSLM));

  if(data == FM_Damage) return(20);

  return(Default(data));
}

public func BotData5(int data)
{
  if(data == BOT_Range)    return(700);
  if(data == BOT_DmgType)  return(DMG_Explosion);
  if(data == BOT_Power)    return(BOT_Power_LongLoad);

  return(Default(data));
}

public func Fire1() { LaunchRocket(MISS,Contained()->~AimAngle(20), GetFMData(FM_Damage, 1)); }
public func Fire2() { LaunchRocket(HMIS,Contained()->~AimAngle(20), GetFMData(FM_Damage, 2)); }
public func Fire3() { LaunchRocket(MISX,Contained()->~AimAngle(20), GetFMData(FM_Damage, 3)); }
public func Fire4() { LaunchRocket(SMIS,Contained()->~AimAngle(20), GetFMData(FM_Damage, 4)); }
public func Fire5() { LaunchRocket(SLMI,Contained()->~AimAngle(20), GetFMData(FM_Damage, 5)); }

public func LaunchRocket(rid, angle, dmg) {

  var user = Contained();
  var x,y;
  user->WeaponEnd(x,y);
  // not too near to clonk
  x = x*3/2;
  y = y*3/2;

  var rocket = CreateObject(rid,x,y,GetController(user));
  rocket->Launch(angle, dmg);

  // Effekte
  var ax, ay, xdir, ydir;
  user->WeaponBegin(ax,ay);
  xdir = ax-x;
  ydir = ay-y;

  CreateParticle("Thrust",ax,ay,xdir/2,ydir/2,80,RGBa(255,200,200,0),0,0);

  for(var i=0; i<20; ++i) {
    var rand = RandomX(-10,+10);
    CreateParticle("Smoke2",ax+Sin(angle,rand),ay-Cos(angle,rand),
                   RandomX(0,2*xdir),RandomX(0,2*ydir),
                   RandomX(80,140),RGBa(220,200,180,0),0,0);
  }

  // Sound
  Sound("Rocket");
}

/* Upgrade */

// Soundeffekte

public func OnReload()
{
  Sound("RocketLoad");
}

public func OnEmpty()
{
  Reload();
}


public func IsUpgradeable(id uid) {
  if(GetUpgrade(uid))
    return(false);
  
  if(uid == KSLM) return("$KSLMUpgradeDesc$");
  if(uid == KLAS) return("$KLASUpgradeDesc$");
  if(uid == KRFL) return("$KRFLUpgradeDesc$");
}

public func OnUpgrade(id uid) {
  var own = GetOwner(Contained());
  if(uid == KSLM) {
    // Feuermodus wechseln
    SetFireMode(5);
    if(Contained()) HelpMessage(own,"$KSLMUpgraded$",Contained());
    return(true);
  }
  if(uid == KLAS) {
    // Feuermodus wechseln
    SetFireMode(2);
    if(Contained()) HelpMessage(own,"$KLASUpgraded$",Contained());
    return(true);
  }
  if(uid == KRFL) {
    // Feuermodus wechseln
    SetFireMode(3);
    if(Contained()) HelpMessage(own,"$KRFLUpgraded$",Contained());
    return(true);
  }
}

public func OnDowngrade(id uid) {
  if(uid == KLAS) {
    SetFireMode(1);
    return(true);
  }
  if(uid == KSLM) {
    SetFireMode(1);
    return(true);
  }
  if(uid == KRFL) {
    SetFireMode(1);
    return(true);
  }
}

