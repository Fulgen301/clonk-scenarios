/*-- Projektile faden aus --*/

#strict
#appendto ROCK
#appendto FLNT
#appendto TFLN

func Ejection(a,b,c,d,e,f,g,h) {
  _inherited(a,b,c,d,e,f,g,h);
  Schedule("FadeOut(0,2)",350,0,this);
}
