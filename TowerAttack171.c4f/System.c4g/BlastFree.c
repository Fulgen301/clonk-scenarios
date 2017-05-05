/*-- Knochen ausfaden --*/

#strict
#appendto BONE
#appendto ROCK

func Initialize() {
  Schedule("FadeOut()",350,0,this);
  return(_inherited());
}
