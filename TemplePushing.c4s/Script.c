/*-- Temple Pushing --*/

#strict 2

static const SBRD_FirstRow = 0;
static const SBRD_TeamSortCol = -3, SBRD_SortCol = -2, SBRD_NameCol = -1, SBRD_RelaunchesCol = 0, SBRD_ScoreCol = 1;
static const SORT_SORTCOL_Team = 0, SORT_SORTCOL_Player = 1, SORT_SORTCOL_Leaver = 2;

static const MaxTeamCount = 3;

static const PlrData_EnableAmbienceSounds = "TemplePushing_EnableAmbienceSounds";
static const PlrData_EnableAmbienceSounds_Yes = 1;
static const PlrData_EnableAmbienceSounds_No = 2;

static section, mode;
static numRelaunches;
static deathmatchEnabled, deathmatchWinScore;
static playerDeaths, playerScore, teamScore;
static sectionID;
static rotateInJumpEnabled;
static ambienceEnabled;
static suddendeathEnabled;
static loadingSection;
static eliminatedPlayers;
static gameStartMessage, countdown, gameStarted, gameOver;
static ambienceSounds;

func Initialize()
{
	ShowLobby();
	eliminatedPlayers = [];
	
	// Create Thrones for recreational purposes
	CreateObject(THRN, 590, 420, NO_OWNER);
	CreateObject(THRN, 410, 210, NO_OWNER);

	// Initial values
	deathmatchWinScore = 20;
	playerDeaths = CreateArray();
	playerScore = CreateArray();
	teamScore = CreateArray();
	countdown = 3;

	// Create setup menu
	var menu = CreateObject(SPMU, LandscapeWidth()/2, LandscapeHeight()-20, NO_OWNER);
	menu->LocalN("rotateInJumpEnabled") = true;
	menu->LocalN("numRelaunches") = 7;
	menu->LocalN("deathmatchWinScore") = 15;
	menu->LocalN("ambienceEnabled") = !GetLeague();
	
	// Modulate endscreen
	SetNextMission("TemplePushing.c4s", "Rematch", "$Rematch$");

	// Set possible spells
	SetScrollSpells([ABLA, MBOT, MFRB, MDBT, GVTY, MLGT, CFAL, MSSH, MINV, MARK, MFWV, MGFL, LAVS, MGPL, ICNL, MDFL, AFST, MGCY, MATT]);
	
	// Disable music altogether
	SetPlayList(" ");
}

/*func TeamRow(int team) { return 1 + team * 1000; }
func PlayerRow(int player) { return TeamRow(GetPlayerTeam(player)) + GetPlayerID(player); }*/
func TeamRow(int team) { return SBRD_FirstRow + team; }
func PlayerRow(int player) { return SBRD_FirstRow + MaxTeamCount + GetPlayerID(player); }

func InitializePlayer(int player)
{
	SetFoW(false, player);

	if (LobbyActive()) return;
	
	playerDeaths[GetPlayerID(player)] = 0;
	if (deathmatchEnabled)
	{
		var team = GetPlayerTeam(player);
		if (team)
		{
			SetScoreboardData(TeamRow(team), SBRD_NameCol, Format("<c %x>Team %s</c>", GetTeamColor(team), GetTeamName(team)));
			SetScoreboardData(TeamRow(team), SBRD_SortCol, " ", SORT_SORTCOL_Team);
		}
	}	
	SetScoreboardData(PlayerRow(player), SBRD_NameCol, GetTaggedPlayerName(player));
	SetScoreboardData(PlayerRow(player), SBRD_SortCol, " ", SORT_SORTCOL_Player);
	SetScoreboardData(PlayerRow(player), SBRD_TeamSortCol, " ", GetPlayerTeam(player));
	UpdateScoreboard(player);
	LaunchClonk(player, GetCrew(player));

	DoAmbienceSounds(player);
}

func GetRelaunchesLeft(int player) { return numRelaunches - playerDeaths[GetPlayerID(player)]; }

func RemovePlayer(int player)
{
	// Leaver?
	if (!LobbyActive() && (!deathmatchEnabled && GetRelaunchesLeft(player) >= 0 || deathmatchEnabled && !gameOver))
	{
		UpdateScoreboard(player, true);
		eliminatedPlayers[GetPlayerID(player)] = true;
		CheckGameOver();
	}
}

