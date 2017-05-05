/*-- Setup Menu --*/

#strict 2

static const
	SETTING_Deathmatch = 0, SETTING_SuddenDeath = 1, SETTING_RotateInJump = 2,
	SETTING_RelaunchesInc = 3, SETTING_RelaunchesDec = 4,
	SETTING_DeathmatchScoreInc = 5, SETTING_DeathmatchScoreDec = 6,
	SETTING_Ambience = 7;

local Sections, Modes;
local clonk, setupPlayer;

// Selected values
local section, mode;
local selectRandomSection, selectRandomMode;
local suddendeathEnabled, rotateInJumpEnabled;
local ambienceEnabled;
local numRelaunches;
local deathmatchEnabled, deathmatchWinScore;

protected func Initialize()
{
	Sections = [];
	for (var i = 0, def; def = GetDefinition(i, C4D_StaticBack); ++i)
	{
		if (DefinitionCall(def, "SectionName")) Sections[GetLength(Sections)] = def;
	}
	section = Sections[0];

	Modes = [];
	for (var i = 0, def; def = GetDefinition(i, C4D_StaticBack); ++i)
	{
		if (DefinitionCall(def, "ModeName")) Modes[GetLength(Modes)] = def;
	}
	mode = Modes[0];
}

private func ShowSetup()
{
	ShowMessage();
	ShowSectionMenu();
}

private func ShowSectionMenu()
{
	CreateMenu(GetID(), clonk, 0, C4MN_Extra_None, 0, 0, C4MN_Style_Context);

	for (var i = 0; i < GetLength(Sections); ++i)
	{
		clonk->AddMenuItem(GetName(0, Sections[i]), Format("SelectSection(%i)", Sections[i]), Sections[i]);
		CheckPreselect(!selectRandomSection && Sections[i] == section, i);
	}

	clonk->AddMenuItem("$Random$", "SelectRandomSection()", SRND);
	CheckPreselect(selectRandomSection, GetLength(Sections));
}

private func SelectSection(id selectedSection)
{
	selectRandomSection = false;
	section = selectedSection;
	SectionSelectionDone();
}

private func SelectRandomSection()
{
	selectRandomSection = true;
	SectionSelectionDone();
}

private func SectionSelectionDone()
{
	ShowMessage();
	ShowModeMenu();
}

private func ShowModeMenu()
{
	CreateMenu(GetID(), clonk, 0, C4MN_Extra_None, 0, 0, C4MN_Style_Context);

	var menuItemIndex = 0;
	for (var m in Modes)
	{
		clonk->AddMenuItem(m->ModeName(), Format("SelectMode(%i)", m), m);
		CheckPreselect(!selectRandomMode && m == mode, menuItemIndex++);
	}

	clonk->AddMenuItem("$Random$", "SelectRandomMode()", SRND);
	CheckPreselect(selectRandomMode, menuItemIndex++);
	clonk->AddMenuItem("$Back$", "ShowSectionMenu()", SBCK);
}

private func SelectMode(id selectedMode)
{
	selectRandomMode = false;
	mode = selectedMode;
	ModeSelectionDone();
}

private func SelectRandomMode()
{
	selectRandomMode = true;
	ModeSelectionDone();
}

private func ModeSelectionDone()
{
	ShowMessage();
	ShowSettingsMenu();
}

private func ShowSettingsMenu(bool preselect, int selectedSetting)
{
	CreateMenu(GetID(), clonk, 0, C4MN_Extra_None, 0, 0, C4MN_Style_Context);

	var menuItemIndex = 0;

	// Deathmatch entry
	AddOptionMenuItem(GetName(0, DTHM), deathmatchEnabled, "SelectSetting(SETTING_Deathmatch)", DTHM);
	CheckPreselect(preselect && selectedSetting == SETTING_Deathmatch, menuItemIndex++);
	
	// Sudden Death entry
	AddOptionMenuItem(GetName(0, SDDT), suddendeathEnabled, "SelectSetting(SETTING_SuddenDeath)", SDDT);
	CheckPreselect(preselect && selectedSetting == SETTING_SuddenDeath, menuItemIndex++);
	
	// "Turn in jump" entry
	AddOptionMenuItem(GetName(0, RIJP), rotateInJumpEnabled, "SelectSetting(SETTING_RotateInJump)", RIJP);
	CheckPreselect(preselect && selectedSetting == SETTING_RotateInJump, menuItemIndex++);
	
	// Ambience entry
	AddOptionMenuItem("$Ambience$", ambienceEnabled, "SelectSetting(SETTING_Ambience)", SABC);
	CheckPreselect(preselect && selectedSetting == SETTING_Ambience, menuItemIndex++);

	if (!deathmatchEnabled)
	{
		clonk->AddMenuItem("$Relaunches$ +", "SelectSetting(SETTING_RelaunchesInc)", SREL);
		CheckPreselect(preselect && selectedSetting == SETTING_RelaunchesInc, menuItemIndex++);
		clonk->AddMenuItem("$Relaunches$ -", "SelectSetting(SETTING_RelaunchesDec)", SREL);
		CheckPreselect(preselect && selectedSetting == SETTING_RelaunchesDec, menuItemIndex++);
	}
	else
	{
		clonk->AddMenuItem("$Kills$ +", "SelectSetting(SETTING_DeathmatchScoreInc)", SKIL);
		CheckPreselect(preselect && selectedSetting == SETTING_DeathmatchScoreInc, menuItemIndex++);
		clonk->AddMenuItem("$Kills$ -", "SelectSetting(SETTING_DeathmatchScoreDec)", SKIL);
		CheckPreselect(preselect && selectedSetting == SETTING_DeathmatchScoreDec, menuItemIndex++);
	}

	clonk->AddMenuItem("$Done$", "SetupDone()", SDNE);
	CheckPreselect(!preselect, menuItemIndex++);
	clonk->AddMenuItem("$Back$", "ShowModeMenu()", SBCK);
}

