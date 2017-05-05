/*-- Neues Objekt --*/

#strict

#include BAS2

protected func ActivateEntrance(object pClonk){
SetPosition(GetX(pClonk),GetY(pClonk)-95,pClonk);
if(GetAction(pClonk) S= "Push") SetPosition(GetX(pClonk->GetActionTarget()),GetY(pClonk->GetActionTarget())-95,pClonk->GetActionTarget());
SetComDir(COMD_None(),pClonk);
SetCommand(pClonk,"");
return(1);
}