func UpdateScoreboard(int player, bool leaver)
{
	var playerID = GetPlayerID(player);
	var text;

	// Ignore invalid player numbers
	if (!playerID) return;

	// Deathmatch only: Team rows
	if (deathmatchEnabled)
	{
		var team = GetPlayerTeam(player);
		if (team)
		{
			if (teamScore[team] == deathmatchWinScore)
				text = "<c 00ff00>$Win$</c>";
			else
				text = Format("<c %x>%d</c>", GetTeamColor(team), teamScore[team]);

			SetScoreboardData(TeamRow(team), SBRD_ScoreCol, text, teamScore[team]);
		}
	}

	// Normal mode only: Show remaining relaunches
	if (!deathmatchEnabled)
	{
		var relaunchesLeft = numRelaunches - playerDeaths[playerID];
		if (relaunchesLeft < 0)
			text = "$Death$";
		else if (leaver)
			text = "{{SLVR}}";
		else
			text = Format("%d", relaunchesLeft);

		SetScoreboardData(PlayerRow(player), SBRD_RelaunchesCol, text, relaunchesLeft);
	}
	
	// Normal and deathmatch mode: Show player score
	if (leaver)
	{
		text = "{{SLVR}}";
		// Move leaver to the bottom of the list
		SetScoreboardData(PlayerRow(player), SBRD_NameCol, GetTaggedPlayerName(player));
		SetScoreboardData(PlayerRow(player), SBRD_SortCol, " ", SORT_SORTCOL_Leaver);
	}
	else
		text = Format("%d", playerScore[playerID]);
	
	SetScoreboardData(PlayerRow(player), SBRD_ScoreCol, text, playerScore[playerID]);

	// Sort rows
	SortScoreboard(SBRD_TeamSortCol);
	SortScoreboard(SBRD_ScoreCol, true);
	if (!deathmatchEnabled) SortScoreboard(SBRD_RelaunchesCol, true);
	SortScoreboard(SBRD_SortCol);

	UpdateComment();
}

func ShowLobby()
{
	LoadScenarioSection("Lobby");
	UpdateComment(true);
}

func SetupDone(object menu, string message)
{
	// Copy settings from menu
	sectionID = menu->LocalN("section");
	mode = menu->LocalN("mode");
	suddendeathEnabled = menu->LocalN("suddendeathEnabled");
	rotateInJumpEnabled = menu->LocalN("rotateInJumpEnabled");
	ambienceEnabled = menu->LocalN("ambienceEnabled");
	numRelaunches = BoundBy(menu->LocalN("numRelaunches"), 3, 10);
	deathmatchEnabled = menu->LocalN("deathmatchEnabled");
	deathmatchWinScore = BoundBy(menu->LocalN("deathmatchWinScore"), 10, 30);
	menu->RemoveObject();

	gameStartMessage = message;

	// Make sure LoadScenarioSection is not called from an object by swapping it out to a script counter callback
	ScriptGo(true);
}

