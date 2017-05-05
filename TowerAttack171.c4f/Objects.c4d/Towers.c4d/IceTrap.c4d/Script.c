/*-- Eisschleuder --*/

#strict

func Construction()
{
  SetCon(100);
  SetPosition(GetX(),GetY()+7);
}

func Timer()
{
  // Ausgebaut?
  if(GetCon()<100)
    return 0;
  // Genug gefeuert?
  if(GetEffect("IntFireDelay",this))
    return 0;
  if(FindObject2(Find_AtPoint(0,-5),Find_OCF(OCF_Alive()),Find_Hostile(GetOwner())))
  {
    AddEffect("IntFireDelay",this,5,FireDelay(),this);
    Fire();
  }
  return(0);
}

func Fire()
{
  // Zauberobjekt erschaffen und aktivieren
  var pSpell = CreateObject(MFBZ,0,0,GetOwner());
  if (!pSpell) return; // Zauber fehlgeschlagen
  pSpell->~Activate(this);
  Message("",this);
  return true;
}

func FireDelay(){ return 240;/*7s*/}

func CanBeBuild(pClonk)
{
  return true;
}

func DoSpellAim(pSpell)
{
  SetPosition(GetX(),GetY()+15);
  pSpell->~ActivateAngle(this, RandomX(-10,10));
  SetPosition(GetX(),GetY()-15);
  Message("",this);
  return 1;
}

func IsLevel1(){return 0;}

func UpgradeTo()
{
  return FRTP;
}

func UpgradeCost()
{
  return 30;
}
