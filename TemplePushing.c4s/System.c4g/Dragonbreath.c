/*-- Prevent caster from setting himself on fire --*/
#strict 2
#appendto MDBT

public func ActivateAngle(object pCaller, int iAngle)
{
	if (GetAction(pCaller) == "HoverCast") return 0;

	/*if (!GetDir(pCaller) && iAngle>0) CreateFireBreath(pCaller, 40, Sin(iAngle, 10), -Cos(iAngle, 10) - (Abs(iAngle) > 90) * 4, -Abs(iAngle)-90);
	else*/ CreateFireBreath(pCaller, 40, Sin(iAngle, 6), -Cos(iAngle, 8) - /*(Abs(iAngle) > 90) **/ 4, iAngle);

	Sound("DragonFire");

	RemoveObject();
	return 1;
}
