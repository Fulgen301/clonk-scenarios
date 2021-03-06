/*-- Clonk-Massen-KI --*/

#strict
#appendto CLNK

local ai_pTarget,ai_Param,ai_Param2,ai_IsBulkAI,ai_Mode,ai_Way,ai_pGeneral;

static const TWRATK_Cmd_Attack=1;
static const TWRATK_Cmd_Follow=2;
static const TWRATK_Cmd_Retreat=3;
static const TWRATK_Cmd_Defend=4;

public func SetBulkAI(fHero)
{
  // Timer erstellen
  if (GetEffect("*AI", this)) return();
  LocalN("ai_iRange", this)=35;
  return(AddEffect("BulkAI", this, 1, 25, this, 0, fHero));
}

public func RemoveBulkAI()
{
  // Timer löschen
  if(GetEffect("BulkAI",this)) RemoveEffect("BulkAI", this);
  LocalN("ai_iRange", this)=0;
  ai_IsBulkAI=0;
  return true;
}

protected func FxBulkAIStart(pTarget,iNum,iTemp,fHero)
{
  if(iTemp) return 0;
  InitBulkAIPart(this,0,fHero);
  ai_Way=Random(2);
  ai_IsBulkAI=true;
}

func OnAIIdle()
{
  if(GetCursor(GetOwner())==this)
    return 0;
  UpdateMovement();
}

protected func FxBulkAITimer()
{
  if(!GetAlive(this)) return -1;
  
  // Unstucken
  if(Stuck())
    return Schedule("SetPosition(GetX()+RandomX(-Random(2),Random(2)),GetY()-2)",2,10);
  
  if(ObjectDistance(ai_pTarget)>350||!Random(20)||!GetAlive(ai_pTarget))
    ai_pTarget=0;
  if(!ai_pTarget)
    if(!Random(5))
      ai_pTarget=FindObject2(Sort_Random(),Find_Hostile(GetOwner()),Find_OCF(OCF_Alive),Find_OCF(OCF_FightReady),Find_InRect(0,-50,-200+400*GetDir(),100),Find_NotHidden(),Find_PathFree());
  if(!Random(5))
    if(Contents())
      if(FindObject2(Find_InRect(0,-20,50*(GetDir()*2-1),40),Find_OCF(OCF_Alive),Find_Hostile(GetOwner()),Find_Func("Visible",GetOwner()),Find_Not(Find_Func("IsHidden")),Find_PathFree()))
      {
        if(this->~CanUse(GetID(Contents()))&&!(Contents()->~IsSpear()))
          ShiftContents();
        if((!(this->~CanUse(GetID(Contents()))))||Contents()->~IsSpear())
          if(!(this->~ControlThrow()))
            return AddCommand(this,"Throw");
      }

  // Betet? Nur wenn kein Gegner in der Nähe
  if(GetAction()=="Pray"||this->IsAiming())
    if(ai_pTarget)
      SetAction("KneelUp");

  if(ai_pTarget)
    if(GetCommand()ne"Attack")
      return SetAICommand("Attack",ai_pTarget);

  if(GetCommand()ne"Attack")
    UpdateMovement();
}

protected func FxBulkAIStop(pTarget,iNum,iReas,fTemp)
{
  if(fTemp) return 0;
  if(iReas!=4) return 0;
  // für den Ritter...
  this->~RemoveShield(); 
  while(Contents()) RemoveObject(Contents());
  //Schedule("FadeOut(0,2)",350,0,this);
  return -1;
}

private func SetAICommand(string szCom, object pTarget, int tx, int ty, object pTarget2, int iData, int iRetries)
{
  // Zielaktion stoppen
  this->~StopAiming();
  //Log("Setting %s %v %d %d %v %d %d", szCom, pTarget, tx, ty, pTarget2, iData, iRetries);
  // Mit Call-Command versehen, damit Fehlschlag kein Hmmm verursacht
  SetCommand(0, "Call", this, 0,0, 0, "BulkAICommand");
  var res = AddCommand(0, szCom, pTarget, tx, ty, pTarget2, iData, iRetries, C4CMD_SilentBase);
  return(res);
}

public func BulkAICommand()
{
  return true;
}

public func BulkAICommandFailed()
{
  return true;
}

public func IsAI()
{
  if(_inherited()) return 1;
  return IsBulkArmyPart();
}

