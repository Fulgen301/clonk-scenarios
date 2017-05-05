/*-- Plöpp! --*/

#strict 2
#appendto CLNK

func CatchBlow(int iChange, object pTarget)
{
  //Clonk stirbt vom Treffer
  if(!GetAlive(this))
  {
    //Das Objekt hat auch den Effekt? Benachrichtigen.
    var iIndex = GetEffect("Flight",pTarget);
    EffectCall(pTarget,iIndex,"Kill",GetOwner(this));
    
    //Sven2-Medaille
    if(GetID(pTarget) == METO)
    {
      var pMedal = FindObject(S2_M);
      if(pMedal)
        Reward(pMedal,GetController(pTarget));
      if(GetEffect("BlindEffect",pTarget))
      {
        //Omgomg, Sven2+1!
        pMedal = FindObject(S3_M);
        if(pMedal)
          Reward(pMedal,GetController(pTarget));    
      }
    }

    //Wood of Doom!
    if(GetID(pTarget) == WOOD)
    {
      var pMedal = FindObject(WD_M);
      if(pMedal)
        Reward(pMedal,GetController(pTarget));
    }
    
    //It's magic
    if(GetID(pTarget) == MRCK)
    {
      var pMedal = FindObject(IM_M);
      if(pMedal)
        Reward(pMedal,GetController(pTarget));
    }
    
    //Terabeißer
    if(GetID(pTarget) == EFLN)
    {
      var pMedal = FindObject(TB_M);
      if(pMedal)
        Reward(pMedal,GetController(pTarget));
    }

    
    //Who-pulled-the-plug-Medaille
    if(GetEffect("WarpUSpellData",pTarget) || GetEffect("WarpUSpellData",this))
    {
      var pMedal = FindObject(WP_M);
      if(pMedal)
        Reward(pMedal,GetController(pTarget));
    }
  }
  return _inherited(...);
}
