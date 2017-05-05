/*-- The Leak --*/
// Exit the mine before it's flooded
// Find mining equipment on the way to help you

#strict 2


/* Init */

static g_goal;

protected func Initialize()
{
	// Dig elevator shafts
	FindObject(ELEV, 656,216)->CreateShaft(580);
	FindObject(ELEV, 596,1585)->CreateShaft(500);
	// Script goal
	g_goal = FindObject(SCRG);
	if (!g_goal) g_goal = CreateObject(SCRG, 50, 50, NO_OWNER);
	g_goal->SetMessages("$Goal2$", "$Goal1$");
	// Message triggers
	AddMessageTrigger(520, 1800, 100, 300, "$Elev1$"); // blocked elevator
	AddMessageTrigger(100, 1470, 120, 150, "$Plans$"); // castle and research plans
	AddMessageTrigger(520, 1360, 280, 250, "$Elev2$"); // have to get up somehow
	AddMessageTrigger(0, 650, 800, 190, "$LastLavaLake$"); // need to pass the lava lake
	AddMessageTrigger(500, 200, 100, 80, "$Blimp$"); // take the blimp to the top right to win
} 

// Initialize after first player join (OpenClonk has InitializePlayers for this)
static g_player_joined;

protected func InitializePlayer(int plr)
{
	// Ignore AI joins
	if (GetPlayerType(plr) != C4PT_User) return;
	// Position at start
	var start_x = 410, start_y = 2320, i = 0, crew;
	var start_hut = FindObject(HUT2, start_x, start_y);
	var has_flag = !!FindObjectOwner(FLAG, NO_OWNER);
	if (start_hut)
	{
		// Start in hut. Ensure we have a flag.
		if (!has_flag)
		{
			start_hut->SetOwner(plr);
			start_hut->CreateContents(FLAG);
		};
		while ((crew = GetCrew(plr, i++))) crew->Enter(start_hut);
	}
	else
	{
		// Late join with hut destroyed? Game is probably lost anyway. Position at old hut location.
		while ((crew = GetCrew(plr, i++))) crew->SetPosition(start_x, start_y);
	}
	// First player join triggers intro
	if (!g_player_joined)
	{
		Schedule("GameCall(\"StartIntro\")", 1, 1);
		AddLeakEffect(); // System.c4g/Leak.c
		g_player_joined = true;
	}
	return true;
}

public func StartIntro()
{
	g_intro_earthquake_pos = [
		[350, 2280],
		[400, 2100],
		[150, 2187]
	];
	ScriptGo(1);
}

private func Script1()
{
	GlobalMsg("$Intro1$");
}

static g_intro_earthquake_pos, g_intro_earthquake_index;

private func Script16()
{
	// Create earthquakes in a few positions
	GlobalMsg("$Intro2$");
	var pos = g_intro_earthquake_pos[g_intro_earthquake_index++];
	if (pos)
	{
		var quake = LaunchEarthquake(pos[0], pos[1], 30);
		// Shift view to the earthquakes
		for (var plr in GetAllPlayers()) SetPlrView(plr, quake);
		goto(14);
	}
}

private func Script18()
{
	// Destroy the bottom elevator
	var elec = FindObject(ELEC, 596,1600);
	if (elec) elec->Incinerate();
}

private func Script21()
{
	// View back to the clonks
	for (var plr in GetAllPlayers()) SetPlrView(plr, GetCursor(plr));
	// Let's-get-out message
	GlobalMsg("$Intro3$");
}

private func Script40()
{
	GlobalMsg("$Goal1$", FindObject(GIDL));
	Sound("Ding");
}

static g_bonus; // Finished the bonus goal?

private func Script45()
{
	// Goal check
	if (!FindObject(0, 700, 0, 100, 60, OCF_CrewMember)) return goto(45);
	g_bonus = !!ObjectCount(GIDL, 0,0,LandscapeWidth(), 440);
	GlobalMsg(["$End$", "$End$||$EndBonus$"][g_bonus]);
	if (g_bonus)
	{
		// In OC, we have achievements. For CR, we can only give some settlement scores.
		for (var plr in GetAllPlayers()) DoScore(5000, plr);
	}
}

private func Script46()
{
	g_goal->Fulfill();
	// GameOver by goal
}