public func SetAIMode(iMode,pTarget)
{
  ai_pGeneral=pTarget;
  ai_Mode=iMode;
  if(iMode)
  {
    SetObjectBlitMode(GFX_BLIT_Mod2+GFX_BLIT_ClrSfc_OwnClr);
    SetClrModulation(HSL(BoundBy(70*iMode,0,255),50,64));
  }
  else
  {
    SetObjectBlitMode();
    SetClrModulation();
  }
  if(iMode==TWRATK_Cmd_Follow)
    ai_Param = RandomX(20,100);
  SetCommand(0,"None");
  SetComDir(COMD_None);
  UpdateMovement();
}

public func IsBulkArmyPart()
{
  return GetEffect("BulkAI*",this);
}

public func HasMode(iMode,pObj)
{
  if(pObj)
    if(pObj!=ai_pGeneral)
      return 0;
  if(IsBulkArmyPart())
    if(GetAlive())  
      return ai_Mode==iMode;
}

public func RejectCollect(id idObject, object pObject)
{
  if(IsBulkArmyPart())
    if(Random(10))
      return 1;
  return _inherited(idObject,pObject);
}

// Destroyer-AI

public func SetDestroyerAI(fHero)
{
  // Timer erstellen
  if (GetEffect("*AI", this)) return();
  return(AddEffect("BulkAIDestroy", this, 1, 15, this, 0, fHero));
}

protected func FxBulkAIDestroyStart(pTarget,iNum,iTemp,fHero)
{
  if(iTemp) return 0;
  InitBulkAIPart(this,"Destroyer",fHero);
  ai_Way=Random(2);
  ai_IsBulkAI=true;
}

protected func FxBulkAIDestroyTimer()
{
  // Unstucken
  if(Stuck())
    return Schedule("SetPosition(GetX()+RandomX(-Random(2),Random(2)),GetY()-2)",2,10);
    
  if(!GetAlive(this)) return -1;
  
  if(GetID()==_ZMB)
  {
    if(!Random(5))
      if(FindObject2(Find_AtPoint(),Find_Category(C4D_Structure),Find_Hostile(GetOwner()),Find_OCF(OCF_Fullcon)))
	Explode(35);
  }
  else if(!Random(5))
  {
    var obj;
    if(GetAction()S="Walk")
      if(Contents())
        if(obj=FindObject2(/*Find_AtRect(0,-20,-50+100*GetDir(),40),*/Find_Or(Find_AtPoint(-50+100*GetDir(),0),Find_AtPoint(-50+100*GetDir(),15),Find_InRect(-40+80*GetDir(),10,30,30)),Find_Category(C4D_Structure),Find_Hostile(GetOwner()),Find_OCF(OCF_Fullcon)))
          if(Random(2))
            return AddCommand(this,"Throw");
          else
            return AddCommand(this,"Throw",0,GetX(obj),GetDefBottom(obj));
    if(GetAction()S="Jump")
      if(Contents())
        if(FindObject2(/*Find_AtRect(0,-20,-50+100*GetDir(),40),*/Find_AtPoint(0,10),Find_Category(C4D_Structure),Find_Hostile(GetOwner()),Find_OCF(OCF_Fullcon)))
        {
          SetComDir(COMD_None);
          return AddCommand(this,"Drop");
        }
  }
  UpdateMovement();
}

protected func FxBulkAIDestroyStop(pTarget,iNum,iReas,fTemp)
{
  return FxBulkAIStop(pTarget,iNum,iReas,fTemp);
}

// Bow-AI

public func SetBowAI(fHero)
{
  // Timer erstellen
  if (GetEffect("*AI", this)) return();
  return(AddEffect("BulkAIBow", this, 1, 50, this, 0, fHero));
}

protected func FxBulkAIBowStart(pTarget,iNum,iTemp,fHero)
{
  if(iTemp) return 0;
  InitBulkAIPart(this,"Bow",fHero);
  ai_IsBulkAI=true;
  ai_Way=Random(2);
}

