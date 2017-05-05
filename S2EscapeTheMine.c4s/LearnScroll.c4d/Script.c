/* Zauber-Lernschriftrolle */

#strict 2

local idSpell;

static SCRL_FirstCollection; // Wurde jemals eine Rolle eingesammelt? Für Intro-Nachricht

public func Selection()
  {
  // wer bin ich? der da!
  if (idSpell)
    {
    // Erstes Einsammeln: Intronachricht
    if (!SCRL_FirstCollection)
      {
      ++SCRL_FirstCollection;
      Message("$MsgIntro$");
      Sound("Ding", true);
      }
    PlayerMessage(GetOwner(Contained()),"{{%i}} %s",Contained(),idSpell,GetName(0,idSpell));
    }
  }

protected func Entrance(object pContainer) { if(GetOCF(pContainer) & OCF_CrewMember) Selection(); }

protected func Activate(object pByClonk)
  {
  var iPlr = GetController(pByClonk);
  if(!idSpell || !GetName(0, idSpell))
    {
    // Kein Zauber belegt
    Sound("Error", false, this, 100, iPlr+1);
    PlayerMessage(iPlr, "$MsgNoSpell$", this);
    return true;
    }
  // Bauplan?
  if (!(GetCategory(0, idSpell) & C4D_Magic))
    {
    if (GetPlrKnowledge(iPlr, idSpell))
      {
      Sound("Error", false, this, 100, iPlr+1);
      PlayerMessage(iPlr, "$MsgKnown$", this, GetName(0, idSpell));
      return true;
      }
    else
      {
      SetPlrKnowledge(iPlr, idSpell);
      }
    }
  else
    {
    // Kennt den Zauber schon?
    if (GetPlrMagic(iPlr, idSpell))
      {
      Sound("Error", false, this, 100, iPlr+1);
      PlayerMessage(iPlr, "$MsgKnown$", this, GetName(0, idSpell));
      return true;
      }
    else
      {
      // Den Zauber lernen
      SetPlrMagic(iPlr, idSpell);
      }
    }
  PlayerMessage(iPlr, "$MsgLearned$", pByClonk, GetName(0, idSpell));
  Sound("SpellSysCombo*", 0, 0, 0, GetOwner()+1);
  CreateParticle("NoGravSpark", 0,0,  0,-6, 5*10, RGBa(255,255,0, 0), pByClonk);
  CreateParticle("NoGravSpark", 0,0, -5,-3, 5*10, RGBa(255,255,0, 0), pByClonk);
  CreateParticle("NoGravSpark", 0,0, -5, 3, 5*10, RGBa(255,255,0, 0), pByClonk);
  CreateParticle("NoGravSpark", 0,0,  5,-3, 5*10, RGBa(255,255,0, 0), pByClonk);
  CreateParticle("NoGravSpark", 0,0,  5, 3, 5*10, RGBa(255,255,0, 0), pByClonk);
  CreateParticle("NoGravSpark", 0,0,  0, 6, 5*10, RGBa(255,255,0, 0), pByClonk);
  return true;
  }

public func SetSpell(id idMagic)
  {
  // Rolle ist nun beschrieben
  // Grafik setzen
  SetGraphics(0,0,idMagic,1,GFXOV_MODE_Picture);
  SetObjDrawTransform(350,-300,3000,150,500,-2000, this, 1);
  SetAction("Be"); // Für zwei Richtungen
  idSpell = idMagic;
  // Name setzen
  UpdateName();
}

protected func UpdateTransferZone()
  {
  // Für Objects.txt-Schriftrollen
  UpdateName();
  }

protected func UpdateName()
  {
  // Namen nach Zauber setzen
  if (idSpell)
    SetName(Format("%s: %s", GetName(0, GetID()), GetName(0,idSpell)));
  else
    SetName();
  }
  