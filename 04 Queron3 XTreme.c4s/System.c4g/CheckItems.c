#strict 2

//Sorgt dafür, dass unbenötigte Items nicht vorhanden sind


static no_ASAS, no_PLDN, no_KAND, no_MAGE;
//static const funktioniert nicht mit Arrays...

global func CheckItems(array &aItems)
{
  if (!no_ASAS)
  {
    //Wurfmesser, Keule, Armbrust, Bolzen, Enterhaken
    no_ASAS = [TKNP, CLUB, CRBW, BOTP, NBTP, SBTP, HOOK];
    //Zweihänder, Muskete, Kugeln
    no_PLDN = [TSWD, MUSK, BLTP, SBLP, PBLP];
    //Krummschwert, Schild
    no_KAND = [SCMT, SHI2];
    //Stab von CKZ
    no_MAGE = [SCKZ];
  }

  //Im ersten Frame erstmal gar nichts tun, alle Truhen füllen sich gerade
  if (!FrameCounter())
    return;

  //Dann mal schauen welche Items unnötig sind
  var a = [];
  //Kein Assa
  if (GetIndexOf(ASAS, g_aClonksOnRelaunch) == -1)
    a = CombineArrays(a, no_ASAS);
  //Kein Paladin
  if (GetIndexOf(PLDN, g_aClonksOnRelaunch) == -1)
    a = CombineArrays(a, no_PLDN);
  //Kein Kanderianer
  if (GetIndexOf(KAND, g_aClonksOnRelaunch) == -1)
    a = CombineArrays(a, no_KAND);
  //Kein Magus
  if (GetIndexOf(MAGE, g_aClonksOnRelaunch) == -1)
    a = CombineArrays(a, no_MAGE);

  //Kein Array da - d.h. Truhen und Shops durchgehen und Items rauswerfen
  if (!aItems)
  {
    var obj, chest;
    for (chest in FindObjects(Find_Or(Find_ID(CHST), Find_ID(STRE))))
      for (obj in FindObjects(Find_Container(chest)))
        if (GetIndexOf(GetID(obj), a) != -1)
          RemoveObject(obj);
    return true;
  }
  //Sonst will eine Truhe gerade spawnen und wüsste gern, was rein darf
  else
    for (var item in a)
      RemoveItem(item, aItems);
  return aItems;
}

global func RemoveItem(item, array &a)
{
  var i = GetIndexOf(item, a), l = GetLength(a);
  if (i == -1)
    return false;
  for (; i < l - 1; i++)
    a[i] = a[i + 1];
  SetLength(a, l - 1);
  return true;
}

global func CombineArrays(array a1, array a2)
{
  for (var i; i < GetLength(a2); i++)
    if (GetIndexOf(a2[i], a1) == -1)
      a1[GetLength(a1)] = a2[i];
  return a1;
}