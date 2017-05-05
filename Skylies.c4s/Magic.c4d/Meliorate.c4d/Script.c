/* Veredeln  */

#strict 2

public func Activate(object pCaster, object pRealcaster)
{
  //Leeres Inventar? Doofclonk.
  if(!Contents(0,pCaster))
  {
    RemoveObject(this);
    return false;
  }

  var aData = GameCall("GetMeliorateData");
  if(GetType(aData) == C4V_Array)
    if(Meliorate(pCaster,aData))
    {
      RemoveObject(this);
      return true;
    }

  aData = [[ROCK,GOLD],[ERTH,LOAM],[ORE1,METL],[METL,CNKT],[ASHS,COAL],[SPHR,FLNT],[FLNT,SFLN],[SFLN,EFLN],[TFLN,STFN],[CNCR,LIQG],[MUSH,CRYS],[DFSH,CFSH],[ARRW,ARWP],[FARW,FARP],[XARW,XARP],[ARWP,FARP],[FARP,XARP],[BARL,WBRL,WBRL,WBRL,OBRL,ABRL,ABRL,LBRL]];
  
  Meliorate(pCaster,aData);
  RemoveObject(this);
  return true;
}

global func Meliorate(object pClonk, array aData)
{
  if(GetType(aData[i]) != C4V_Array) return false;

  var pObj = Contents(0,pClonk);
  for(var i=0; i<GetLength(aData); i++)
  {
    if(GetType(aData[i]) != C4V_Array) continue;
    
    if(GetID(pObj) == aData[i][0])
    {
      var idObj = aData[i][Random(GetLength(aData[i])-1)+1];
      
      if(CreateContents(idObj,pClonk))
      {
        RemoveObject(pObj);
        return true;
      }
      continue;
    }
  }
  return false;
}

/* Zaubercombo */

public func GetSpellClass(object pMage) { return(EART); }
public func GetSpellCombo(pMage) { return ("65"); } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
