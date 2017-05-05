/*-- Ecke --*/

#strict

protected func Initialize() {
  Snap();
  return(1);
}

public func Snap(int o,int p)
  {
  SetPosition((GetX()+5)/10*10-5+o, (GetY()+5)/10*10-5+p);
  }

public func SetP(int p)
  {
  SetAction("Edge"); SetPhase(p);
  SetSolidMask(p*10,0,10,10);
  }
  
// In Echt umwandeln
public func UpdateTransferZone()
{
  if(ScriptCounter()>1) return 0;
  var i=GetPhase();
  if(!i--)
    DrawMaterialQuad("Brick",GetX()-5,GetY()+5,GetX()-5,GetY()-5,GetX()+5,GetY()+5,GetX()+5,GetY()+5,1);
  if(!i--)
    DrawMaterialQuad("Brick",GetX()+5,GetY()+5,GetX()+5,GetY()-5,GetX()-5,GetY()+5,GetX()-5,GetY()+5,1);
  if(!i--)
    DrawMaterialQuad("Brick",GetX()-5,GetY()+5,GetX()-5,GetY()-5,GetX()+5,GetY()-5,GetX()+5,GetY()-5,1);
  if(!i--)
    DrawMaterialQuad("Brick",GetX()+5,GetY()+5,GetX()+5,GetY()-5,GetX()-5,GetY()-5,GetX()-5,GetY()-5,1);
  RemoveObject();
}
