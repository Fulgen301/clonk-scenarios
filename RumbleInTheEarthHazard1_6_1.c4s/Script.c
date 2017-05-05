#strict

static bunker1;
static bunker2;
static bunker3;
static bunker4;
static bunker5;
static bunker6;
static bunker7;
static bunker8;
static bunker9;

static casualties;

// Team ID 1 -> Blau
// Team ID 2 -> Rot

func Initialize() 
{
  bunker1 = CreateObject(CB5B, 556, 673);
  bunker2 = CreateObject(CB5B, 104, 889);
  bunker3 = CreateObject(CB5B, 237, 1465);
  bunker4 = CreateObject(CB5B, 1036, 695);
  bunker5 = CreateObject(CB5B, 973, 993);
  bunker6 = CreateObject(CB5B, 953, 1313);
  bunker7 = CreateObject(CB5B, 1808, 665);
  bunker8 = CreateObject(CB5B, 2296, 840);
  bunker9 = CreateObject(CB5B, 2070, 1282);

  CreateObject(FP5B, 596, 673, GetPlayerByTeam(1));
  CreateObject(FP5B, 154, 889, GetPlayerByTeam(1));
  CreateObject(FP5B, 287, 1465, GetPlayerByTeam(1));
  CreateObject(FP5B, 1086, 707, GetPlayerByTeam(1));
  CreateObject(FP5B, 1023, 993, -1);
  CreateObject(FP5B, 999, 1313, GetPlayerByTeam(2));
  CreateObject(FP5B, 1858, 665, GetPlayerByTeam(2));
  CreateObject(FP5B, 2246, 840, GetPlayerByTeam(2));
  CreateObject(FP5B, 2120, 1282, GetPlayerByTeam(2));

  SetName("North-West Bunker"  , bunker1);
  SetName("Middle-West Bunker" , bunker2);
  SetName("South-West Bunker"  , bunker3);
  SetName("North-Middle Bunker", bunker4);
  SetName("Main Bunker"        , bunker5);
  SetName("South-Middle Bunker", bunker6);
  SetName("North-East Bunker"  , bunker7);
  SetName("Middle-East Bunker" , bunker8);
  SetName("South-East Bunker"  , bunker9);

  for (var flagPole in FindObjects(Find_ID(FP5B)))
  {
    var color = RGB(255, 255, 255);

    if (ObjectDistance(flagPole, bunker1) < 100) color = GetTeamColor(1);
    if (ObjectDistance(flagPole, bunker2) < 100) color = GetTeamColor(1);
    if (ObjectDistance(flagPole, bunker3) < 100) color = GetTeamColor(1);
    if (ObjectDistance(flagPole, bunker4) < 100) color = GetTeamColor(1);
    if (ObjectDistance(flagPole, bunker5) < 100) color = RGB(255,255,255);
    if (ObjectDistance(flagPole, bunker6) < 100) color = GetTeamColor(2);
    if (ObjectDistance(flagPole, bunker7) < 100) color = GetTeamColor(2);
    if (ObjectDistance(flagPole, bunker8) < 100) color = GetTeamColor(2);
    if (ObjectDistance(flagPole, bunker9) < 100) color = GetTeamColor(2);
    
    flagPole -> CreateFlag(color);
  }
  InitializeScoreboard();
  ScriptGo(1);
}
func Script1() { SetMaxPlayer(); }


func InitializeScoreboard()
{
  casualties = [0, 0];

  SetScoreboardData(SBRD_Caption, SBRD_Caption, "Score");  

  SetScoreboardData(1, SBRD_Caption, Format("<c ff0000>%s</c>", GetTeamName(1)));
  SetScoreboardData(2, SBRD_Caption, Format("<c 0000ff>%s</c>", GetTeamName(2)));

  SetScoreboardData(SBRD_Caption, 1, "{{BK5B}}");
  SetScoreboardData(SBRD_Caption, 2, "{{SY5B}}");

  SetScoreboardData(1, 1, "1");
  SetScoreboardData(2, 1, "1");

  SetScoreboardData(1, 2, "0");
  SetScoreboardData(2, 2, "0");
}

