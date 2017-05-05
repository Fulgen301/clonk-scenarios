/*-- Make Clonks able to shoot arrows without a bow --*/

#strict 2

#appendto ARWP

local coolingDown;

protected func Initialize()
{
	iUsedItems = RandomX(7,8);
}

private func CooledDown()
{
	return !coolingDown;
}

protected func Activate(object clonk) 
{
	[$Shoot$|Image=BOW1|Condition=CooledDown]

	if (!CooledDown()) return 0;

	// Extract an arrow from the pack
	var arrow = GetItem();

	// Make shooting clonk responsible for possible kill and owner of the arrow
	arrow->SetOwner(clonk->GetOwner());
	arrow->SetController(clonk->GetOwner());
	
	// Shoot
	// Do not launch fire arrows too close to the clonk to prevent incineration when launched while climbing
	var arrowPosX = IIf(arrow->GetID() == FARW, -10 + 20 * clonk->GetDir(), -3 + 6 * clonk->GetDir());
	arrow->Exit(0, arrowPosX, 5, -90 + 180 * clonk->GetDir(), -8 + 16 * clonk->GetDir(), -2);
	arrow->~Launch(clonk);
	
	// Start cooldown
	coolingDown = true;
	Schedule("coolingDown = false", RandomX(3, 5));
	
	// Play sound
	Sound("Arrow");

	return 1;
}
