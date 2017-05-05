/*-- Prevent rock strike from hitting allies --*/
#appendto BIRK
#strict 2

func QueryOwnCatchBlow(object target)
{
	return !Hostile(GetOwner(), target->GetOwner());
}
