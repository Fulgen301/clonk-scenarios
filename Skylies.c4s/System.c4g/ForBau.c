/*-- Neues Script --*/

#strict 2

#appendto FRCA

protected func GetForceFieldTime() { return( 5700); }

func FxForceFieldPSpellDamage(object pTarget, int iIndex, int iDmg, int iDmgType)
{
  if(ScriptCounter() > 500){
  EffectVar(0,pTarget,iIndex) += iDmg*60;
  Sound("Electric");
  CastParticles("MSpark", 5, 50, 0,0, 100, 200, RGBa(100,100,255,128), RGBa(0,0,255,0));
  CreateParticle("MSpark", 0,0, 1000, RGBa(50,50,255,150));

  var iTime = EffectVar(0, pTarget, iIndex);
  // Nach Ablauf der Zeit wird der Effekt gelöscht
  if (iTime >= GetForceFieldTime()) return FX_Execute_Kill;
  }
  return iDmg;
}