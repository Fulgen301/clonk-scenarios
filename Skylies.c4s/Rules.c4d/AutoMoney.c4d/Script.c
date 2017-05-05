/* Auto money */
//Auf den neuesten Stand gebracht.

#strict 2

func Initialize()
{
  AddEffect("Money",this,100,100,this);
  return true;
}

func FxMoneyTimer()
{
  for(var i=0; i<GetPlayerCount(); i++)
  {
    var iPlr = GetPlayerByIndex(i);
    SetWealth(iPlr,GetWealth(iPlr)+1);
  }
  return true;
}

protected func Activate(caller) 
{
  MessageWindow(GetDesc(), caller);
  return true;
}