private func SelectSetting(int selectedSetting)
{
	if (selectedSetting == SETTING_Deathmatch)
	{
		deathmatchEnabled = !deathmatchEnabled;
	}
	else if (selectedSetting == SETTING_SuddenDeath)
	{
		suddendeathEnabled = !suddendeathEnabled;
	}
	else if (selectedSetting == SETTING_RotateInJump)
	{
		rotateInJumpEnabled = !rotateInJumpEnabled;
	}
	else if (selectedSetting == SETTING_Ambience)
	{
		ambienceEnabled = !ambienceEnabled;
	}
	else if (selectedSetting == SETTING_RelaunchesInc)
	{
		numRelaunches = Min(numRelaunches + 1, 10);
	}
	else if (selectedSetting == SETTING_RelaunchesDec)
	{
		numRelaunches = Max(numRelaunches - 1, 3);
	}
	else if (selectedSetting == SETTING_DeathmatchScoreInc)
	{
		deathmatchWinScore = Min(deathmatchWinScore + 1, 30);
	}
	else if (selectedSetting == SETTING_DeathmatchScoreDec)
	{
		deathmatchWinScore = Max(deathmatchWinScore - 1, 10);
	}

	ShowMessage();

	ShowSettingsMenu(true, selectedSetting);
}

private func SetupDone()
{
	// Apply random selection
	if (selectRandomSection) section = Sections[Random(GetLength(Sections))];
	if (selectRandomMode) mode = Modes[Random(GetLength(Modes))];
	selectRandomSection = selectRandomMode = false;
	// Show final setup message and start the game
	ShowMessage();
	GameCall("SetupDone", this, GetMessage());
}

private func AddOptionMenuItem(string caption, bool enabled, string command, id idItem)
{
	clonk->AddMenuItem(IIf(enabled, caption, Format("<c a0a0a0>%s</c>", caption)), command, idItem);
}

private func CheckPreselect(bool preselect, int menuItemIndex)
{
	if (preselect) clonk->SelectMenuItem(menuItemIndex);
}

private func KeepMenuOpen()
{
	// Find new player?
	if (!GetPlayerID(setupPlayer))
	{
		clonk = 0;
		if (GetPlayerCount() == 0) return;
		setupPlayer = GetPlayerByIndex(0);
	}

	// Find clonk
	if (!clonk || !clonk->GetAlive()) clonk = GetCrew(setupPlayer);

	// (Re)open menu
	if (clonk && !clonk->GetMenu()) ShowSetup();
}

private func ShowMessage()
{
	var message = Format("@%s", GetMessage());
	CustomMessage(message, this, setupPlayer, -LandscapeWidth() / 5, 0, 0, 0, 0, MSG_NoLinebreak);
	for (var i = 0; i < GetPlayerCount(); ++i)
	{
		if (GetPlayerByIndex(i) == setupPlayer) continue;
		CustomMessage(message, this, GetPlayerByIndex(i), 0, 0, 0, 0, 0, MSG_NoLinebreak | MSG_Multiple);
	}
}

private func GetMessage()
{
	var msgSection;
	if (selectRandomSection)
	{
		msgSection = "$Landscape$: {{SRND}} $Random$";
	}
	else
	{
		msgSection = Format("$Landscape$: {{%i}} %s", section, GetName(0, section));
	}

	var msgMode;
	if (selectRandomMode)
	{
		msgMode = Format("$Mode$: {{SRND}} $Random$");
	}
	else
	{
		msgMode = Format("$Mode$: {{%i}} %s", mode, mode->ModeName());
	}

	var msgWinScore;
	if (!deathmatchEnabled)
	{
		msgWinScore = Format("{{SREL}} $Relaunches$: %d", numRelaunches);
	}
	else
	{
		msgWinScore = Format("{{SKIL}} %s: %d $Kills$", GetName(0, DTHM), deathmatchWinScore);
	}

	var msgSuddenDeath = Format("{{SDDT}} %s: %s", GetName(0, SDDT), IIf(suddendeathEnabled, "$Enabled$", "$Disabled$"));
	var msgRotateInJump = Format("{{RIJP}} %s: %s", GetName(0, RIJP), IIf(rotateInJumpEnabled, "$Enabled$", "$Disabled$"));
	var msgAmbience = Format("{{SABC}} $Ambience$: %s", IIf(ambienceEnabled, "$Enabled$", "$Disabled$"));

	return Format("%s|%s|%s|%s|%s|%s", msgSection, msgMode, msgWinScore, msgSuddenDeath, msgRotateInJump, msgAmbience);
}
