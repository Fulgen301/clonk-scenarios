/*-- Neues Script --*/

#strict
#appendto ANVL

private func Forging() {
  // Noch nicht fertig
  if (GetActTime() < 150) return(0);

  var pProduct = ComposeContents(product);
  // Objekt auswerfen
  if(pProduct)
    Exit(pProduct);

  GameCallEx("OnAnvilWork",GetOwner(FindCrewContents()));    // An die Medaile senden

  // Aktion beenden und Clonk auswerfen
  ProductionCancel();
  return(1);
}