func Script0()
{
	ScriptGo(false);

	// Change scenario section
	loadingSection = true;
	LoadScenarioSection(DefinitionCall(sectionID, "SectionName"));
	loadingSection = false;
	section = CreateObject(sectionID, 0, 0, NO_OWNER);
	ambienceSounds = mode->~AmbienceSounds() || section->~SectionAmbienceSounds() || [];
	mode = CreateObject(mode, 0, 0, NO_OWNER);
	
	var modeGamma = mode->~Gamma();
	if (modeGamma) SetGamma(modeGamma[0], modeGamma[1], modeGamma[2]);

	// Create spawnpoints
	if (!mode->~NoSpawnpoints())
	{
		var spawnPointSpawner = CreateObject(SPSR, 0, 0, NO_OWNER);
		spawnPointSpawner->SetLocations(section->SpawnpointLocations());

		spawnPointSpawner->SetDefinitions(mode->SpawnpointDefinitions());
		spawnPointSpawner->SetSpawnInterval(mode->SpawnpointInterval());
		
		spawnPointSpawner->CreateSpawnPoints();
	}
	
	// Create melee goal
	CreateObject(MELE, 0, 0, NO_OWNER);
	
	// Create rules
	CreateObject(TBMC, 0, 0, NO_OWNER); // Rule for enabling/disabling music
	CreateObject(_ETG, 0, 0, NO_OWNER);
	if (suddendeathEnabled) CreateObject(SDDT, 0, 0, NO_OWNER);
	if (rotateInJumpEnabled) CreateObject(RIJP, 0, 0, NO_OWNER);
	CreateObject(OFDR, 0, 0, NO_OWNER);
 
	SetScoreboardData(SBRD_Caption, SBRD_NameCol, " "); // Make sure the name column gets created first
	
	// Deathmatch?
	if (deathmatchEnabled)
	{
		CreateObject(DTHM, 0, 0, NO_OWNER);
		SetScoreboardData(SBRD_FirstRow, SBRD_NameCol, "$WinScore$");
		SetScoreboardData(SBRD_FirstRow, SBRD_SortCol, " ");
		SetScoreboardData(SBRD_FirstRow, SBRD_ScoreCol, Format("%d $Kills$", deathmatchWinScore));
	}
	else
	{
		SetScoreboardData(SBRD_Caption, SBRD_RelaunchesCol, "{{SREL}}");
	}
	
	SetScoreboardData(SBRD_Caption, SBRD_ScoreCol, "{{SKIL}}");

	for (var sound in ambienceSounds)
	{
		SoundLevel(sound[0], sound[1]);
	}
	
	// Initialize players
	for (var i = 0; i < GetPlayerCount(); ++i)
	{
		InitializePlayer(GetPlayerByIndex(i));
	}

	ShowCountdown();
}

func ShowCountdown()
{
	if (countdown == 0)
	{
		gameStartMessage = 0;
		Message("");
		Schedule("SetMaxPlayer(0)", 60 * 38);
		
		// Reenable crew
		for (var i = 0; i < GetPlayerCount(); ++i)
		{
			var player = GetPlayerByIndex(i);
			var clonk = GetCrew(player);
			if (!clonk) continue; // Happens if player still in team choice menu
			
			// Relaunch if clonk does not stand.
			if (clonk->GetAction() != "Walk")
			{
				clonk->Kill();
				clonk = GetCrew(player);
			}

			clonk->SetCrewEnabled(true);
			SelectCrew(player, clonk, true);

			// Make sure all clonks start with equal health
			clonk->Extinguish();
			ResetHealth(clonk);
		}
		
		gameStarted = true;
	}
	else
	{
		Message("@<c ffff00>%d</c>|%s", 0, countdown, gameStartMessage);
		Schedule("GameCall(\"ShowCountdown\")", 38);
	}
	
	--countdown;
}

func LobbyActive() { return !section; }

global func GetActiveTeamCount()
{
	var teams = [];
	for(var i = 0; i < GetPlayerCount(); i++)
	{
		if(!eliminatedPlayers[GetPlayerID(GetPlayerByIndex(i))])
		{
			++teams[GetPlayerTeam(GetPlayerByIndex(i))];
		}
	}
	
	teams[-1] = 0;
	var count = 0;
	for(var teamCount in teams)
	{
		if(teamCount > 0)
		{
			++count;
		}
	}
	return count;
}
 
global func EliminatePlayer(int iPlr, bool fQuiet)
{
	var ret = _inherited(iPlr, fQuiet);
	eliminatedPlayers[GetPlayerID(iPlr)] = true;

	// Check if the game is over
	CheckGameOver();
	return ret;
}

global func CheckGameOver()
{
	if (GetActiveTeamCount() <= 1) StartGameOverEffect();
}

