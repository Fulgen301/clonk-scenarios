/*-- Scroll --*/
#strict 2

#appendto SCRL

static SCRL_spells;

protected func Initialize()
{
	SetSpell(SCRL_spells[Random(GetLength(SCRL_spells))]);

	return _inherited();
}

public func SpellFailed(id idSpell, object pAimingClonk)
{
	// Spell canceled? Give back the scroll
	SetVisibility(VIS_All);
	SetSpell(idSpell);
	if(pAimingClonk && !pAimingClonk->~RejectCollect(GetID(this), this))
	{
		Enter(pAimingClonk, this);
	}
	pAimingClonk = 0;
	return 0;
}

global func SetScrollSpells(array spells)
{
	SCRL_spells = spells;
}

protected func WannaRemove()
{
	// manche Zauber hängen gerne Effekte an den Caster
	if(!(GetEffectCount(0,this()) - GetEffectCount("FadeOut", this)) && !pAimingClonk) RemoveObject();
}

public func AvoidFadeOut()
{
	return GetAction(this) == "WannaRemove";
}

private func DoMagic(object pByClonk)
{
	SetVisibility(VIS_Owner | VIS_Allies, this);
	return _inherited(pByClonk);
}

func SetSpell(id spell)
{
	SetClrModulation(spell->~ScrollColor());
	return _inherited(spell, ...);
}

func Entrance2(object pContainer)
{
	if (pContainer && GetOCF(pContainer) & OCF_CrewMember)
	{
		pContainer->~ShowTeamHUD(Format("{{%i}}", idSpell));
	}
	return _inherited(pContainer, ...);
}
