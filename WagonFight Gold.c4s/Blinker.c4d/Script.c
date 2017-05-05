/* Auswahlpfeil für Zauber mit Objektziel */

#strict

func Initialize()
{
SetAction("Arrow");
ScheduleCall(this(),"Remove",25,0);
}

func Remove()
{
var brand=CreateObject(FBMP,0,0,-1);
SetYDir(10,brand);
RemoveObject();
}