func HandleKill(int killed, int killer)
{
	// Check if the game is over
	if (GetEffectCount("GameOver")) return 0;
	
	// Assume suicide if killer cannot be determined
	if (killer == NO_OWNER) killer = killed;

	var killedEliminated = false;
	var killedID = GetPlayerID(killed), killerID = GetPlayerID(killer);
	var killedTeam = GetPlayerTeam(killed), killerTeam = GetPlayerTeam(killer);
	var teamKill = killedTeam != 0 && killedTeam == killerTeam;
	
	++playerDeaths[killedID];
	
	// Update kill score
	if (!teamKill)
	{
		++playerScore[killerID];
		if (killerTeam) ++teamScore[killerTeam];
	}
	else if (teamKill && killed != killer) // Decrement score if it's a team kill but not a suicide
	{
		if (playerScore[killerID] > 0) // Prevent negative scores
		{
			--playerScore[killerID];
			if (killerTeam) --teamScore[killerTeam];
		}
	}

	// Show relaunch message or eliminate player if no relaunches left
	var relaunchesLeft;
	if (!deathmatchEnabled)
	{
		relaunchesLeft = numRelaunches - playerDeaths[killedID];
		if (relaunchesLeft < 0)
		{
			EliminatePlayer(killed);
			killedEliminated = true;
		}
		else if (relaunchesLeft == 0)
		{
			PlayerMessage(killed, "$MsgLastRelaunch$");
		}
		else if (relaunchesLeft == 1)
		{
			PlayerMessage(killed, "$MsgOneRelaunch$");
		}
		else // More than one relaunch left
		{
			PlayerMessage(killed, "$MsgRelaunch$", 0, relaunchesLeft);
		}
	}

	// Check for deathmatch winner
	if (deathmatchEnabled)
	{
		// Teams enabled?
		if (killerTeam)
		{
			// Winner?
			if (teamScore[killerTeam] >= deathmatchWinScore)
			{
				// Eliminate all players of losing teams
				for (var player in GetPlayers())
				{
					if (GetPlayerTeam(player) != killerTeam) EliminatePlayer(player);
				}
				Message(Format("$MsgDeathmatchWin$", GetTeamColor(killerTeam), GetTeamName(killerTeam)));
				gameOver = true;
				killedEliminated = true;
			}
		}
		else // No teams?
		{
			// Winner?
			if (playerScore[killerID] >= deathmatchWinScore)
			{
				// Eliminate all losing players
				for (var player in GetPlayers())
				{
					if (player != killer) EliminatePlayer(player);
				}
				gameOver = true;
				killedEliminated = true;
			}
		}
	}
	
	UpdateScoreboard(killed);
	UpdateScoreboard(killer);
	
	return killedEliminated;
}

func OnGoalsFulfilled()
{
	// Safety only, GameOver-Effect should have already started
	CheckGameOver();
	return 1;
}

global func StartGameOverEffect()
{
	if (!GetEffect("GameOver")) AddEffect("GameOver", 0, 1, 1);
}

global func FxGameOverStart(object pTarget, int iEffectNumber)
{
	EffectVar(0, pTarget, iEffectNumber) = ambienceSounds;
}

global func FxGameOverTimer(object pTarget, int iEffectNumber, int iEffectTime)
{
	var sounds = EffectVar(0, pTarget, iEffectNumber);
	if (iEffectTime <= 100)
	{
		for(var sound in sounds)
		{
			SoundLevel(sound[0], sound[1]*(100 - iEffectTime)/100);
			for(var i = 0; i < GetPlayerCount(); ++i)
			{
				var player = GetPlayerByIndex(i);
				if (!WantsAmbienceSounds(player)) Sound(sound[0], true, 0, sound[1], player + 1, -1);
			}
		}
	}
	else if((iEffectTime > 200) || (iEffectTime > 100 && !ambienceEnabled))
	{
		return -1;
	}
}

global func FxGameOverStop(object pTarget, int iEffectNumber)
{
	Sound("Trumpet", 1);
	GameOver();
	RemoveAll(MELE);
}

func GetPlayers()
{
	var players = CreateArray(GetPlayerCount());
	for (var i = 0; i < GetPlayerCount(); ++i)
	{
		players[i] = GetPlayerByIndex(i);
	}
	return players;
}

func OnClonkDeath(object clonk, int killedBy)
{
	if (loadingSection) return;

	var player = clonk->GetOwner();

	// Do nothing if Clonk does not belong to a player
	if (GetPlayerID(player) == 0) return;

	// Handle kill. Do not relaunch if player got eliminated
	if (gameStarted && !gameOver && HandleKill(player, killedBy)) return;

	// Relaunch
	if (GetPlayerID(player)) LaunchClonk(player, clonk, true);
}

