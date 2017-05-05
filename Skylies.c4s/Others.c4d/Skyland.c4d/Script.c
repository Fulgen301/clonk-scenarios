/*-- Himmelsinsel --*/

#strict 2

static const SKYL_ALPHA = 100;
static const SKYL_NORMAL = 0xffffff;
static const SKYL_BROKEN = 0xaaaaaa;
static const SKYL_PARA = 70;

func Initialize() 
{
  Local(0) = SKYL_PARA;
  Local(1) = SKYL_PARA;

  var iClr;
  if(GetEffect("Broken",this)) iClr = SKYL_BROKEN;
  else                         iClr = SKYL_NORMAL;

  SetGraphics(Format("%d",Random(3)),this,GetID(this));
  SetClrModulation(iClr|(SKYL_ALPHA<<24),this);

  if(ScriptCounter() < 500)
    SetField(true);
  return true;
}

func SetField(bool fStatus)
{
  var iClr, iAlpha;
  if(GetEffect("Broken",this)) iClr = SKYL_BROKEN;
  else                         iClr = SKYL_NORMAL;

  if(fStatus) iAlpha = SKYL_ALPHA;
  else        iAlpha = 255;

  SetGraphics("Field",this,GetID(this),1,GFXOV_MODE_Base);
  SetClrModulation(iClr|(iAlpha<<24),this,1);
  SetObjDrawTransform(1000,0,0,0,1000,-20000,this,1);

  SetObjDrawTransform(1000,0,10000,0,1000,0,this,0);
  return true;
}

func Breakdown()
{
  SetField(false);
  
  SetCategory(C4D_Vehicle|C4D_Background|C4D_Environment|C4D_Parallax,this);
  SetRDir(Random(10)-5,this);
  SetClrModulation(SKYL_BROKEN|(SKYL_ALPHA<<24),this);
  AddEffect("Broken",this,100,0);
  Sound("SkylandBreakdown",false,this,30);
  return true;
}

func ForceFieldRemove()
{
  SetField(false);
  AddEffect("Impact",this,100,10,this);
  return true;
}

func FxImpactTimer(object pTarget, int iIndex, int iTime)
{
  if(Random(30)) return true;
  
  CreateParticle("Skyland_Blast",Random(100)-50,Random(60)-30,0,0,Random(75)+25,0xffffff,this,false);
  
  if(!Random(100)) Breakdown();
  
  return true;
}

global func PlaceDekoSkylands(int iAmount, int iDiff, int iAbort)
{
  if(!iAbort) iAbort = 100;
  var iCount = 0;

  for(var i=0; i<iAmount && iCount <= iAbort; i++)
  {
    var iX = Random(LandscapeWidth()-200)+100;
    var iY = Random(LandscapeHeight()-200)+100;

    if(FindObject2(Find_ID(SL0D),Find_Distance(iDiff,iX,iY)))
    {
      i--;
      iCount++;
      continue;
    }
    CreateObject(SL0D,iX,iY,NO_OWNER); 
  }

}