protected func FxBulkAIBowTimer()
{
  if(!GetAlive(this)) return -1;
  // Unstucken
  if(Stuck())
    return Schedule("SetPosition(GetX()+RandomX(-Random(2),Random(2)),GetY()-2)",2,10);
   
  var pObj;
  if(IsBowEquipped())
    if(pObj=FindObject2(Find_OCF(OCF_Alive()),Find_Hostile(GetOwner()),Find_Not(Find_Distance(50)),Find_Distance(500),Find_PathFree(),Sort_Distance()))
      return this->~ExecuteAttackBow(pObj); 
  if(WildcardMatch(GetAction(),"*Bow*"))
    SetAction("Walk");    
  
  UpdateMovement();
}

protected func FxBulkAIBowStop(pTarget,iNum,iReas,fTemp)
{
  return FxBulkAIStop(pTarget,iNum,iReas,fTemp);
}

// Paladin-AI

public func SetPalaAI(fHero)
{
  // Timer erstellen
  if (GetEffect("*AI", this)) return();
  return(AddEffect("BulkAIBow", this, 1, 50, this, 0, fHero));
}

protected func FxBulkAIPalaStart(pTarget,iNum,iTemp,fHero)
{
  if(iTemp) return 0;
  InitBulkAIPart(this,"Pala",fHero);
  ai_IsBulkAI=true;
  ai_Way=Random(2);
}

protected func FxBulkAIPalaTimer()
{
  if(!GetAlive(this)) return -1;
  // Unstucken
  if(Stuck())
    return Schedule("SetPosition(GetX()+RandomX(-Random(2),Random(2)),GetY()-2)",2,10);
  
  // MPRT (Schutz), MGPH (Energieangriff), MLDL (Lebensentzug), MRVL (Wiederbelebung), MSMN (Skelett), MSPD (Geschwindigkeit), MHEL (Heilung)
  if(!Random(10))
  {
    // Heilung
    if(!Random(5))
      if(!GetEffect("IntMHELDelay", this))
	if(GetEnergy()<Random(12))
	  return DoConjurez(MHEL);
    if(MMGetChurch(GetOwner())==scBloodchurch)
    {
      // Lebensentzug
      if(!Random(5))
	if(!GetEffect("IntMGPHDelay", this))
	  if(ai_pTarget)
	    return DoConjurez(MGPH);
      // Geschwindigkeit
      if(!Random(10))
	if(!GetEffect("IntMSPDDelay", this))
	  if(ai_pTarget&&ObjectDistance(ai_pTarget)>100)
	    return DoConjurez(MSPD);
    }
    else
    {
      // Energieangriff
      if(!Random(5))
	if(!GetEffect("IntMGPHDelay", this))
	  if(ai_pTarget)
	    return DoConjurez(MGPH);
      // Schutz
      if(!Random(10))
	if(!GetEffect("IntMPRTDelay", this))
	  if(GetEnergy()<RandomX(15,25))
	    return DoConjurez(MPRT);
    }
  }
  
  UpdateMovement();
}

protected func FxBulkAIPalaStop(pTarget,iNum,iReas,fTemp)
{
  return FxBulkAIStop(pTarget,iNum,iReas,fTemp);
}

private func DoConjurez(id idWonder)
{
  //if (!AI_CanConjure(idWonder)) return;
  // Das Ziel anschauen, für alle gerichteten Zauber
  if (ai_pTarget) SetDir(GetX(ai_pTarget) > GetX());
  Call("DoMagic", idWonder);
  // Irgendwelche Nachrichten von Zaubern löschen
  Message(" ", this);
  return true;
}

// Magican-AI

public func SetMagicanAI(fHero)
{
  // Timer erstellen
  if (GetEffect("*AI", this)) return();
  return(AddEffect("BulkAIMagican", this, 1, 15, this, 0, fHero));
}

protected func FxBulkAIMagicanStart(pTarget,iNum,iTemp,fHero)
{
  if(iTemp) return 0;
  InitBulkAIPart(this,"Magican",fHero);
  ai_Way=Random(2);
  ai_IsBulkAI=true;
}