func LaunchClonk(int player, object clonk, bool relaunch)
{
	if (!clonk || relaunch)
	{
		var newClonk = CreateObject(CLNK, 0, 0, player);
		if (clonk)
		{
			newClonk->GrabObjectInfo(clonk);
		}
		else
		{
			MakeCrewMember(newClonk, player);
		}
		clonk = newClonk;
	}
	ResetHealth(clonk);
	SelectCrew(player, clonk, true);

	// Move clonk to random position

	var maxDistance = Distance(0, 0, LandscapeWidth(), LandscapeHeight());
	var bestPosition = [LandscapeWidth() / 2, LandscapeHeight() / 2], bestQuality = 0;

	// Generate 25 random positions and choose best
	for (var i = 0; i < 25; ++i)
	{
		// Place wipf, save its position and remove it
		var wipf = PlaceAnimal(WIPF);
		if (!wipf) continue;
		var pos = [wipf->GetX(), wipf->GetY()];
		wipf->RemoveObject();

		// Get distance to closest enemy
		var closestEnemy = FindObject2AllLayers(Find_OCF(OCF_CrewMember | OCF_Alive), Find_Hostile(player), Sort_Distance(pos[0], pos[1]));
		var enemyDistance;
		if (closestEnemy) enemyDistance = Distance(pos[0], pos[1], closestEnemy->GetX(), closestEnemy->GetY());

		// Calculate quality of position from its y-value and its distance to the closest enemy and use position if it is the best
		var quality = (LandscapeHeight() - pos[1]) * 1000 / LandscapeHeight() + enemyDistance * 1000 / maxDistance;
		if (quality > bestQuality)
		{
			bestPosition = pos;
			bestQuality = quality;
		}
	}

	clonk->SetPosition(bestPosition[0], bestPosition[1]);
	clonk->SetDir(bestPosition[0] < LandscapeWidth()/2);
	
	// Still in countdown?
	if (!LobbyActive() && !gameStarted)
	{
		clonk->SetCrewEnabled(false);
	}
	
	// No corpses in apocalypse mode
	if (mode->~NoCorpses()) clonk->LocalN("removeOnDeath") = true;
	
	// Enable rotation in jump for the clonk if allowed by rule
	if (FindObject(RIJP)) clonk->LocalN("rotateInJump") = true;
	
	// Do not immediately pass player control to the new clonk to prevent accidental jumps
	if (relaunch)
	{
		clonk->SetCrewEnabled(false);
		clonk->SetCrewEnabled(true);
		clonk->Schedule("SelectCrew(GetOwner(), this, true)", 20);
		clonk->SetObjectLayer(clonk);
		clonk->Schedule("SetObjectLayer(0)", 50);
	}
	
	// Respawn effects
	PlayerMessage(player, "{{SREL}}", clonk);
	DrawParticleLine("PSpark", GetX(clonk), 0, GetX(clonk), GetY(clonk), 10, 150, RGBa(Random(255), Random(255), Random(255),50), RGBa(Random(255), Random(255), Random(255),50), 0);
	DrawParticleLine("PSpark", GetX(clonk) + RandomX(5, 60), 0, GetX(clonk), GetY(clonk), 10, 150, RGBa(Random(255), Random(255), Random(255),50), RGBa(Random(255), Random(255), Random(255),50), 0);
	DrawParticleLine("PSpark", GetX(clonk) - RandomX(5, 60), 0, GetX(clonk), GetY(clonk), 10, 150, RGBa(Random(255), Random(255), Random(255),50), RGBa(Random(255), Random(255), Random(255),50), 0);
	Sound("PlayerJoin", 0, clonk, 100);
	CastParticles("MSpark", 50, 20, GetX(clonk), GetY(clonk), 50, 75, RGBa(128,128,255,0), RGBa(255,255,255,127));
	
	SetPlrView(player, clonk);
	ResetHealth(clonk);
}

func ResetHealth(object clonk)
{
	if (suddendeathEnabled)
	{
		clonk->DoEnergy(1 - clonk->GetEnergy());
	}
	else
	{
		clonk->DoEnergy(100);
	}
}

