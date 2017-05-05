#strict

public func Activate(caster, real_caster) {
  // Zaubernden Clonk ermitteln
  /*dir=GetDir(real_caster);
  for(var i in FindObjects(Find_ID(WAGN)))
  {
  i->Set(dir);
  }*/
  ChangeDir();
  Sound("Magic*");
  return(1);
 }

