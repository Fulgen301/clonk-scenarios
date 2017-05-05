/*-- Find_PathFree --*/

#strict

global func Find_PathFree(iX,iY)
{
  return Find_Eval(Format("PathFree(%d,%d,GetX(),GetY())",GetX()+iX,GetY()+iY));
}

global func Find_NotHidden()
{
  return Find_And(Find_Func("Visible",GetOwner()),Find_Not(Find_Func("IsHidden")),Find_NoContainer());
}
