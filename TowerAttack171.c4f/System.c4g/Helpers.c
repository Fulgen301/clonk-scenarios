/*-- Hilfsfunktionen --*/

#strict 2

global func RandomColor()
{
  var r=Random(10);
  var mod;
  if(!r--||!r--||!r--||!r--||!r--)mod=HSL(Random(256),255,127);
  if(!r--||!r--)                  mod=HSL(Random(256),255,RandomX(64,192));
  if(!r--)                        mod=HSL(Random(256),255,RandomX(127,255));
  if(!r--)                        mod=RGB(5,5,5);
  if(!mod) mod=RGB(255,255,255);
  return mod;
}
