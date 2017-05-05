/*-- Anti-Tausend-Leichen-Script --*/

#strict
#appendto CLNK
#appendto BGNT
#appendto _ZMB

func Death(a) {
  _inherited(a);
  if(!GetAlive())
    Schedule("FadeOut(0,2)",1000,0,this);
}
