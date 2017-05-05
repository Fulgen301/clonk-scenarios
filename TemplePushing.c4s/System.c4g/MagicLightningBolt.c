/*-- Lightning Bolt --*/

#strict 2

#appendto LGTS

local caster;

private func Advance()
{
  var obj;
  
  // Einschlag
  var iVtx = GetVertexNum()-1, iVtxX = GetVertex(iVtx, 0), iVtxY = GetVertex(iVtx, 1);
  if (GBackSolid(iVtxX-GetX(), iVtxY-GetY() ))
    return(Remove());

  // Neuen Eckpunkt
  if (!AddVertex( iVtxX+iAdvX+RandomX(-5,5), iVtxY+iAdvY+RandomX(-5,5)))
    return(Remove());

  SetPosition(GetVertex(GetVertexNum()), GetVertex(GetVertexNum(), 1));
  
  // Im Wasser?
  if (GBackLiquid(iVtxX-GetX(), iVtxY-GetY() ))
  {
    // Alle Lebewesen in der Nähe bekommen was ab
    for (obj in FindObjects(Find_InRect(iVtxX-GetX()-400, iVtxY-GetY()-400, 800, 800), Find_Or(Find_OCF(OCF_Alive), Find_Func("IsForceField")), Find_NoContainer(), Find_Layer(GetObjectLayer()), Find_Exclude(caster)))
    {
      if(!PathFree(iVtxX, iVtxY, GetX(obj), GetY(obj))) continue;
      if(!GBackLiquid(GetX(obj)-GetX(), GetY(obj)-GetY())) continue;
      // Selber so ausrichten, dass die Schlagrichtung stimmt
      var xdiff = GetX(obj) - GetVertex(Max(GetVertexNum()-3, 0), 0);
      if (!xdiff) xdiff = iAdvX;
      if (xdiff > 0) SetDir(DIR_Right); else SetDir(DIR_Left);
      obj->~LightningStrike(this);
      Punch(obj, 12);
	  if(!Frozen(obj)) Freeze(obj);
      DrawParticleLine ("LightningSpark2", iVtxX-GetX(), iVtxY-GetY(), 
           GetX(obj)-GetX(), GetY(obj)-GetY(), 6, 60, RGB(0,100,255));
      DrawParticleLine ("LightningSpark2", iVtxX-GetX(), iVtxY-GetY(), 
            GetX(obj)-GetX(), GetY(obj)-GetY(),  3, 25, RGB(250,250,255));
    }
    return(Remove());
  }

  var findHostile = Find_And();
  if (iVtx < 4) findHostile = Find_Hostile(GetOwner(caster));
  
  // Objektanziehung
  iVtx = GetVertexNum()-1; iVtxX = GetVertex(iVtx, 0); iVtxY = GetVertex(iVtx, 1);
  for (var obj in FindObjects( Find_AtRect(iVtxX-GetX()-13, iVtxY-GetY()-13, 26, 26), Find_Or(Find_OCF(OCF_Alive), Find_Func("IsForceField")), Find_Layer(GetObjectLayer()), Find_NoContainer(), Find_Exclude(caster), findHostile ) )
  {
    if(!PathFree(iVtxX, iVtxY, GetX(obj), GetY(obj))) continue;
    Attraction(obj);
    break;
  }
  for(obj in FindObjects(Find_ID(GetID()), Find_Distance(35,iVtxX-GetX(), iVtxY-GetY()), Find_Layer(GetObjectLayer()), Find_Exclude(this()), Find_Exclude(caster)))
  {
    AttractionLightning(obj);
    break;
  }
  
  Timer();
  // Weiter	
  return;
}

public func Launch(object caller)
{
  caster = caller;
  return _inherited(...);
}
