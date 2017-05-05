/*-- Ballon--*/

#strict

local MyToy;
local iTimer;
local iTurns;

func BorderFlip(int i)
{
  iTurns += i;

  if(Abs(iTurns) >= 30)
    Reward(FindObject(DL_M), GetController(this));

  return true;
}

/*Produktionseigentschaften*/
func IsAnvilProduct(){return(1);}

func Activate(pCaller)
{
  SetOwner(GetOwner(pCaller));
  CreateMenu(CLNK, pCaller, , C4MN_Extra_None, "Verbinden mit:", , C4MN_Style_Normal, false);

  //Aufgrund der Länge der Suchkriterien speichere ich die einfach mal einzeln in Variabeln.
  var aCriteria = Find_Or(Find_Category(C4D_Living),Find_Category(C4D_Object),Find_OCF(OCF_Collectible),Find_Func("BallonUse"));

  for(var pUse in FindObjects(Find_NoContainer(),Find_Distance(15),Find_Not(Find_Func("IsClonk")),aCriteria))
    if(GetID(pUse) != GetID(this))
      AddMenuItem(GetName(pUse), "Bind", GetID(pUse), pCaller, 0, 0, "Soll der Ballon mit diesem Objekt verbunden werden?", 0, pUse, pCaller);
}

func Bind(pUsed)
{
  SetPlrView(GetOwner(Contained()), this());
  MyToy = FindObject2(Find_ID(pUsed),Find_Distance(15));

  if(!MyToy) return false;

  var fern = CreateContents(BEFE, Contained());
  fern->SetToRem(this());
  SetAction("Fly");

  if(GetAlive(MyToy)) {
    var pMedal = FindObject(TP_M);
    if(pMedal && GetOwner(this()) != NO_OWNER)
      Reward(pMedal,GetOwner(this()));
  }// Medal!!1

  Exit(this());
  //SetPosition(GetX(MyToy),GetY(MyToy)-GetDefHeight(GetID(MyToy))/2);
}

func Flyaway()
{
  iTimer++;
  SetXDir( BoundBy(GetWind()/4,-10,+10));
  SetPosition(GetX(),GetY()+9+(GetDefHeight(GetID(MyToy))/2),MyToy);
  SetYDir(-1,MyToy);
  CheckWindY();

  var pObject = FindObject2(Find_Distance(20),Find_Category(C4D_Object),Find_Exclude(MyToy),Find_Exclude(this()));
  if(pObject){
   if(iTimer > 120){
   if(pObject->Contained()) return(0);
   DoHit();
   }
  }

  Exit(MyToy);
}
private func CheckWindY()
{
  SetYDir(-10+BoundBy(GetYDir() + RandomX(-GetYDir()) - 1 + Random(3), Max(GetYDir() - 1, -3), Min(GetYDir() + 1, 3)));
}

protected func FxIntWindYDirTimer(object target, int number, int time)
{
  SetYDir(BoundBy(GetYDir() + RandomX(-GetYDir()) - 1 + Random(3), Max(GetYDir() - 1, -3), Min(GetYDir() + 1, 3)));
}


func RejectEntrance(object new_container){if(MyToy) return(true);}

/* Externe Einwirkungen */

public func Poke()
{
  Sound("Rip");
  if(!Random(2)) DoHit();
}

/* Trefferkontrolle */

protected func RejectCollect(id idObject, object pObj)
{
  // Pfeile vertragen sich nicht mit einem Ballon
  if (DefinitionCall(idObject,"IsArrow"))
   // Nur, wenn der Pfeil sich auch bewegt
   if(GetXDir(pObj) || GetYDir(pObj))
  {
    // bei brennendem Pfeil anzünden
    if(OnFire(pObj)) Incinerate();
    // ansonsten abstürzen
    if(!Random(2)) Explode(RandomX(1,5));
    // in jedem Fall im Pfeil Hit auslösen (Sprengpfeil explodiert zB)
    ProtectedCall(pObj, "Hit");
    return(1);
  }
  return(1);
}
private func DoHit()
{
  Sound("Poff");
  CastParticles("FSpark", 30, 28, 0, 0, 70, 80, RGB(255,255,255),RGB(255,255,255));
  RemoveObject();
}
