/*-- Neues Objekt --*/

#strict
local Target;

func Initialize() {
   
  return(1);
}
func Set(object ptar) {
   Target = ptar;
   SetAction("Fly");
  return(1);
}
public func Check() {
  if(!Target) RemoveObject();
  if(Target) SetPosition(GetX(Target),GetY(Target)-25);
  return(1);
}