protected func FxBulkAIMagicanTimer()
{
  // Unstucken
  if(Stuck())
    return Schedule("SetPosition(GetX()+RandomX(-Random(2),Random(2)),GetY()-2)",2,10);
    
  if(!GetAlive(this)) return -1;
  
  //if(!Random(5))
  if((GetMagicEnergy()>20)&&this->~ReadyToMagic())
  {
    var enmysDistant=FindObjects(Sort_Distance(),Find_Hostile(GetOwner()),Find_OCF(OCF_Alive),Find_Distance(170),Find_NotHidden());
    var enmysNear=FindObjects(Sort_Distance(),Find_Hostile(GetOwner()),Find_OCF(OCF_Alive),Find_Distance(40),Find_NotHidden());
    var enmyCntD=GetLength(enmysDistant)-1;
    var enmyCntN=GetLength(enmysNear)-1;
    enmyCntD-=enmyCntN;
    var nearestEnmy=enmysNear[0];
    if(enmyCntD+enmyCntN>2)
    {
      SetAICommand("Wait",0,0,0,0,100);
      SetComDir(0);
      if(!nearestEnmy)
        nearestEnmy=enmysDistant[0];
      var minDist=9999;
      if(nearestEnmy)
        minDist=ObjectDistance(nearestEnmy);
      var frndsDistant=FindObjects(Sort_Distance(),Find_Not(Find_Hostile(GetOwner())),Find_OCF(OCF_Alive),Find_OCF(OCF_FightReady),Find_Distance(170));
      var frndsNear=FindObjects(Sort_Distance(),Find_Not(Find_Hostile(GetOwner())),Find_OCF(OCF_Alive),Find_OCF(OCF_FightReady),Find_Distance(40));
      var frndCntD=GetLength(frndsDistant);
      var frndCntN=GetLength(frndsNear);
      //var msg="";
      //msg=Format("%d+%d / %d+%d",enmyCntD,enmyCntN,frndCntD,frndCntN);
      
      // Viele Gegner in der Nähe
      if(Random(enmyCntN)>Random(5))
      {
        //msg=Format("%s|O",msg);
        // Eiswelle
        if(!Random(3))
          if(!Random(15+frndCntN*3-enmyCntN))
            if(CanMagicz(MFWV))
              return DoMagicz(MFWV);
        // Feuerfaust
        if(!Random(3))
          if(!Random(15+frndCntN*3-enmyCntN))
            if(CanMagicz(FRFS))
              return DoMagicz(FRFS);
        // Schutzzaps
        if(!Random(3))
          if(!Random(5))
            if(CanMagicz(GZ9Z))
              return DoMagicz(GZ9Z);
        // Ohnmacht
        if(!Random(3))
          if(!Random(5-enmyCntN/2))
            if(CanMagicz(MBOT))
              return DoMagicz(MBOT);
      }
      // Keine in der Nähe aber welche in der Ferne kommend?
      //if(!Random(7))
      if(enmyCntD>1&&!Random(enmyCntN*3))
      {
	//msg=Format("%s|-",msg);
	// Blutsauger
	if(!Random(3))
	  if(!Random(10-GetEnergy()/10))
	    if(CanMagicz(MBLS))
	      return DoMagicz(MBLS);
	// Eis/Feuerschlag
	if(!Random(5))
	  if(!Random(10-enmyCntD/2))
	    if(Random(2)&&CanMagicz(MICS))
	      return DoMagicz(MICS);
	    else if(CanMagicz(MFRB))
	      return DoMagicz(MFRB);
      }
      // Magische Kopien
      if(enmyCntN)
	if(!Random(5))
	  if(!Random(10-enmyCntD/2))
	    if(Random(2)&&CanMagicz(MICS))
	      return DoMagicz(MICS);
	    else if(CanMagicz(MFRB))
	      return DoMagicz(MFRB);
    }
  }
  if(GetCommand()ne"Wait")
    UpdateMovement();
}

protected func FxBulkAIMagicanStop(pTarget,iNum,iReas,fTemp)
{
  return FxBulkAIStop(pTarget,iNum,iReas,fTemp);
}

func CanMagicz(idSpell)
{
  //if(!GetPlrMagic(GetOwner(),idSpell))
  //  return 0;
  //if(!(this->~CheckMagicRequirements(idSpell)))
  //  return 0;
  if(!(this->~ReadyToMagic()))
     return 0;
  if(GetMagicEnergy()>Value(idSpell))
    return 1;
}

func DoMagicz(idSpell)
{
  if(CanMagicz(idSpell))
    return this->~SetMagicAction(idSpell);
}

public func DoSpellAim()
{
  if(IsAI())
    return 0;
  return _inherited(...);
}

public func DoSpellSelect()
{
  if(IsAI())
    return 0;
  return _inherited(...);
}

