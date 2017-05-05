/*-- Apocalyptic Mode effects --*/

#strict 2

global func FxCreateTeraFlintsTimer()
{
	for (var i = 0; i < GetPlayerCount(); ++i)
	{
		var clonk = GetCrew(GetPlayerByIndex(i));
		if (!clonk) continue;

		if (clonk->ContentsCount(EFLN) < 3) clonk->CreateContents(EFLN);
	}

	return 1;
}

global func FxShakeScreenTimer()
{
	ShakeViewPort(10);
	return 1;
}

global func FxSkyAdjustStart(object target, int effectNumber)
{
	EffectVar(0, 0, effectNumber) = 255;
	EffectVar(1, 0, effectNumber) = 1;
	return 1;
}

global func FxSkyAdjustTimer(object target, int effectNumber)
{
	var color = EffectVar(0, 0, effectNumber);
	var decrease = EffectVar(1, 0, effectNumber);

	// Increase/decrease color value
	if (decrease)
	{
		--color;
	}
	else
	{
		++color;
	}

	// Switch direction?
	if (color <= 150)
	{
		color = 150;
		decrease = false;
	}
	else if (color >= 255)
	{
		color = 255;
		decrease = true;
	}

	// Apply color
	SetSkyAdjust(RGB(255, color / 2, color / 4), RGB(128, color / 2, color / 4));
	SetGamma(RGB(2, 0, 0), RGB(128, color / 2, color / 4), RGB(180, color /2 , color / 4));
	
	EffectVar(0, 0, effectNumber) = color;
	EffectVar(1, 0, effectNumber) = decrease;

	return 1;
}

global func FxBottomTimer()
{
	for (var i = 0; i < GetPlayerCount(); ++i)
	{
		var clonk = GetCrew(GetPlayerByIndex(i));
		if (clonk && clonk->GetY() >= LandscapeHeight() - 15) clonk->SetPosition(clonk->GetX() + RandomX(-1, 1), 0);
	}
	
	return 1;
}