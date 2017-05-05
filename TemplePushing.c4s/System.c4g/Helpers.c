/*-- Helpers --*/

#strict 2

global func IIf(expression, truePart, falsePart)
{
	if (expression)
	{
		return truePart;
	}
	else
	{
		return falsePart;
	}
}

global func RGBpA(int rgb, int a) { return (a & 255)<<24 | rgb & 0xFFFFFF; }

global func CleanAngle(&angle)
{
	if (angle > 360) angle = angle % 360;
	else while (angle < 0) angle += 360;
}

global func Angle180(int angle)
{
	CleanAngle(angle);
	if (angle > 180) angle -= 360;
	return angle;
}

global func Angle360(int angle)
{
	CleanAngle(angle);
	return angle;
}
