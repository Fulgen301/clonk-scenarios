/*--- Bausatz ---*/

#strict

public func Activate(pClonk)
{ 
  // Clonk anhalten
  SetComDir(COMD_Stop(), pClonk);
  CreateMenu(FK5B, pClonk, 0, 2);
  AddMenuItem("Flak", "Installflak", FK5B, pClonk, 0, pClonk, GetDesc(0, FK5B));
  AddMenuItem("Pulskanone", "Installpkanone", PC5B, pClonk, 0, pClonk, GetDesc(0, PC5B));
  AddMenuItem("Teslaspule", "InstallTesla", TC5B, pClonk, 0, pClonk, GetDesc(0, TC5B));
  return(1);
}

protected func Hit()
{
  Sound("RockHit*");
    return(1);
}

func Installflak(clonk){
   CreateObject(FK5B,0,13,GetOwner(this()));
   RemoveObject();
}

func Installpkanone(clonk){
   CreateObject(PC5B,0,13,GetOwner(this()));
   RemoveObject();
}

func InstallTesla(clonk){
   CreateObject(TC5B,0,13,GetOwner(this()));
   RemoveObject();
}

/* Produkteigenschaften */

public func IsAnvilProduct() { return(1); }