func InitializePlayer(player)
{
  SetOwner(GetPlayerByTeam(1), bunker1);
  SetOwner(GetPlayerByTeam(1), bunker2);
  SetOwner(GetPlayerByTeam(1), bunker3);
  SetOwner(GetPlayerByTeam(1), bunker4);
  SetOwner(-1, bunker5);
  SetOwner(GetPlayerByTeam(2), bunker6);
  SetOwner(GetPlayerByTeam(2), bunker7);
  SetOwner(GetPlayerByTeam(2), bunker8);
  SetOwner(GetPlayerByTeam(2), bunker9);

  DoScoreboardShow(1, player + 1);

  var clonk = GetCrew(player);
  InitializeClonk(clonk);
}


func InitializeClonk(clonk, homeCount)
{ 
  var sanctuary = CreateObject(SY5B, GetX(bunker5), GetY(bunker5), NO_OWNER);
  Enter(sanctuary, clonk);

  CreateMenu(SY5B, clonk, 0, 0, "R.I.P", 0, C4MN_Style_Info);

  LocalN("homeCount", sanctuary) = homeCount;
  sanctuary -> SetAction("Countdown", clonk);
}

func ChooseGear(ID,clonk)
{
  CreateMenu(HZCK, clonk, 0, 0, "Wähle deine erste Waffe", 0, C4MN_Style_Context);
  
  AddMenuItem("Bazooka", "Bazooka", BZWP, clonk, 0, clonk);
  AddMenuItem("Kettensäge", "Kettensage", MEZL, clonk, 0, clonk);
  AddMenuItem("Energiegewehr", "Energieg", ENWP, clonk, 0, clonk);
  AddMenuItem("Flammenwerfer", "Flammenw", FTWP, clonk, 0, clonk);
  AddMenuItem("Granatenwerfer", "Granatenw", GLWP, clonk, 0, clonk);
  AddMenuItem("Minigun", "Minigun", MIWP, clonk, 0, clonk);
  AddMenuItem("Partikelkanone", "Partikelk", GGWP, clonk, 0, clonk);
  AddMenuItem("Pumpgun", "Pumpgun", PGWP, clonk, 0, clonk);
}

func ChooseClonk(clonk)
{
  CloseMenu(clonk); // Relaunch-Countdown-Menü schliessen
  CreateMenu(CLNK, clonk, 0, 0, "Wähle deinen Clonk", 0, C4MN_Style_Context);
  AddMenuItem("Hazard", "ChooseGear", HZCK, clonk, 0, clonk);
  AddMenuItem("SFT", "SFT", SF5B, clonk, 0, clonk);
}

func ChooseGearSFT(clonk)
{
  CreateMenu(SF5B, clonk, 0, 0, "Wähle deine erste Waffe", 0, C4MN_Style_Context);
  
  AddMenuItem("Assault Rifle", "Weapon", AR5B, clonk, 0, clonk);
  AddMenuItem("Flammenwerfer", "Weapon", FT5B, clonk, 0, clonk);
  AddMenuItem("Raketenwerfer", "Weapon", RL5B, clonk, 0, clonk);
  AddMenuItem("Schrotflinte", "Weapon", SG5B, clonk, 0, clonk);
  AddMenuItem("Uzi", "Weapon", UZ5B, clonk, 0, clonk);
}

