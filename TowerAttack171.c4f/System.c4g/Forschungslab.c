/* Forschungslabor */

#strict 2
#appendto RSRC

private func Researching()
{
  if(GetWealth(GetOwner())<10)
    return SetAction("Idle");
  DoWealth(GetOwner(),-10);
  return _inherited(...);
}

public func ResearchMenu(clonk)
{
  // Hauptmenü erzeugen
  ResearchStructures(CLNK, clonk);
}

protected func SelectResearchCategory(idImage, pClonk, dwCategory)
{
  // Auswahlmenü erzeugen
  CreateMenu(idImage, pClonk, this(), 0, "Alles wurde bereits erforscht");
  // Alle geladenen Baupläne überprüfen
  var i,idDef,iPlr=GetOwner(pClonk);
  while (idDef = GetDefinition(i++, dwCategory))
    // Passende Kategorie
    if (GetCategory(0, idDef) & C4D_Knowledge)
      // Dem Spieler noch nicht bekannt
      if (!GetPlrKnowledge(iPlr,idDef))
      {
	if(!(idDef->~NeedToBeResearched()))
	  continue;
        // Keine Forschungsgrundlage nötig oder Forschungsgrundlage vorhanden
        var idBase = DefinitionCall(idDef,"GetResearchBase"), fHasBase, j;
        fHasBase = !idBase || GetPlrKnowledge(iPlr,idBase); j=1;
        // Erweiterte Forschungsgrundlagen
        while (idBase = DefinitionCall(idDef, Format("GetResearchBase%d", ++j)))
          if (!GetPlrKnowledge(iPlr,idBase)) fHasBase=0;
        // Ist schon durch etwas anderes erforschbar? (Zugbrücke rechts -> Zugbrücke links etc.)
        var link;
        if (link = DefinitionCall(idDef, "GetResearchLink"))
          if (GetName(0, link)) // Linkdefinition auch tatsächlich geladen?
            if(!GetPlrKnowledge(iPlr, link) ) // Linkdefinition noch nicht erforscht? (passiert durch SetPlrKnowledge-Aufrufe oder Szenariovorgaben)
              continue;
        // Menüeintrag hinzufügen
        if (fHasBase) AddMenuItem("Forschen: %s", "SelectResearch", idDef, pClonk, 0, pClonk);
      }
  return true;  
}

public func StartResearch()
{
  _inherited(...);
}