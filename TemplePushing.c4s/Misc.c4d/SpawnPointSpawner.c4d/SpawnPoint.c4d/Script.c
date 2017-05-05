/*-- Spawnpoint --*/

#strict 2

local spawner;
local framesUntilRespawn;
local angle;

public func Enable(object spawner)
{
	LocalN("spawner") = spawner;
}

private func SpawnObject()
{
	var obj = CreateContents(spawner->GetRandomDefinition());
	SetGraphics(0, 0, Contents()->GetID(), GFX_Overlay, GFXOV_MODE_Base);
	SetClrModulation(obj->GetClrModulation() || RGB(255, 255, 255), this, GFX_Overlay);
	SetObjDrawTransform(1000, 0, 0, 0, 1000, -5000, 0, 1);
}

private func Timer()
{
	if (!Contents())
	{
		framesUntilRespawn -= 5;
		if (framesUntilRespawn <= 0) SpawnObject();
	}

	angle = (angle + 10) % 360;
	SetObjDrawTransform(1000, 0, 0, 0, 1000, Sin(angle, 8) * 1000 - 2000, 0, 1);
	if (Random(2)) CreateParticle("NoGravSpark", RandomX(-5, 5), RandomX(5, 10), 0, -5, 25, RGBa(210, 210, 255, 100));
}

protected func RejectEntrance(object container)
{
	// Still in countdown?
	if (!gameStarted) return true;

	// Container has to be a crew member
	if (!(container->GetOCF() & OCF_CrewMember)) return true;

	// Ready?
	if (!Contents()) return true;

	// Try to let container collect the object
	container->Collect(Contents());

	// Object still there? Then something went wrong
	if (Contents()) return true;

	container->Sound("Grab", false, 0, 0, GetOwner(container) + 1);

	SetGraphics(0, 0, 0, GFX_Overlay, GFXOV_MODE_Base);
	framesUntilRespawn = spawner->GetSpawnInterval();
	
	return true;
}
