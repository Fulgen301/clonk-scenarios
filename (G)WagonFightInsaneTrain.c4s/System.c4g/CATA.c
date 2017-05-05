/*-- CATA --*/

#strict
#appendto CATA

local aRare; 
local aStandard; 

func Initialize() {
 aRare=[SFLN,FBMP,EFLN];
 aStandard=[STFN,FLNT,ROCK,TFLN,GUNP];
 CreateContents(aStandard[Random(GetLength(aStandard))]);
 CreateContents(aRare[Random(GetLength(aRare))]);
 AddEffect("ContShow",this(),100,5,this(),GetID(this()));
 return(_inherited());
 }
 
private func Projectile()
{
  var pProjectile=Contents();
  var iX = (GetDir()*2-1)*12;
  var iY = -10;
  var iR = Random(360);
  var iXDir =  +8 * (GetDir() * 2 - 1) * iPhase / 6;
  var iYDir = -12 * iPhase / 6;
  var iRDir = 30;
  Exit(pProjectile,iX,iY,iR,iXDir,iYDir,iRDir);
  SetController(GetController(),pProjectile);
  // Zufällige Streuung
  // Bei minimaler Spannung: -30 bis +30
  // Bei voller Spannung:    -80 bis +80
  var iDeviation = RandomX(-iPhase * 10 - 20, iPhase * 10 + 20);
  SetXDir(iXDir * 100 + iDeviation, pProjectile, 100);
  SetYDir(iYDir * 100 + iDeviation, pProjectile, 100);
  // Sicht verfolgen wenn kein automatischer Schuss
  if (GetActionTarget(1))
    SetPlrView(GetOwner(GetActionTarget(1)), pProjectile);
}

func FxContShowTimer(object pTarget, int iEffectNumber, int iEffectTime) {
 var sItems="";
 for(var i=0;i<ContentsCount(0,pTarget);i++) {
  sItems=Format("<c %x>%s{{%i}} </c>",RGBa(255,255,255,128),sItems,GetID(Contents(i,pTarget)));
  Message(sItems,pTarget);
  }
 return(1);
 }
