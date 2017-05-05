/*-- Neues Objekt --*/

#strict

global func IsHardcoreMod(){ if(FindObject(HCOR)) return(1); }

func Initialize(){
 //SetSkyAdjust(RGBa(205,50,55), RGB(255,0,155));

 Sound("MagicElementEarth",1);
 Sound("MagicElementAir",1);
 ShowMessage("Absofort wird im <c ffcccc>Hardcore</c>-Modus gespielt!");
  return(1);
}
func Check() {
  for(var i=0; i<GetPlayerCount(); i++)
  {
  var iPlr = GetPlayerByIndex(i);
  SetWealth(iPlr,GetWealth(iPlr)+1);
  if(!Random(100)) {
  if(GetHomebaseMaterial(iPlr,FLNT) < 20) DoHomebaseMaterial(iPlr,FLNT,1);
  if(GetHomebaseMaterial(iPlr,SFLN) < 10) DoHomebaseMaterial(iPlr,SFLN,1);
  if(GetHomebaseMaterial(iPlr,EFLN) < 5) DoHomebaseMaterial(iPlr,EFLN,1);
  if(GetHomebaseMaterial(iPlr,TFLN) < 20) DoHomebaseMaterial(iPlr,TFLN,1);
  if(GetHomebaseMaterial(iPlr,STFN) < 10) DoHomebaseMaterial(iPlr,STFN,1);
  if(GetHomebaseMaterial(iPlr,HTBM) < 10) DoHomebaseMaterial(iPlr,HTBM,1);
  if(GetHomebaseMaterial(iPlr,_MBM) < 10) DoHomebaseMaterial(iPlr,_MBM,1);
  if(GetHomebaseMaterial(iPlr,GUNP) < 20) DoHomebaseMaterial(iPlr,GUNP,1);
  if(GetHomebaseMaterial(iPlr,GNBR) < 10) DoHomebaseMaterial(iPlr,GNBR,1);
  if(GetHomebaseMaterial(iPlr,BLND) < 7) DoHomebaseMaterial(iPlr,BLND,1);

  if(GetHomebaseMaterial(iPlr,ROCK) < 20) DoHomebaseMaterial(iPlr,ROCK,1);
  if(GetHomebaseMaterial(iPlr,METL) < 5) DoHomebaseMaterial(iPlr,METL,1);
  if(GetHomebaseMaterial(iPlr,WOOD) < 10) DoHomebaseMaterial(iPlr,WOOD,1);
  if(GetHomebaseMaterial(iPlr,LOAM) < 5) DoHomebaseMaterial(iPlr,LOAM,1);

  if(GetHomebaseMaterial(iPlr,CATA) < 1) DoHomebaseMaterial(iPlr,CATA,1);
  if(GetHomebaseMaterial(iPlr,CANN) < 1) DoHomebaseMaterial(iPlr,CANN,1);
  if(GetHomebaseMaterial(iPlr,XBOW) < 1) DoHomebaseMaterial(iPlr,XBOW,1);

  if(GetHomebaseMaterial(iPlr,ARWP) < 20) DoHomebaseMaterial(iPlr,ARWP,1);
  if(GetHomebaseMaterial(iPlr,FARP) < 10) DoHomebaseMaterial(iPlr,FARP,1);
  if(GetHomebaseMaterial(iPlr,XARP) < 3) DoHomebaseMaterial(iPlr,XARP,1);
  if(GetHomebaseMaterial(iPlr,MARP) < 5) DoHomebaseMaterial(iPlr,MARP,1);

  if(SeaAddon){
  if(GetHomebaseMaterial(iPlr,BH5P) < 5) DoHomebaseMaterial(iPlr,BH5P,1);
  if(GetHomebaseMaterial(iPlr,BJ5P) < 3) DoHomebaseMaterial(iPlr,BJ5P,1);
  if(GetHomebaseMaterial(iPlr,BJ5P) < 7) DoHomebaseMaterial(iPlr,TRP1,1);
  if(GetHomebaseMaterial(iPlr,BJ5P) < 2) DoHomebaseMaterial(iPlr,SLBT,1);
              }
   }
  }
  var pObj;
  while(pObj=FindObject(0,0,0,0,0,OCF_CrewMember(), 0,0,0,pObj)) {
  /* Known as Hardcoreeffect. */
  if(!GetEffect("ControlHardcore",pObj))
  AddEffect("ControlHardcore",pObj,100,0,this);

    if(GetPhysical("Magic", 0, pObj)) {
     if(!Random(8)) DoMagicEnergy(+1, pObj);
      }
     }


  return(1);
}
/*global func FxControlHardcoreControlThrow(object pTarget)
{
  var pCannon = GetActionTarget(0,pTarget);
  if(GetAction(pTarget) == "Push"){
    if(GetID(pCannon) == CANN) {
      if(FindOtherContents(GUNP,pCannon)){
        if(!Contents(0,pTarget)) {
          CreateContents(GUNP,pCannon);
     }
    }
   }
  }
  AddEffect("Cooldown",pTarget,100,20);
  return (false);
}

func OnClonkCreation(object pClonk)
{
  AddEffect("ControlHardcore",pClonk,100,0,this);
  return ("Java ist doof");
}   */