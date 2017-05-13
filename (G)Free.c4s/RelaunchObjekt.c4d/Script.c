/*-- Neues Objekt --*/

#strict
local posX,posY;
local nposition;

func Initialize() {
if(!GlobalN("initialized")==0)while(!GoodRelaunchPosition()) NewRelaunchPosition();  
  return(1);
}

protected func NewRelaunchPosition()
{
SetPosition(Random(LandscapeWidth()),Random(LandscapeHeight()));
}


protected func GoodRelaunchPosition()
{
if(GetX()==0 || GetY()==0)return(false);

if(Stuck() || GBackSolid(0,4) || GBackSolid(0,2) || GBackSolid(0,8) || GBackSolid(0,16) ||! GBackSolid(0,18))return(false);

if(Stuck() || GBackSolid(-4,0) || GBackSolid(4,0) || GBackSolid(-6,0) || GBackSolid(6,0) || GBackSolid(-10,0) || GBackSolid(10,0) || GBackSolid(-14,0) || GBackSolid(14,0))return(false);
if(FindObject(0,-4,-2,8,10,OCF_OnFire()))return(false);

if(GlobalN("SkyLandscape")==1)
{
if(FindObject(ZFRK,-13,-2,26,30))return(false);
}

if(InLiquid())return(false);

return(true);
}

protected func RelaunchPlr()
{
while(!GoodRelaunchPosition())NewRelaunchPosition();
CastParticles("PSpark",20,10,0,0,50,100,RGB(154,206,254),RGB(154,206,254));
var crew=FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,this());
if(GlobalN("godmode")==1)
{
crew->BecomeGod();


}

RemoveObject(0,1);
}

protected func RelaunchPlr2()
{

CastParticles("PSpark",20,10,0,0,50,100,RGB(154,206,254),RGB(154,206,254));
var crew=FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,this());
SetPosition(703,1318);
if(GlobalN("godmode")==1)
{
crew->BecomeGod();


}

RemoveObject(0,1);
}

protected func RelaunchEffect()
{
}

protected func JoinPlr()
{
if(!GlobalN("JoinOK"))return(Message("$MsgNoJoin$",0,0));
while(!GoodRelaunchPosition())NewRelaunchPosition();

Log("$MsgPlayerJoint$",GetPlayerName(GetOwner(FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,this()))));
var crew=FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,this());
if(GlobalN("godmode")==1)
{
crew->BecomeGod();
}

RemoveObject(0,1);
}
