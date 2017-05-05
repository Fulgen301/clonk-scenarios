/*-- Liane --*/

#strict

local isTot;

protected func Construction()
{
  // Zufälliges Aussehen
  SetAction("Vine");
  SetPhase(Random(10));
  // In Kürze Position anpassen
  AddEffect("AdjustGrowthPos", this(), 1, 1, this());
  if(!Random(3)) CreateObject(GetID(),0,60,-1);
}

public func GetVineLength()
{
  return (GetCon() * GetDefCoreVal("Height") / 100);
}

public func FxAdjustGrowthPosTimer()
{
  // Effekt entfernen
  RemoveEffect("AdjustGrowthPos", this());
  // Y-Position anpassen (Wachstumsverschiebung der Engine ausgleichen)
  SetPosition(GetX(), GetY() + GetVineLength());   
}
public func Check(){
// Eingebaut? Hm.
if(GBackSolid(0,64)){ RemoveObject(); }

if(!isTot){
 if(!GBackSolid(0,-8)){ // Keine Decke?
  if(!FindObject(VINE,0,-12)){ // Nicht mal eine andere?
    isTot = 1;
   }
  }
 }
if(isTot) {
 if(GetCon() > 60){ SetCon(GetCon()-1); }
 SetRDir(RandomX(-4,4));
 SetCategory(C4D_Vehicle);
 }
}
public func Hit(){
if(isTot)
CastObjects(BUET,12,50);
RemoveObject();
}
