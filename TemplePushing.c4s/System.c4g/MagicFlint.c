/*-- Make Summon Flint spell compatible with scrolls --*/

#strict 2

#appendto MGFL

public func Activate(object caster, object realcaster)
{
	var result = CheckEffect("FlintNSpell", 0, 125);
	if (result)
	{
		RemoveObject();
		return result != -1;
	}

	Sound("Magic*");
	CreateParticle("MSpark", 0,0, 1000, RGBa(255,50,50,150));

	if (realcaster) caster = realcaster;

	var flints = [SFLN, EFLN];
	caster->CreateContents(flints[Random(GetLength(flints))]);

	RemoveObject();
	return 1;
}
