/*-- Zauberer --*/

#strict 2
#appendto SCLK

private func ConvertCrystal(object pObj)
  {
    GameCallEx("OnCrystalConvert",this);
    return(_inherited(Par(), Par(1)));
  }