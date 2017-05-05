#strict 2

func Attach(object to)
{
	SetOwner(GetOwner(to));
	SetAction("Attach", to);
	SetVisibility(VIS_Allies | VIS_God);
}

func Show(string text, int time)
{
	AddEffect("ShowText", this, 20, 1, this, GetID(), text, time);
}

func FxShowTextStart(object target, int effectNumber, int temp, string text, int time)
{
	if (temp) return;

	EffectVar(0, target, effectNumber) = text;
	EffectVar(1, target, effectNumber) = time;

	Message("@%s", target, text);
}

func FxShowTextTimer(object target, int effectNumber, int time)
{
	var showTime = EffectVar(1, target, effectNumber);
	if (time > showTime)
	{
		if (time >= showTime + showTime / 3) return FX_Execute_Kill;
		Message("@<c %x>%s</c>", target, RGBa(255, 255, 255, 255 - ((time - showTime) * 255)/(showTime / 3)), EffectVar(0, target, effectNumber));
	}
}

func FxShowTextStop(object target, int effectNumber, int reason, bool temp)
{
	if (!temp) Message("", target);
}

func FxShowTextEffect(string newEffectName, object target, int effectNumber)
{
	if(newEffectName == "ShowText")
	{
		RemoveEffect(0, target, effectNumber);
	}
}