protected func FxBulkAIMagicanStop(pTarget,iNum,iReas,fTemp)
{
  return FxBulkAIStop(pTarget,iNum,iReas,fTemp);
}

private func IsBowEquipped() { return(_inherited()); }

public func UpdateMovement()
{
  BulkAIWayToWalk(this,ai_Param,ai_Mode,ai_Way,ai_pGeneral);
}

func InitBulkAIPart(pBulkPart,szSpecial,fHero)
{
  if(GameCall("InitBulkAIPart",pBulkPart,szSpecial)) return -1;
  // Physikals
  if(GetEffect("IntBulkArmyPart",pBulkPart))
    if(!fHero)
    {
      // Stärke=(45+verbesserungen)*standartwert/100
      var iStrength=45+g_aStrength[GetPlayerTeam(GetOwner(pBulkPart))];
      SetPhysical("Energy",GetPhysical("Energy",0,pBulkPart)*iStrength/100+FrameCounter()/5,PHYS_Temporary,pBulkPart);
      SetPhysical("Fight",GetPhysical("Fight",0,pBulkPart)*iStrength/100+FrameCounter()/4,PHYS_Temporary,pBulkPart);
      SetPhysical("Walk",GetPhysical("Walk",0,pBulkPart)*(iStrength+45)/100+FrameCounter()/4,PHYS_Temporary,pBulkPart);
    }
  SetPhysical("CanScale",1,PHYS_Temporary,pBulkPart);
  SetPhysical("CanHangle",1,PHYS_Temporary,pBulkPart);

  // Ausrüstung für Massen-KI

  // Zombies kriegen nichts
  if(GetID(pBulkPart)==_ZMB) return 0;

  // Ritter? Schild geben.
  if(pBulkPart->~IsKnight())
    if(Random(3))
      pBulkPart->CreateContents(SHIE)->Activate(pBulkPart);

  // Kanderianer? Ausrüsten.
  if(pBulkPart->~IsKanderian())
  {
    if(!Random(3))
      pBulkPart->CreateContents(SHI2)->Activate(pBulkPart);
    if(!Random(3))
    {
      if(pBulkPart->~CanUse(SCMT))
        pBulkPart->CreateContents(SCMT);
    }
    else if(!Random(2))
    {
      if(pBulkPart->~CanUse(AXE1))
        pBulkPart->CreateContents(AXE1);
    }
    else
    {
      if(pBulkPart->~CanUse(SPER))
        pBulkPart->CreateContents(SPER);
    }
  }

  // Waffen geben.
  if((!Random(5)||pBulkPart->~IsKnight())&&!pBulkPart->~IsKanderian())
  {
    if(!Random(2))
    {
      if(pBulkPart->~CanUse(SWOR))
        pBulkPart->CreateContents(SWOR);
    }
    else
    {
      if(pBulkPart->~CanUse(AXE1))
        pBulkPart->CreateContents(AXE1);
    }
  }

  if(pBulkPart->~IsJungleClonk())
    if(!Random(3))
      pBulkPart->CreateContents(SPR1);


  if(szSpecial eq "Bow")
  {
    pBulkPart->CreateContents(BOW1);
    pBulkPart->CreateContents(ARWP);
    if(!Random(3))
      pBulkPart->CreateContents(XARP);
    if(!Random(6))
      pBulkPart->CreateContents(FARP);
    if(!Random(6))
      pBulkPart->CreateContents(ARWP);
    return true;
  }

  if(szSpecial eq "Destroyer")
  {
    if(!Random(14))
      return pBulkPart->CreateContents(STFN);
    if(Random(3))
      return pBulkPart->CreateContents(SFLN);
    if(!Random(4))
      return pBulkPart->CreateContents(EFLN);
    return pBulkPart->CreateContents(FLNT);
  }

  if(Random(5))
    return pBulkPart->CreateContents(ROCK);
  if(!Random(2))
    return pBulkPart->CreateContents(FLNT);
  return pBulkPart->CreateContents(TFLN);
}