func Choose2ndWeapon(clonk)
{
  CreateMenu(SF5B, clonk, 0, 0, "Wähle deine zweite Waffe", 0, C4MN_Style_Context);
  
  AddMenuItem("Assault Rifle", "Weapon2", AR5B, clonk, 0, clonk);
  AddMenuItem("Flammenwerfer", "Weapon2", FT5B, clonk, 0, clonk);
  AddMenuItem("Raketenwerfer", "Weapon2", RL5B, clonk, 0, clonk);
  AddMenuItem("Schrotflinte", "Weapon2", SG5B, clonk, 0, clonk);
  AddMenuItem("Uzi", "Weapon2", UZ5B, clonk, 0, clonk);
}

func ChooseSFTEquipment(clonk)
{
  CreateMenu(SF5B, clonk, 0, 0, "Wähle deine Ausrüstung", 0, C4MN_Style_Context);
  
  AddMenuItem("GPED", "Equipment", GP5B, clonk, 0, clonk);
  AddMenuItem("Harpune", "Equipment", HP5B, clonk, 0, clonk);
  AddMenuItem("Jetpack", "Equipment", JP5B, clonk, 0, clonk);
  CreateContents(NH5B,clonk);
}

func ChooseSFTEquipment2(clonk)
{
  CreateMenu(SF5B, clonk, 0, 0, "Wähle deine Ausrüstung", 0, C4MN_Style_Context);
  
  AddMenuItem("Bauequipment", "Conkit", CNKT, clonk, 0, clonk);
  AddMenuItem("Geschützbausatz", "Conkit2", CNK2, clonk, 0, clonk);
  AddMenuItem("5x Feuerstein", "Flint", FLNT, clonk, 0, clonk);
  AddMenuItem("4x Superflint", "SFlint", SFLN, clonk, 0, clonk);
  AddMenuItem("3x Teraflint", "EFlint", EFLN, clonk, 0, clonk);
  AddMenuItem("3x Omniblaster", "OBlaster", OB5B, clonk, 0, clonk);
  CreateContents(NH5B,clonk);
}

func OBlaster(id icon, clonk)
{
    CreateContents(OB5B,clonk,3);
    ChooseBunker(clonk);
}

func Equipment(id icon, clonk)
{
   var Equipment = CreateContents(icon,clonk);
   if(icon == HP5B)
   LocalN("qGrenades", Equipment) = 100;
   if(icon == JP5B)
   LocalN("ammo", Equipment) = 100;
   ChooseSFTEquipment2(clonk);
}

func Weapon(id icon, clonk)
{
  var Weapon = CreateContents(icon, clonk);
  if(icon == RL5B)
  Weapon -> CreateContents(MS5B);
  LocalN("ammo", Weapon) = 100;
  if(icon == AR5B)
  LocalN("qGrenades", Weapon) = 100;

  Choose2ndWeapon(clonk);
}

func Weapon2(id icon, clonk)
{
  var Weapon = CreateContents(icon, clonk);
  if(icon == RL5B)
  Weapon -> CreateContents(MS5B);
  LocalN("ammo", Weapon) = 100;
  if(icon == AR5B)
  LocalN("qGrenades", Weapon) = 100;

  ChooseSFTEquipment(clonk);
}

func Bazooka(icon, clonk)
{
  var tmp = CreateContents(BZWP, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));
  ChooseWeapon(clonk);
}

func SFT(icon, clonk)
{
  ChangeDef(SF5B,clonk);
  clonk->Initialize();
  ChooseGearSFT(clonk);
}

func Kettensage(icon, clonk)
{
  var tmp = CreateContents(MEZL, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));    
  ChooseWeapon(clonk);
}

func Energieg(icon, clonk)
{
   
  var tmp = CreateContents(ENWP, clonk);  
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));
  ChooseWeapon(clonk);
}

func Flammenw(icon, clonk)
{
  var tmp = CreateContents(FTWP, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));  
  ChooseWeapon(clonk);
}

func Granatenw(icon, clonk)
{
  var tmp = CreateContents(GLWP, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));  
  ChooseWeapon(clonk);
}

func Drohne(icon, clonk)
{
   CreateContents(DRSU, clonk);
  
  ChooseGear3(clonk);
}

