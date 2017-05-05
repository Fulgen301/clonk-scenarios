/*-- Schalter --*/

#strict

func ControlRight()
{
  if(GetAction() eq "Idle")
    SetAction("Switch");
}

func ControlLeft()
{
  if(GetAction() eq "Idle")
    SetAction("Switch");
}

func Switched()
{
  var i;
  while(Local(i++)) Local(i-1)->~Activate(this);
}

func AddTarget(pTarget)
{
  var i; while(Local(i)) ++i;
  Local(i) = pTarget;
  return this;
}
