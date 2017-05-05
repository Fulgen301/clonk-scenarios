/*-- Medaille --*/

#strict 2

local aDeaths;

func IsMedal() {return true;}
func MedalEntry() {return 0;}
func MedalIndex() {return 15;}

// Teile vom Script stehen in Medal_Melee.c

func Initialize()
{
  aDeaths = [];
  return true;
}

func OnClonkDeath(object pClonk)
{
  if(GetOwner(pClonk) == NO_OWNER) return false;
  aDeaths[GetOwner(pClonk)]++;
  return true;
}

//FindObject(SA_M) -> Fulfil()

func MedalFulfil()
{
  //Das Spiel ist vorbei? Dann gibt es ja keine verfeindeten Spieler mehr. Alle durchgehn.
  for(var i=0; i<GetPlayerCount(); i++)
    if(!aDeaths[GetPlayerByIndex(i)])
      Reward(this,GetPlayerByIndex(i));
  return true;
}
