/*---- FREE!!! ----*/
/*-     KTO     -*/
/*--CoOb Arbeit von Gecko und Clonkus93(KdD -E)--*/
/*--Clonkus musste Essen oO?Und ich auf Klo XD --*/

#strict

global func DoRound() {
Round++;
Log("<c ffcc00>Runde </c><c ff0000>%d</c> <c ffcc00>wurde gestartet!</c>",Round);
  return(1);
}

static Box; //Das Szeanrio ist Maguskampf in der Arena
static Relaunches; //Relaunches
static RelaunchesPosi; //RelaunchPosition (Es gibt von 1 bis 6 welche!)
static NoRela; //Kein Relaunchtyp
static PlayerRelaunches; //Spieler RElaunch Mod
static TeamRelaunches; //Team RElaunch Mod
static RelaunchesTeam1;//Die relaunches für Team 1
static RelaunchesTeam2;//Relaunches für Team2
static Round;//Runde!

protected func Initialize() {
RelaunchesTeam1=8;//Relaunches für Team1
RelaunchesTeam2=8;//Relaunchanzahö für Team2
 Box=1; //Das Szeanrio ist die Box Oo
 Relaunches=3; //Relaunch Anzahl für jeden Spieler
 NoRela=1; //Kein RelaunchTyp gewählt
 PlayerRelaunches=0; //keine Spieler relaunchs(nochnicht gewählt!)
 TeamRelaunches=0; //keine Team relaunchs(nochnicht gewählt!)
  // T-Melee Objekt erschaffen
 if (!FindObject(MEL2)) CreateObject(MEL2);
 RemoveAll(MELE);  	
  // Regel#1 erschaffen
 if (!FindObject(AGEH)) CreateObject(AGEH);
  // Regel#2 erschaffen
 if (!FindObject(MGES)) CreateObject(MGES);
 	  	for(var spwn in FindObjects(Find_ID(SPNP))) {
						var Contents = [FLNT, PMAN, , PSTO, PHEL, WBRL, LBRL, ABRL, METL];
		CreateContents(Contents[Random(11)], spwn);
   }
  DoRound();
  return(ScriptGo(1));//TimerStarten
}

func Script1() 
{
for(var i=0;i<24;i++)
  {
  if(GetPlayerName(i)) ObjectSetAction(GetCursor(i),"Dead",0,0,1);
  }
Message("<c 00ff00>Möge der Kampf um den Goldklumpen beginnen!");//...kommt eine kuhle Nachricht!
}


/*--- Relaunch System ---*/

global func SetRelaunches()
{
 if(TeamRelaunches==1)
  {
   var Spieler=0;  //das ist der Spieler z.b. von Team1
   var Gegner;     // das soll ein spieler von team2 sein (muss es aber nicht)
   var Durchlauf=0;//eine durchlaufnummer für die whileschleife
   while(Hostile(Spieler,Gegner)==true)//sollange Spieler und gegner verbündet sind wird die schleife ausgeführt
     {
     Durchlauf++;//der durchlauf gibt den spieler an
     Gegner=GetOwner(GetCursor(Durchlauf));//gibt  Gegner einen neuen spieler
     }
   var i1=GetPlayerTeam(Spieler);
   var i2=GetPlayerTeam(Gegner);
   for(;i1--;) Global(i1)=Relaunches;
   for(;i2--;) Global(i2)=Relaunches;
  }
if(PlayerRelaunches==1)
  {
 var i=GetPlayerCount();
 for(;i--;) Global(GetPlayerByIndex(i))=Relaunches;
  }
}

global func Relaunches2(val)
{
if(val==1)
  {
  RelaunchesTeam1+=1;
  RelaunchesTeam2+=1;
  }
if(val==-1)
  {
  RelaunchesTeam1-=1;
  RelaunchesTeam2-=1;
  }
if(Relaunches+val>15 || Relaunches+val<1) return();
if(val==-1)Relaunches=Relaunches-1;
if(val==+1)Relaunches=Relaunches+1;
//Message("Es sind jetzt %d Relaunchs eingestellt",0,Relaunches);
if(PlayerRelaunches==1)
  {
  Log("<c ccffff>{{MEN5}}Es sind jetzt %d Relaunchs eingestellt{{RELA}}</c>",Relaunches);
  Message("<c ccffff>Es sind jetzt %d Relaunchs eingestellt{{RELA}}</c>",GetCursor(0),Relaunches);
  }
if(TeamRelaunches==1)
  {
  Log("<c ccffff>{{MEN5}}Es sind jetzt %d Team-Relaunchs eingestellt{{RELA}}</c>",RelaunchesTeam1);
  Message("<c ccffff>Es sind jetzt %d Team-Relaunchs eingestellt{{RELA}}</c>",GetCursor(0),RelaunchesTeam1);
  }
SetRelaunches();
goto(10);
}

