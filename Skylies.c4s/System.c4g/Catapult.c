#strict
#appendto CATA

private func Projectile()
{
  var pProjectile=Contents();
  var iX = (GetDir()*2-1)*12;
  var iY = -10;
  var iR = Random(360);
  var iXDir =  +8 * (GetDir() * 2 - 1) * iPhase / 6;
  var iYDir = -12 * iPhase / 6;
  var iRDir = 30;
  //Hier Owner setzen fürs Killtracing
  SetController(GetOwner(GetActionTarget(1)),pProjectile);
  Exit(pProjectile,iX,iY,iR,iXDir,iYDir,iRDir);
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