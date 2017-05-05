/*-- Neues Script --*/

#strict

global func Find_Eval(szString) {
  
  return(Find_Func("DoEval",szString));
}

global func DoEval(szString)
{
  return eval(szString);
}
