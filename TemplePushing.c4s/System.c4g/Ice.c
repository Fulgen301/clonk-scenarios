/*--- Make ice chunk create frost wave upon impact ---*/
 
#strict 2
 
#appendto ICE1
 
local hit;
 
protected func Hit()
{
        if (!hit)
        {
                var frostwave = CreateObject(MFWV, 0, 0, NO_OWNER);
                frostwave->SetMaxRadius(60);
                frostwave->Activate(this);
                hit = true;
        }
 
		CastParticles("Snow", 50, 20, 0, 0, 50, 80, RGBa(120,120,255,0), RGBa(90,90,255,127));
		RemoveObject();
}