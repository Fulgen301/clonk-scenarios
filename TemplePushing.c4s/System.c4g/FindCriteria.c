/*-- Additional FindObjects search criteria for a certain angle range --*/
#strict 2

global func SwapIfBigger(&smaller, &bigger)
{
	if (bigger < smaller)
	{
		var swap = smaller;
		smaller = bigger;
		bigger = swap;
	}
}

global func Find_Angle(int angleStart, int angleEnd, bool biggerPart, int x, int y)
{
	while (angleStart < 0) angleStart += 360;
	while (angleEnd < 0) angleEnd += 360;
	angleStart %= 360;
	angleEnd %= 360;
	SwapIfBigger(angleStart, angleEnd);
	if (angleEnd - angleStart > 180) biggerPart = !biggerPart;
	return [C4FO_Func, "Find_AngleCheck", angleStart, angleEnd, biggerPart, GetX() + x, GetY() + y];
}

global func Find_AngleCheck(int angleStart, int angleEnd, bool biggerPart, int x, int y)
{
	var angle = Angle(x, y, GetX(), GetY());
	var inside = Inside(angle, angleStart, angleEnd);
	var ret;
	if (biggerPart) ret = !inside;
	else ret = inside;
	return ret;
}

global func Find_Procedure(string procedure)
{
	return Find_FuncEqual("GetProcedure()", procedure);
}
