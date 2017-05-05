/* Message triggers: Display a message when a clonk enters a region */

#strict 2

global func AddMessageTrigger(x, y, wdt, hgt, message)
{
	// Add message trigger
	var search_param = Find_And(Find_OCF(OCF_CrewMember), Find_OCF(OCF_Alive), Find_InRect(x, y, wdt, hgt));
	return AddEffect("MessageTrigger",0,1,16,0,0,search_param, message);
}

global func FxMessageTriggerStart(object trg, int num, int tmp, array search_param, string message)
{
	// Remember parameters
  if(tmp) return;
  EffectVar(0, trg, num) = search_param;
  EffectVar(1, trg, num) = message;
  return FX_OK;
}

global func FxMessageTriggerTimer(object trg, int num, int time)
{
	var obj;
	if (obj = FindObject2(EffectVar(0, trg, num)))
	{
		// Clonk entered region: Show message (to all)
		GlobalMsg(EffectVar(1, trg, num), obj);
		// No more searching
		return FX_Execute_Kill;
	}
	return FX_OK;
}