func Drohne2(icon, clonk)
{
   CreateContents(DRSU, clonk);
  
  ChooseGear4(clonk);
}

func Minigun(icon, clonk)
{
  var tmp = CreateContents(MIWP, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));  
  ChooseWeapon(clonk);
}

func Partikelk(icon, clonk)
{
  var tmp = CreateContents(GGWP, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));  
  ChooseWeapon(clonk);
}

func Pumpgun(icon, clonk)
{
  var tmp = CreateContents(PGWP, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));  
  ChooseWeapon(clonk);
}

func ChooseWeapon(clonk)
{
  CloseMenu(clonk); // Relaunch-Countdown-Menü schliessen
  CreateMenu(HZCK, clonk, 0, 0, "Wähle deine zweite Waffe", 0, C4MN_Style_Context);
  
  AddMenuItem("Bazooka", "Bazooka2", BZWP, clonk, 0, clonk);
  AddMenuItem("Kettensäge", "Kettensage2", MEZL, clonk, 0, clonk);
  AddMenuItem("Energiegewehr", "Energieg2", ENWP, clonk, 0, clonk);
  AddMenuItem("Flammenwerfer", "Flammenw2", FTWP, clonk, 0, clonk);
  AddMenuItem("Granatenwerfer", "Granatenw2", GLWP, clonk, 0, clonk);
  AddMenuItem("Minigun", "Minigun2", MIWP, clonk, 0, clonk);
  AddMenuItem("Partikelkanone", "Partikelk2", GGWP, clonk, 0, clonk);
  AddMenuItem("Pumpgun", "Pumpgun2", PGWP, clonk, 0, clonk);
}

func Bazooka2(icon, clonk)
{
  var tmp = CreateContents(BZWP, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad)); 
  ChooseUpgrade(clonk);
}

func Kettensage2(icon, clonk)
{
  var tmp = CreateContents(MEZL, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));    
  ChooseUpgrade(clonk);
}

func Energieg2(icon, clonk)
{
   
  var tmp = CreateContents(ENWP, clonk);  
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));
  ChooseUpgrade(clonk);
}

func Flammenw2(icon, clonk)
{
  var tmp = CreateContents(FTWP, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));  
  ChooseUpgrade(clonk);
}

func Granatenw2(icon, clonk)
{
  var tmp = CreateContents(GLWP, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));  
  ChooseUpgrade(clonk);
}

func Minigun2(icon, clonk)
{
  var tmp = CreateContents(MIWP, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));  
  ChooseUpgrade(clonk);
}

func Partikelk2(icon, clonk)
{
  var tmp = CreateContents(GGWP, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad)); 
  ChooseUpgrade(clonk);
}

func Pumpgun2(icon, clonk)
{
  var tmp = CreateContents(PGWP, clonk);
  tmp->DoAmmo(tmp->GetFMData(FM_AmmoID), tmp->GetFMData(FM_AmmoLoad));  
  ChooseUpgrade(clonk);
}

func ChooseUpgrade(clonk)
{
  CloseMenu(clonk); // Relaunch-Countdown-Menü schliessen
  CreateMenu(HZCK, clonk, 0, 0, "Wähle ein Waffenupgrade", 0, C4MN_Style_Context);
  
  AddMenuItem("Laser", "Laser", KLAS, clonk, 0, clonk);
  AddMenuItem("Bioaufsatz", "Bioaufs", KSLM, clonk, 0, clonk);
  AddMenuItem("Waffenteil", "Waffent", KRFL, clonk, 0, clonk);
}

func Laser(icon, clonk)
{
   CreateContents(KLAS, clonk);
  
  ChooseUpgrade2(clonk);
}

func Bioaufs(icon, clonk)
{
   CreateContents(KSLM, clonk);
  
  ChooseUpgrade2(clonk);
}

func Waffent(icon, clonk)
{
   CreateContents(KRFL, clonk);
  
  ChooseUpgrade2(clonk);
}

