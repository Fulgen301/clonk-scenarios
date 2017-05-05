/*-- Neues Script --*/

#strict 2
#appendto MART

func Activate(pCaster, pRealCaster) 
{
  var inh = _inherited(pCaster,pRealCaster);
  
  if(inh)
    GameCallEx("ArtefactActivation",pCaster);
  return inh;
}
