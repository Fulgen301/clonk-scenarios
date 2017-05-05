/*-- Spawn Point Spawner --*/

#strict 2

local locations, definitions, spawnInterval;
local sumProbability;

public func CreateSpawnPoints()
{
	for (var pos in locations)
	{
		CreateObject(SNPT, pos[0], pos[1], NO_OWNER)->Enable(this);
	}
}

// [[x1, y1], [x2, y2], ...]
public func SetLocations(array locations)
{
	LocalN("locations") = locations;
}

// [[FLNT, 50], [SFLN, 20], ...]
public func SetDefinitions(array definitions)
{
	LocalN("definitions") = definitions;

	sumProbability = 0;
	for (var def in definitions)
	{
		sumProbability += def[1];
	}
}

public func GetSpawnInterval() { return spawnInterval; }

public func SetSpawnInterval(int spawnInterval)
{
	LocalN("spawnInterval") = spawnInterval;
}

public func GetRandomDefinition()
{
	var rnd = Random(sumProbability);
	for (var def in definitions)
	{
		rnd -= def[1];
		if (rnd < 0) return def[0];
	}
}