func ChooseUpgrade2(clonk)
{
  CloseMenu(clonk); // Relaunch-Countdown-Menü schliessen
  CreateMenu(HZCK, clonk, 0, 0, "Wähle ein Waffenupgrade", 0, C4MN_Style_Context);
  
  AddMenuItem("Laser", "Laser2", KLAS, clonk, 0, clonk);
  AddMenuItem("Bioaufsatz", "Bioaufs2", KSLM, clonk, 0, clonk);
  AddMenuItem("Waffenteil", "Waffent2", KRFL, clonk, 0, clonk);
}

func Laser2(icon, clonk)
{
   CreateContents(KLAS, clonk);
  
  ChooseGear2(clonk);
}

func Bioaufs2(icon, clonk)
{
   CreateContents(KSLM, clonk);
  
  ChooseGear2(clonk);
}

func Waffent2(icon, clonk)
{
   CreateContents(KRFL, clonk);
  
  ChooseGear2(clonk);
}

func ChooseGear2(clonk)
{
  CloseMenu(clonk); // Relaunch-Countdown-Menü schliessen
  CreateMenu(HZCK, clonk, 0, 0, "Wähle eine Ausrüstung", 0, C4MN_Style_Context);
  
  AddMenuItem("Rüstung", "Armor", HARM, clonk, 0, clonk);
  AddMenuItem("Jetpack", "Jetpack", JTPK, clonk, 0, clonk);
  AddMenuItem("Schildgenerator", "Schildg", HSHD, clonk, 0, clonk);
  AddMenuItem("Drohne", "Drohne", DRSU, clonk, 0, clonk);
}

func ChooseGear3(clonk)
{
  CloseMenu(clonk); // Relaunch-Countdown-Menü schliessen
  CreateContents(NH5B, clonk);
  CreateMenu(HZCK, clonk, 0, 0, "Wähle eine Ausrüstung", 0, C4MN_Style_Context);
  
  AddMenuItem("Rüstung", "Armor2", HARM, clonk, 0, clonk);
  AddMenuItem("Jetpack", "Jetpack2", JTPK, clonk, 0, clonk);
  AddMenuItem("Schildgenerator", "Schildg2", HSHD, clonk, 0, clonk);
  AddMenuItem("Drohne", "Drohne2", DRSU, clonk, 0, clonk);
}


func Armor2(icon, clonk)
{
   CreateContents(HARM, clonk)->Activate(clonk);
  
  ChooseGear4(clonk);
}

func Jetpack2(icon, clonk)
{
   CreateContents(JTPK, clonk)->Activate(clonk);
  
  ChooseGear4(clonk);
}

func Schildg2(icon, clonk)
{
   CreateContents(HSHD, clonk)->Activate(clonk);
  
  ChooseGear4(clonk);
}

func Armor(icon, clonk)
{
   CreateContents(HARM, clonk)->Activate(clonk);
  
  ChooseGear3(clonk);
}

func Jetpack(icon, clonk)
{
   CreateContents(JTPK, clonk)->Activate(clonk);
  
  ChooseGear3(clonk);
}

func Schildg(icon, clonk)
{
   CreateContents(HSHD, clonk)->Activate(clonk);
  
  ChooseGear3(clonk);
}

func ChooseGear4(clonk)
{
  CloseMenu(clonk); // Relaunch-Countdown-Menü schliessen
  CreateContents(NH5B, clonk);
  CreateMenu(HZCK, clonk, 0, 0, "Wähle eine Ausrüstung", 0, C4MN_Style_Context);
  
  AddMenuItem("Bauequipment", "Conkit", CNKT, clonk, 0, clonk);
  AddMenuItem("Geschützbausatz", "Conkit2", CNK2, clonk, 0, clonk);
  AddMenuItem("5x Feuerstein", "Flint", FLNT, clonk, 0, clonk);
  AddMenuItem("4x Superflint", "SFlint", SFLN, clonk, 0, clonk);
  AddMenuItem("3x Teraflint", "EFlint", EFLN, clonk, 0, clonk);
}