func CheckGameStatus()
{
	if (GetTeamCount() == 0)
	{
		var winner = NO_OWNER;

		// Check if a player has reached the kill limit
		for (var i = 0; i < GetPlayerCount(); ++i)
		{
			var plr = GetPlayerByIndex(i);
			if (playerScore[plr] >= deathmatchWinScore)
			{
				winner = plr;
				break;
			}
		}

		// Eliminate other players if there is a winner
		for (var i = 0; i < GetPlayerCount(); ++i)
		{
			var plr = GetPlayerByIndex(i);
			if (plr != winner) EliminatePlayer(plr);
		}
	}
	else
	{
		var winnerTeam = 0;

		// Clear team score array
		teamScore = CreateArray(GetTeamCount());

		// Calculate team score and check if kill limit is reached
		for (var i = 0; i < GetPlayerCount(); ++i)
		{
			var plr = GetPlayerByIndex(i), team = GetPlayerTeam(plr);
			teamScore[team] += playerScore[plr];
			if (teamScore >= deathmatchWinScore)
			{
				winnerTeam = team;
				break;
			}
		}

		// Do we have a winner?
		if (winnerTeam != 0)
		{
			for (var i = 0; i < GetPlayerCount(); ++i)
			{
				var plr = GetPlayerByIndex(i);
				if (GetPlayerTeam(plr) != winnerTeam) EliminatePlayer(plr);
			}
		}
	}
}

global func WantsAmbienceSounds(int player)
{
	// Check if user already specified in the past if he wants to enable ambience sounds
	var preference = GetPlrExtraData(player, PlrData_EnableAmbienceSounds);
	if (preference == PlrData_EnableAmbienceSounds_Yes) return true;
	if (preference == PlrData_EnableAmbienceSounds_No) return false;
	// Preference not set yet/invalid? Enable for non-league games and disable otherwise.
	return !GetLeague();
}

func DoAmbienceSounds(int player)
{
	for (var sound in ambienceSounds)
	{
		Sound(sound[0], true, 0, sound[1], player + 1, WantsAmbienceSounds(player) * 2 - 1);
	}
}

func ToggleAmbienceSounds(int player)
{
	var preference;
	if (WantsAmbienceSounds(player))
	{
		preference = PlrData_EnableAmbienceSounds_No;
	}
	else
	{
		preference = PlrData_EnableAmbienceSounds_Yes;
	}

	SetPlrExtraData(player, PlrData_EnableAmbienceSounds, preference);
	DoAmbienceSounds(player);
}

func UpdateComment(bool inLobby)
{
	if (inLobby) SetGameComment(" $LobbyComment$");
	else
	{
		var score = "";
		var teams = [];
		var teamRelaunches = [];
		for (var i = 0; i < GetPlayerCount(); i++)
		{
			if (!eliminatedPlayers[GetPlayerID(GetPlayerByIndex(i))])
			{
				++teams[GetPlayerTeam(GetPlayerByIndex(i))];
				if (!deathmatchEnabled) teamRelaunches[GetPlayerTeam(GetPlayerByIndex(i))] += numRelaunches - playerDeaths[GetPlayerID(GetPlayerByIndex(i))];
			}
		}

		for (var i = 0; i <= GetTeamCount(); ++i)
		{
			var team = GetTeamByIndex(i);
			if (teams[team])
			{
				if (GetLength(score)) score = Format("%s : ", score);
				if (deathmatchEnabled) score = Format("%s<c %x>%d</c>", score, GetTeamColor(team), teamScore[team]);
				else score = Format("%s<c %x>%d</c>", score, GetTeamColor(team), teamRelaunches[team]);
			}
		}

		var sudden = "";
		if(suddendeathEnabled) sudden = " $SuddenDeath$";
		var goalDesc;
		if(deathmatchEnabled) goalDesc = Format("$DM$", deathmatchWinScore);
		else goalDesc = Format("$LMS$", numRelaunches);

		SetGameComment(Format(" $GameComment$", GetName(0, sectionID), mode->ModeName(), sudden, goalDesc, score));
	}
}
