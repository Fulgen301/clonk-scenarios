/*-- Allow custom radius for Frostwave spells --*/
 
#strict 2
 
#appendto MFWV
 
local maxRadius;
 
protected func Initialize()
{
        maxRadius = 90;
}
 
func Activate(object caster, object realcaster)
{
        if (realcaster) caster = realcaster;
 
        if (AddEffect("FrostwaveNSpell", this, 130, 1, this, 0, caster, maxRadius) <= 0)
        {
                RemoveObject();
                return 1;
        }
 
        Sound("MgWind*");
        return 1;
}
 
func FxFrostwaveNSpellStart(object target, int number, int temp, object caster, int maxRadius)
{
        if (temp) return;
 
        // Initial radius
        EffectVar(1, target, number) = 20;
 
        // Position
        EffectVar(2, target, number) = caster->GetX();
        EffectVar(3, target, number) = caster->GetY();
 
        // Caster
        EffectVar(4, target, number) = caster;
        EffectVar(6, target, number) = caster->GetController();
 
        // Maximum radius
        EffectVar(7, target, number) = maxRadius;
 
        // Combo
        var combo = caster->FindContents(ICE1);
        if (combo)
        {
                EffectVar(5, target, number) = true;
                combo->RemoveObject();
        }
 
        return 1;
}
 
func FxFrostwaveNSpellTimer(object target, int number, int time)
{
        var radius = EffectVar(1, target, number);
 
        // Remove if maximum radius is reached
        if (radius >= EffectVar(7, target, number)) return -1;
 
        // Position
        var absX = EffectVar(2, target, number), relX = AbsX(absX);
        var absY = EffectVar(3, target, number), relY = AbsY(absY);
 
        // Combo?
        var searchOCF = OCF_Alive;
        if (EffectVar(5, target, number)) searchOCF |= OCF_Collectible;
 
        // Effects!
        CreateParticle("FrostWave", relX, relY, RandomX(-1, 1), RandomX(-1, 1), 400 + 10 * radius, RGB(255, 255, 255));
 
        // Fling enemies
        var caster = EffectVar(4, target, number);
        for (var obj in FindObjects(
                Find_Distance(radius + 5, relX, relY), Find_Not(Find_Distance(radius - 5)),
                Find_OCF(searchOCF), Find_NoContainer(), Find_Not(caster)))
        {
                var angle = Angle(absX, absY, obj->GetX(), obj->GetY());
                obj->SetKiller(EffectVar(6, target, number));
                Fling(obj, Sin(angle, 80) / 9, -Cos(angle, 80) / 9);
                if (!Frozen(obj)) Freeze(obj, caster);
        }
 
        // Increase radius
        EffectVar(1, target, number) += 8;
 
        return 1;
}
 
/* Zaubercombo */
 
public func GetSpellClass() { return WATR; }
public func GetSpellCombo() { return "335"; } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
 
/* Custom radius */
public func SetMaxRadius(int radius) { maxRadius = radius; }