func Conkit(icon, clonk)
{
   CreateContents(CNKT, clonk, 3);
   CreateContents(FLAG, clonk);
  
  ChooseBunker(clonk);
}

func Conkit2(icon, clonk)
{
   CreateContents(CNK2, clonk);
  
  ChooseBunker(clonk);
}

func Flint(icon, clonk)
{
   CreateContents(FLNT, clonk, 5);
 
  ChooseBunker(clonk);
}

func SFlint(icon, clonk)
{
   CreateContents(SFLN, clonk, 4);
 
  ChooseBunker(clonk);
}

func EFlint(icon, clonk)
{
   CreateContents(EFLN, clonk, 3);
 
  ChooseBunker(clonk);
}

func RelaunchPlayer(player)
{
  var team = GetPlayerTeam(player);
  casualties[team - 1]++;
  SetScoreboardData(team, 2, Format("%d", casualties[team - 1]));

  var b1 = GetPlayerTeam(GetOwner(bunker1)) == GetPlayerTeam(player);
  var b2 = GetPlayerTeam(GetOwner(bunker2)) == GetPlayerTeam(player);
  var b3 = GetPlayerTeam(GetOwner(bunker3)) == GetPlayerTeam(player);
  var b4 = GetPlayerTeam(GetOwner(bunker4)) == GetPlayerTeam(player);
  var b5 = GetPlayerTeam(GetOwner(bunker5)) == GetPlayerTeam(player);
  var b6 = GetPlayerTeam(GetOwner(bunker6)) == GetPlayerTeam(player);
  var b7 = GetPlayerTeam(GetOwner(bunker7)) == GetPlayerTeam(player);
  var b8 = GetPlayerTeam(GetOwner(bunker8)) == GetPlayerTeam(player);
  var b9 = GetPlayerTeam(GetOwner(bunker9)) == GetPlayerTeam(player);

  // alle Bunker gehören dem Feind?
  if (!b1 && !b2 && !b3 && !b4 && !b5 && !b6 && !b7 && !b8 && !b9)
  {
    // kein verbündeter SFT in freier Wildbahn?
    if (!FindObject2(Find_OCF(OCF_CrewMember), Find_Allied(player), Find_NoContainer()))
    {
      // das ganze Team terminieren!
      for (var i = GetPlayerCount(); i--;)
      {
        var p = GetPlayerByIndex(i);    
        if (GetPlayerTeam(p) == GetPlayerTeam(player))
        {
          var content;
          while (content = Contents(0, GetCursor(p)))
          {
            // Clonk vorm Killen entleeren
            RemoveObject(content);
          }        
          EliminatePlayer(p);
        }
      }
      return;
    }
  }
  var clonk = CreateObject(HZCK, 0, 0, player);
  MakeCrewMember(clonk, player);
  clonk -> DoEnergy(100);
  SelectCrew(player, clonk, 1);
    
  var homeCount = 36 - ((b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 + b9) * 4);
  InitializeClonk(clonk, homeCount);
}



