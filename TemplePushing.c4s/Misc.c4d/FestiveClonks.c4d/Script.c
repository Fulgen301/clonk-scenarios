/*-- Festliche Clonks --*/

#strict 2
#appendto CLNK

func Construction () {
	if (mode && mode->GetID() == MODE_Festive)
	{
		if(GetID() == CLNK) SetGraphics(0, this, FSVC);
		return (_inherited (...));
	}
}
