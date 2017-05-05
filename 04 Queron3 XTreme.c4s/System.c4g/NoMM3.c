#strict 2

global func CheckVersion()
{
  //Queron funktioniert mit M&M 3 nicht, also kanns auch direkt beendet werden.
  //M&M 3 hat sich einige Hazard-Funktionen gekrallt, die in 2.8 nicht enthalten waren.
  //Das wird hier ausgenutzt.
  var rock = CreateObject(ROCK, 0, 0, NO_OWNER);
  if (rock->~Chance(100))
  {
    //Schedule("GameOver()", 70);
    //FatalError("Es wird Metall und Magie 2.8 benötigt.|Szenario ist mit Version 3 und höher inkompatibel.");
    //return false;
  }
  RemoveObject(rock);
  return true;
}