func ChooseBunker(clonk)
{
  var b1 = GetPlayerTeam(GetOwner(bunker1)) == GetPlayerTeam(GetOwner(clonk));
  var b2 = GetPlayerTeam(GetOwner(bunker2)) == GetPlayerTeam(GetOwner(clonk));
  var b3 = GetPlayerTeam(GetOwner(bunker3)) == GetPlayerTeam(GetOwner(clonk));
  var b4 = GetPlayerTeam(GetOwner(bunker4)) == GetPlayerTeam(GetOwner(clonk));
  var b5 = GetPlayerTeam(GetOwner(bunker5)) == GetPlayerTeam(GetOwner(clonk));
  var b6 = GetPlayerTeam(GetOwner(bunker6)) == GetPlayerTeam(GetOwner(clonk));
  var b7 = GetPlayerTeam(GetOwner(bunker7)) == GetPlayerTeam(GetOwner(clonk));
  var b8 = GetPlayerTeam(GetOwner(bunker8)) == GetPlayerTeam(GetOwner(clonk));
  var b9 = GetPlayerTeam(GetOwner(bunker9)) == GetPlayerTeam(GetOwner(clonk));

  CreateMenu(BK5B, clonk, 0, 0, "Entry Point", 0, C4MN_Style_Context, true);

  AddMenuItem("North-West",   "EnterBunker1", SY5B, clonk, 0, clonk, 0, 2, !b1 + 1);
  AddMenuItem("Middle-West",  "EnterBunker2", SY5B, clonk, 0, clonk, 0, 2, !b2 + 1);
  AddMenuItem("South-West",   "EnterBunker3", SY5B, clonk, 0, clonk, 0, 2, !b3 + 1);
  AddMenuItem("North-Middle", "EnterBunker4", SY5B, clonk, 0, clonk, 0, 2, !b4 + 1);
  AddMenuItem("Main",         "EnterBunker5", SY5B, clonk, 0, clonk, 0, 2, !b5 + 1);
  AddMenuItem("South-Middle", "EnterBunker6", SY5B, clonk, 0, clonk, 0, 2, !b6 + 1);
  AddMenuItem("North-East",   "EnterBunker7", SY5B, clonk, 0, clonk, 0, 2, !b7 + 1);
  AddMenuItem("Middle-East",  "EnterBunker8", SY5B, clonk, 0, clonk, 0, 2, !b8 + 1);
  AddMenuItem("South-East",   "EnterBunker9", SY5B, clonk, 0, clonk, 0, 2, !b9 + 1);

  SelectMenuItem(0, clonk);
}

func UpdateBunkerMenu()
{
  for (var i = GetPlayerCount(); i--;)
  {
    var clonk = GetCursor(GetPlayerByIndex(i));
    var team = GetPlayerTeam(GetOwner(clonk));

    var b1 = GetPlayerTeam(GetOwner(bunker1)) == GetPlayerTeam(GetOwner(clonk));
    var b2 = GetPlayerTeam(GetOwner(bunker2)) == GetPlayerTeam(GetOwner(clonk));
    var b3 = GetPlayerTeam(GetOwner(bunker3)) == GetPlayerTeam(GetOwner(clonk));
    var b4 = GetPlayerTeam(GetOwner(bunker4)) == GetPlayerTeam(GetOwner(clonk));
    var b5 = GetPlayerTeam(GetOwner(bunker5)) == GetPlayerTeam(GetOwner(clonk));
    var b6 = GetPlayerTeam(GetOwner(bunker6)) == GetPlayerTeam(GetOwner(clonk));
    var b7 = GetPlayerTeam(GetOwner(bunker7)) == GetPlayerTeam(GetOwner(clonk));
    var b8 = GetPlayerTeam(GetOwner(bunker8)) == GetPlayerTeam(GetOwner(clonk));
    var b9 = GetPlayerTeam(GetOwner(bunker9)) == GetPlayerTeam(GetOwner(clonk));
    var b0 = FindObject2(Find_OCF(OCF_CrewMember), Find_Allied(GetOwner(clonk)), Find_NoContainer());
    
    // Scoreboard aktualisieren
    SetScoreboardData(GetPlayerTeam(GetOwner(clonk)), 1, Format("%d", b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 + b9));

    // alle Bunker gehören dem Feind und kein verbündeter SFT in freier Wildbahn?
    if (!b1 && !b2 && !b3 && !b4 && !b5 && !b6 && !b7 && !b8 && !b9 && !b0)
    {
      var content;
      while (content = Contents(0, clonk))
      {
        // Clonk vorm Killen entleeren
        RemoveObject(content);
      }
      EliminatePlayer(GetOwner(clonk));
    }
    else
    {
      if (GetMenu(clonk) == BK5B)  
      {
        var index = GetMenuSelection(clonk);
        ClearMenuItems(clonk);

        AddMenuItem("North-West",   "EnterBunker1", SY5B, clonk, 0, clonk, 0, 2, !b1 + 1);
        AddMenuItem("Middle-West",  "EnterBunker2", SY5B, clonk, 0, clonk, 0, 2, !b2 + 1);
        AddMenuItem("South-West",   "EnterBunker3", SY5B, clonk, 0, clonk, 0, 2, !b3 + 1);
        AddMenuItem("North-Middle", "EnterBunker4", SY5B, clonk, 0, clonk, 0, 2, !b4 + 1);
        AddMenuItem("Main",         "EnterBunker5", SY5B, clonk, 0, clonk, 0, 2, !b5 + 1);
        AddMenuItem("South-Middle", "EnterBunker6", SY5B, clonk, 0, clonk, 0, 2, !b6 + 1);
        AddMenuItem("North-East",   "EnterBunker7", SY5B, clonk, 0, clonk, 0, 2, !b7 + 1);
        AddMenuItem("Middle-East",  "EnterBunker8", SY5B, clonk, 0, clonk, 0, 2, !b8 + 1);
        AddMenuItem("South-East",   "EnterBunker9", SY5B, clonk, 0, clonk, 0, 2, !b9 + 1);

        SelectMenuItem(index, clonk);
      }
    }
  }  
}

