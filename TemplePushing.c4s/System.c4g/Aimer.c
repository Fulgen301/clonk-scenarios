/*-- Improve Aimer selection --*/

#strict 2
#appendto AIMR

local targetDir;

private func DoDirControl(int iDir)
{
  // Abbruch, wenn das Zielobjekt weg ist
  if (!pTargetObject) return(Abort());
  // Richtungsänderung?
  if (iDir != targetDir)
  {
    iAngle=-iAngle;
    if(GetAction(pTargetObject) != "Scale")
    {
      pTargetObject->SetDir(iDir);
    }
    pArrow->UpdateAngle(iAngle);
    pTargetObject->~AimingAngle(iAngle);
    targetDir = iDir;
  }
  else
    // Tastendruck in Zielrichtung: Zaubern!
    DoEnter();
  return(1);
}

private func DoUpDownControl(int iByChange)
{
  // Abbruch, wenn das Zielobjekt weg ist
  if (!pTargetObject) return(Abort());
  // Zielrichtung ändern
  iAngle = BoundBy(Abs(iAngle) + iByChange, 0, 180);
  if (!targetDir) iAngle *= -1;
  pArrow->UpdateAngle(iAngle);
  pTargetObject->~AimingAngle(iAngle);
  return(1);
}

public func Create(object pCommandObject, object pMenuObj, int iStartAngle)
{
  var ret = _inherited(pCommandObject, pMenuObj, iStartAngle);
  targetDir = pTargetObject->GetDir();
  return ret;
}

public func Initialize()
{
	SetVisibility(VIS_Owner | VIS_Allies);
	return _inherited(...);
}
