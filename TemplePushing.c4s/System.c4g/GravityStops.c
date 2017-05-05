/*-- Make the Gravity spell stop Magic Lightning and Lavashot --*/
#strict 2
#appendto LGTS
#appendto _LVS

func MagicStop(object caller)
{
	var vertex = GetVertexNum() - 1;
	CastParticles("MSpark", 50, 20, AbsX(GetVertex(vertex, VTX_X)), AbsY(GetVertex(vertex, VTX_Y)), 50, 75, RGBa(128,128,255,0), RGBa(255,255,255,127));
	return RemoveObject();
}