func EnterBunker1(icon, clonk) { CreateShield(clonk, bunker1); }
func EnterBunker2(icon, clonk) { CreateShield(clonk, bunker2); }
func EnterBunker3(icon, clonk) { CreateShield(clonk, bunker3); }
func EnterBunker4(icon, clonk) { CreateShield(clonk, bunker4); }
func EnterBunker5(icon, clonk) { CreateShield(clonk, bunker5); }
func EnterBunker6(icon, clonk) { CreateShield(clonk, bunker6); }
func EnterBunker7(icon, clonk) { CreateShield(clonk, bunker7); }
func EnterBunker8(icon, clonk) { CreateShield(clonk, bunker8); }
func EnterBunker9(icon, clonk) { CreateShield(clonk, bunker9); }

func CreateShield(clonk, bunker)
{
  if (GetPlayerTeam(GetOwner(bunker)) == GetPlayerTeam(GetOwner(clonk)))
  {  
    CloseMenu(clonk);

    var sanctuary = Contained(clonk);
    Enter(bunker, clonk);

    RemoveObject(sanctuary);
  }
  else Sound("Error", 0, 0, 0, GetOwner(clonk) + 1);
}

func OnMenuSelection(index, clonk)
{
  if (GetMenu(clonk) == BK5B)  
  {
    if (index == 0) SetPlrView(GetOwner(clonk), bunker1);
    if (index == 1) SetPlrView(GetOwner(clonk), bunker2);
    if (index == 2) SetPlrView(GetOwner(clonk), bunker3);
    if (index == 3) SetPlrView(GetOwner(clonk), bunker4);
    if (index == 4) SetPlrView(GetOwner(clonk), bunker5);
    if (index == 5) SetPlrView(GetOwner(clonk), bunker6);
    if (index == 6) SetPlrView(GetOwner(clonk), bunker7);
    if (index == 7) SetPlrView(GetOwner(clonk), bunker8);
    if (index == 8) SetPlrView(GetOwner(clonk), bunker9);
  }
}

func MenuQueryCancel()
{ 
  return(true);
}

func GetPlayerByTeam(teamId)
{
  for (var i = GetPlayerCount(); i--;)
  {
    if (GetPlayerTeam(GetPlayerByIndex(i)) == teamId) return i;
  }
  return(-1);
}
