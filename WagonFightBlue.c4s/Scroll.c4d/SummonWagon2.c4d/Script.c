#strict

public func Activate(caster, real_caster) {
  var idir=1;
  if(GetDir(caster)==0)idir=-1;
  var wagn=CreateObject(WAGN,20*idir,38,GetOwner(caster));
  wagn->Fade();
  SWGN;
    var wagn=CreateObject(WAGN,60*idir,38,GetOwner(caster));
  wagn->Fade();
 Sound("Magic*");
  return(1);
 }