func Script10()
{
SetRelaunches();
CreateMenu(WIPF,GetCursor(0),GetCursor(0),0,"Spiel Optionen",1,1);
if(NoRela==1) AddMenuItem("TeamRelaunchs","ModTE();",MEL2,GetCursor(0));
if(NoRela==1) AddMenuItem("SpielerRelaunchs","ModSP();",MELE,GetCursor(0));
if(TeamRelaunches==1) AddMenuItem("TeamRelaunchs erhöhen","Relaunches2(+1)",PLAR,GetCursor(0));
if(TeamRelaunches==1) AddMenuItem("TeamRelaunchs vermindern","Relaunches2(-1)",MIAR,GetCursor(0));
if(PlayerRelaunches==1) AddMenuItem("SpielerRelaunchs erhöhen","Relaunches2(+1)",PLAR,GetCursor(0));
if(PlayerRelaunches==1) AddMenuItem("SpielerRelaunchs vermindern","Relaunches2(-1)",MIAR,GetCursor(0));
}

global func ModSP(val)
{
if(val==1)
Log("SpielerRelaunchs wurden ausgewählt.");
NoRela=0;
PlayerRelaunches=1;
TeamRelaunches=0;
goto(10);
}

global func ModTE(val)
{
if(val==1)
Log("TeamRelaunchs wurden ausgewählt.");
NoRela=0;
PlayerRelaunches=0;
TeamRelaunches=1;
goto(10);
}

public func RelaunchPlayer(plr)
{
if(PlayerRelaunches==1)
  {
  Global(plr)=Global(plr)-1;
  if(Global(plr)<0)
    { 
    EliminatePlayer(plr);
    return(1);
    }
  }
if(TeamRelaunches==1)
  {
  if(GetPlayerTeam(plr)==1)
    {
    RelaunchesTeam1-=1;
    if(RelaunchesTeam1<0) return(EliminatePlayer(plr));
    }
  if(GetPlayerTeam(plr)==2)
    {
    RelaunchesTeam2-=1;
    if(RelaunchesTeam2<0) return(EliminatePlayer(plr));
    }   
  }
Var()=CreateObject(MAGE,0,0,plr);
MakeCrewMember(Var(),plr);
if(PlayerRelaunches==1)
  {
  Log("{{MEN5}}%s <c ffcc00>hat noch</c> <c ff0000>%d</c> <c ffcc00>Relaunchs</c>{{RELA}}",GetPlayerName(plr),Global(plr));
  }
if(TeamRelaunches==1)
  {
  if(GetPlayerTeam(plr)==1)
    {
    Log("{{MEN5}} Das Team von %s <c ccffff>hat noch</c> <c ff0000>%d</c> <c ccffff>Relaunchs</c>{{RELA}}",GetPlayerName(plr),RelaunchesTeam1);
    }
      if(GetPlayerTeam(plr)==2)
    {
    Log("{{MEN5}} Das Team von %s <c ccffff>hat noch</c> <c ff0000>%d</c> <c ccffff>Relaunchs</c>{{RELA}}",GetPlayerName(plr),RelaunchesTeam2);
    }
  }
var rel=CreateObject(RELA,583,404,-1);
 Enter(rel,Var());
 ObjectSetAction(rel,"Relaunch");
//if(NewRel==1) ObjectSetAction(rel,"Relaunch2");
DoMagicEnergy(200,Var());
SetCursor(plr,Var());
DoEnergy(100,Var());
}

/*--Relaunchsystem Ende--*/

func Script11()
{
for(var i=0;i<24;i++)
  {
  if(GetPlayerName(i)) ObjectSetAction(GetCursor(i),"FlatUp",0,0,1);
  }
}

func Script15()
{
if(NoRela==1) return(goto(10));
}

func Script20()
{
if(NoRela==1) return(goto(14));
return(1);
}
func Script100()
{
  	for(var spwn in FindObjects(Find_ID(SPNP))) {
				var Contents = [FLNT, PMAN, , PSTO, PHEL, WBRL, LBRL, ABRL, METL];
		CreateContents(Contents[Random(11)], spwn);
   }
   }
   
   func Script110()
{
return(goto(20));
   }
