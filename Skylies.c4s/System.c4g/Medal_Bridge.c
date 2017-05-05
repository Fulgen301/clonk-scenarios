/*-- Brückensegment --*/

#strict 2
#appendto BRDG

func Lock(quiet, dont_descend) 
{
  if(!is_locked)
    GameCallEx("OnBridgeFix",true,this);
  return _inherited(quiet,dont_descend);
}

func Release(quiet, dont_ascend) 
{
  if(is_locked)
    GameCallEx("OnBridgeFix",false,this);
  return _inherited(quiet, dont_ascend);
}

func Damage()
{
  if(is_locked)
    if(GetDamage(this) >= GetDefCoreVal("BlastIncinerate","DefCore",BRDG))
      GameCallEx("OnBridgeFix",false,this);
  return  _inherited(...);
}
