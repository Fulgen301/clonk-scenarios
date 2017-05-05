/*-- Neues Script --*/

#strict
#appendto KNIG

func ContextAntiStuck()
{
    [Anti Stuck|Image=STUC]
    FindObject(STUC)->Activate(GetOwner());
}
