/* Acid+Lava Leak */

#strict 2

static g_leak_tunnel, g_leak_materials, g_leakpos_x, g_leakpos_y;

global func AddLeakEffect()
{
	return AddEffect("LiquidLeakage", 0, 1, 1);
}

global func FxLiquidLeakageStart(r,n,t)
{
	if (t) return; // temp
	g_leak_tunnel = Material("Tunnel");
	g_leak_materials = [Material("Acid"), Material("DuroLava")];
	g_leakpos_x = [0, LandscapeWidth() - 1];
	g_leakpos_y = [2200, 2200];
	return FX_OK;
}

global func FxLiquidLeakageTimer()
{
	for (var i in [0, 1, 0, 1])
	{
		var x = g_leakpos_x[i];
		var y = g_leakpos_y[i];
		var mat = GetMaterial(x, y);
		if (mat == g_leak_tunnel)
			InsertMaterial (g_leak_materials[Random(2)], x, y - Random(10), (31*!x)-36+Random(10), -11+Random(10));
		else
			--g_leakpos_y[i];
	}
}
