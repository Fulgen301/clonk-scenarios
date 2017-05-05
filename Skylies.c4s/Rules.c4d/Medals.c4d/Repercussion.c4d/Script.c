/*-- Medaille --*/

#strict 2

func IsMedal() {return true;}
func MedalEntry() {return 1;}
func MedalIndex() {return 6;}


func OnClonkRepercussion(object pClonk, int iPlr)
{
  if(GetYDir(pClonk) < 0) // Richtige Richtung?
  {
    if((LandscapeHeight()-GetY(pClonk)) < 150) // Tief genug?
    {
      if(GetMagicEnergy(pClonk)) // Aha! Das muss ein Magier sein.
      {
        if(GetAction (pClonk) == "Tumble") // Mh.. du taumelst also?
        {
          Reward(this(),iPlr); // Okay kannst haben
        }
      }
      
      else // Aha! du bist zmd doof. Du musst nicht taumeln!
      {
        Reward(this(),iPlr); // Okay kannst haben
      }
    }
  }
}
