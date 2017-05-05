#strict

public func Activate(caster, real_caster) 
{
 for(var pWagon in FindObjects(Find_Distance(50),Find_Category(C4D_Structure)))
    pWagon->SetMode(1);
 Sound("Magic*");
  return(1);
 }

