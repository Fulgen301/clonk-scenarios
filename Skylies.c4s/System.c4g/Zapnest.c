/*-- Neues Script --*/

#strict
#appendto ZAPN

public func BreakUp(int num)
{
  var x,y;
  if(!num) num=28;
  for (var i=0;i<num;++i) 
  {
    x=Random(11)-5;
    y=Random(11)-5;
    if (!GBackSolid(x,y))
    {
      var pZap = CreateObject(ZAP1,x,y,-1);
      SetOwner(GetController(this),pZap);
    }
  }
  RemoveObject();
}
