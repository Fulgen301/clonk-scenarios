/*-- Weben --*/

#strict

protected func Initialize() {
  SetAction("Be");
  if(Random(3))
    SetCategory(C4D_Foreground());
  SetPhase(Random(5), 0);
  //SetClrModulation(RGBa(255,255,255,55+RandomX(-7,12)));
}

