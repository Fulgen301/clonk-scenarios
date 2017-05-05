/*-- Extinguisher --*/

#strict 2

private func Check()
{
	if (!ActIdle()) return;
	for (var obj in FindObjects(Find_OCF(OCF_OnFire)))
	{
		if (!FindObject2(Find_ID(GetID()), Find_Action("IsOnFire"), Find_ActionTarget(obj), Find_OCF(OCF_Alive)))
		{
			var extinguisher = CreateObject(GetID(), 0, 0, NO_OWNER);
			extinguisher->SetAction("IsOnFire", obj);
		}
	}
}

private func DoExtinguish()
{
	var target = GetActionTarget();
	if (!target || !target->GetAlive())
	{
		RemoveObject();
		return;
	}

	if (GetActTime() > 200)
	{
		target->Extinguish();
		RemoveObject();
		return;
	}
}

protected func Activate(int player) { MessageWindow(GetDesc(), player); }
