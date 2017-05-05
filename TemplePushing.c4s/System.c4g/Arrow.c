/*-- Prevent firing clonk from hitting itself --*/
#strict 2
#appendto ARRW
#appendto FARW

local shooter;

func Launch(object shooterClonk)
{
	if (shooterClonk) shooter = shooterClonk;
	return _inherited(shooterClonk, ...);
}

func QueryOwnCatchBlow(object target)
{
	return target == shooter;
}
