/*-- Neues Script --*/

#strict
#appendto KNIG

func ContextAntiStuck()
{
    [Anti Stuck|Image=STUC]
    FindObject(STUC)->Activate(GetOwner());
}

//Für den T-Flint
protected func Collection(pObj) {
 var OldOwner=GetOwner(pObj);
 SetOwner(GetOwner(this()),pObj);
 if(GetID(pObj)==TFLN || GetID(pObj)==STFN) { 
  //Log(Format("SetOwner(%d,Object(%d),GetName(Object(%d)))",OldOwner,ObjectNumber(pObj),ObjectNumber(pObj)));
  Schedule(Format("SetOwner(%d,Object(%d))",OldOwner,ObjectNumber(pObj)),1);
  }
 _inherited (...);
 }  
 
protected func Collection2(pObj) {
 var OldOwner=GetOwner(pObj);
 SetOwner(GetOwner(this()),pObj);
 if(GetID(pObj)==TFLN || GetID(pObj)==STFN) { 
  //Log(Format("SetOwner(%d,Object(%d),GetName(Object(%d)))",OldOwner,ObjectNumber(pObj),ObjectNumber(pObj)));
  Schedule(Format("SetOwner(%d,Object(%d))",OldOwner,ObjectNumber(pObj)),1);
  }
 _inherited (...);
 }  