func BulkAIWayToWalk(pBulkPart,&Param,iMode,&iWay,pTarget)
{
  if(GetX(pBulkPart)>LandscapeWidth()-20)
    if(GetPlayerTeam(GetOwner(pBulkPart))!=2)
      if(TWRATKChangeLP(2,-1))
        return RemoveObject(pBulkPart);
  if(GetX(pBulkPart)<20)
    if(GetPlayerTeam(GetOwner(pBulkPart))!=1)
      if(TWRATKChangeLP(1,-1))
        return RemoveObject(pBulkPart);
  if(GameCall("HardcodetBulkAIMovement",pBulkPart,Param,iMode,iWay,pTarget)) return 1;
  if(!iMode)
    iMode=g_aArmyMode[GetOwner(pBulkPart)];

  // Angreifen
  if(iMode==TWRATK_Cmd_Attack)
  {
    if(GetProcedure(pBulkPart) S= "SCALE") return pBulkPart->SetComDir(COMD_Up);
    if(GetProcedure(pBulkPart) S= "HANGLE") return pBulkPart->SetAction("Walk");
    SetComDir(COMD_Right,pBulkPart);
    if(GetPlayerTeam(GetOwner(pBulkPart))==2)
      SetComDir(COMD_Left,pBulkPart);
  }
  // Aktuelle Position verteidigen
  else if(iMode==TWRATK_Cmd_Defend)
  {
    if(GetProcedure(pBulkPart) S= "SCALE") return pBulkPart->SetComDir(COMD_Up);
    if(GetProcedure(pBulkPart) S= "HANGLE") return pBulkPart->SetAction("Walk");
    if(!Random(5))
      SetComDir(COMD_None,pBulkPart);
  }
  // FLUCHT!!!!111
  else if(iMode==TWRATK_Cmd_Retreat)
  {
    if(GetProcedure(pBulkPart) S= "SCALE") return pBulkPart->SetComDir(COMD_Up);
    if(GetProcedure(pBulkPart) S= "HANGLE") return pBulkPart->SetAction("Walk");
    if(GetPlayerTeam(GetOwner(pBulkPart))==1)
    {
      if(GetX(pBulkPart)>LandscapeWidth()/4)
        SetComDir(COMD_Left,pBulkPart);
      else if(!Random(40))
        SetComDir(COMD_None,pBulkPart);
    }
    else
    {
      if(GetX(pBulkPart)<LandscapeWidth()-LandscapeWidth()/4)
        SetComDir(COMD_Right,pBulkPart);
      else if(!Random(40))
        SetComDir(COMD_None,pBulkPart);
    }
  }
  // Folgen
  else if(iMode==TWRATK_Cmd_Follow)
  {
    var pCursor = GetCursor(GetOwner(pBulkPart));
    if(pTarget)
      pCursor=pTarget;
    iWay=GameCall("GetWay",pCursor);

    if(ObjectDistance(pCursor,pBulkPart)<Param)
    {
      if(GetAction(pCursor)S="Pray"){ if(!Random(20)) pBulkPart->SetAction("Pray");}
      else { if(GetAction(pBulkPart)S="Pray") pBulkPart->SetAction("KneelUp");}
      if(!GetCommand(pBulkPart)) return pBulkPart->SetComDir(COMD_None);
      return 0;
    }

    if(iWay!=GameCall("GetWay",pBulkPart)) return SetCommand(pBulkPart,"MoveTo",pCursor);

    if(GetProcedure(pBulkPart) S= "SCALE") return pBulkPart->SetComDir(COMD_Up);
    if(GetProcedure(pBulkPart) S= "HANGLE") return pBulkPart->SetAction("Walk");

    if(Param==0) Param = RandomX(20,100);
    if(!Random(10000)) Param = RandomX(20,100);

    if(Random(3)) return 0;

    SetComDir(COMD_Right,pBulkPart);
    if(GetX(pBulkPart)>GetX(pCursor))
      SetComDir(COMD_Left,pBulkPart);

    ClearScheduleCall(pBulkPart,"UpdateMovement");
    ScheduleCall(pBulkPart,"UpdateMovement",5+Random(2));
  }

  // Wenn nichts zu tun ist, beten oder �hnliche Dinge tuen
  if(!GetCommand(pBulkPart)&&GetComDir(pBulkPart)==COMD_None)
    if(pBulkPart->~IsPaladin()||pBulkPart->~IsPriest())
      if(GetAction(pBulkPart)ne"Pray")
        if(!Random(20))
          pBulkPart->SetAction("Pray");
  return 0;
}
