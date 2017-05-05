/*-- Shop --*/

// einkaufen ahoi v1.1 by miniwipf
#strict 2

local _aOrder;

protected func ActivateEntrance(object pCustomer)
{
	ShopMenu(pCustomer);
	// Und jetzt nerv nicht weiter
  FinishCommand(pCustomer, 1);
	return 0;
}

/* OPTIONS */

public func SetOrder(array aOrder)
{
	_aOrder = aOrder;
	return 1;
}

public func SetMenuClonk(object pClonk)
{
	return SetAction("Attach", pClonk);
}

public func GetMenuClonk()
{
	return GetActionTarget();
}

public func AddItems(id idItem, int iNr)
{
	var obj;
	while (iNr--) {
		obj = CreateContents(idItem);
		// Schriftrollen und Zauberbücher mit Zaubern belegen
		if (idItem == SCRL || idItem == BOOK) obj -> SetSpells();
	}
	return 1;
}

/* Spezifisch */

private func Text(id idClonk, int iIndex)
{
	if (idClonk == KING) {
		if (iIndex == 0) return "$MnuKingShopInfo$";
		if (iIndex == 1) return "$MnuKingShopYes$";
		if (iIndex == 2) return "$MnuKingShopNo$";
	}
	if (idClonk == SCLK) {
		if (iIndex == 0) return "$MnuScorcerShopInfo$";
		if (iIndex == 1) return "$MnuScorcerShopYes$";
		if (iIndex == 2) return "$MnuScorcerShopNo$";
	}
	if (idClonk == KNIG) {
		if (iIndex == 0) return "$MnuKnightShopInfo$";
		if (iIndex == 1) return "$MnuKnightShopYes$";
		if (iIndex == 2) return "$MnuKnightShopNo$";
	}
}

/* SHOPMENüS */

private func ShopMenu(object pCustomer)
{
	var clonk = GetMenuClonk(), ID = GetID(clonk);
	var pos;
	// Shopmenü
	pCustomer -> AddMenu(SHOP, this, RSR1, "");
	pCustomer -> SetMenuStyle(SHOP, 3);
	//pCustomer -> SetMenuDecoration2(SHOP, MD69);
		// Einträge
		pos = (pCustomer->AddMenuEntry(SHOP, ICON, 0,,, Format("Portrait:%i::%x::%d", ID, GetColorDw(clonk), 1))); pCustomer -> SetMenuEntryExtra(SHOP, pos, 5);
		pCustomer -> AddMenuEntry(SHOP, INFO, 1,,, Text(ID));
		pos = (pCustomer->AddMenuEntry(SHOP, YES_, 2, "On_SHOP_MenuChoice", XMEN, Text(ID, 1), "")); pCustomer -> SetMenuEntryExtra(SHOP, pos, 2, 0);
		pos = (pCustomer->AddMenuEntry(SHOP, NO__, 3, "On_SHOP_MenuChoice", XMEN, Text(ID, 2), "")); pCustomer -> SetMenuEntryExtra(SHOP, pos, 2, 1);

	// Itemmenü
	/*pCustomer -> AddMenu(BUYM, this, RSR1, "");
	pCustomer -> SetMenuExtra(BUYM, 2);
	pCustomer -> SetMenuParent(BUYM, SHOP);
	pCustomer -> SetMenuStyle(BUYM, 3);
	pCustomer -> SetMenuDecoration2(BUYM, MD69);
		// Einträge
		for (var i=ContentsCount()-1, obj; i; i--) {
			obj = Contents(i);
			pos = (pCustomer->AddMenuEntry(BUYM, GetID(obj), -1, "On_BUYM_MenuChoice", GetID(obj), GetName(obj)));
			pCustomer -> SetMenuEntryExtra(BUYM, pos, 4, obj);
		}*/
	// Anzeigen
	pCustomer -> OpenMenu(SHOP);
}

private func ItemMenu(object pCustomer, int iSel)
{
	CloseMenu(pCustomer);
	CreateMenu(GetID(GetMenuClonk()), pCustomer, this, 2,,, 1, 1, BUYM);
	//SetMenuDecoration(MD69, pCustomer);
	// Einträge sortiert im Menü einordnen
	for (var i, ID, n; i < GetLength(_aOrder); i++) {
		ID = _aOrder[i];
		if (GetType(_aOrder[i+1]) == C4V_Int) {
			++i; // Anzahl überspringen
			continue;
		}
		for (var obj in FindObjects(Find_ID(ID), Find_Container(this))) {
			AddMenuItem(GetName(obj), Format("On_BUYM_MenuChoice(Object(%d), Object(%d))", ObjectNumber(obj), ObjectNumber(pCustomer)), GetID(obj), pCustomer,,,, 4, obj);
			n++;
		}
	}
	// Eintrag anwählen
	if (iSel) {
		if (iSel >= n) iSel = n-1;
		SelectMenuItem(iSel, pCustomer);
	}
	return 1;
}

private func On_SHOP_MenuChoice(int iEntryNr, int iMode, object pMenuObj)
{
	if (!iMode) return;
	var idEntry = pMenuObj->M_EntryID(SHOP, iEntryNr);
	var plr = GetOwner(pMenuObj);
	if (iMode < 0 || idEntry == NO__) {
		Sound("ControlRate", 1,,, plr+1);
		return pMenuObj -> RemoveMenu(SHOP);
	}
	// Auswahl
	Sound("ArrowHit", 1,,, plr+1);
	pMenuObj -> RemoveMenu(SHOP);
	ItemMenu(pMenuObj);
	return 1;
}

private func On_BUYM_MenuChoice(object pObj, object pCustomer)
{
	// Kaufen
	BuyItem(pObj, pCustomer);
	// Menü neu erzeugen
	ItemMenu(pCustomer, GetMenuSelection(pCustomer));
	return 1;
}

public func BuyItem(object pObj, object pBuyer)
{
	var plr = GetOwner(pBuyer);
	// Nicht genug Geld
	var val = GetValue(pObj);
	if (GetWealth(plr) < val) {
		Sound("Error",, pBuyer,, plr+1);
		PlayerMessage(plr, "Nicht genug Geld!", pBuyer);
		return;
	}
	// Nicht genug Platz im Inventar
	if (pBuyer->RejectCollect(GetID(pObj), pObj)) {
		Sound("Error",, pBuyer,, plr+1);
		PlayerMessage(plr, "Inventar voll!", pBuyer);
		return;
	}
	// endlich kaufen!!!
	Sound("Cash",, pBuyer,, plr+1);
	DoWealth(plr, -GetValue(pObj));
	Enter(pBuyer, pObj);
	// Nachliefern
	AddEffect("ShopDelivery", this, 200, 35*val, this,, GetID(pObj));
	return 1;
}

// Effekt

private func FxShopDeliveryStart(object pTarget, int iNr, int iTemp, id idDef)
{
	if (iTemp) return;
	// Was?
	EffectVar(0, pTarget, iNr) = idDef;
	return 1;
}

private func FxShopDeliveryStop(object pTarget, int iNr, int iReason, bool fTemp)
{
	if (fTemp) return;
	// So jetzt nachliefern
	var ID = EffectVar(0, pTarget, iNr);
	pTarget -> AddItems(ID, 1);

	// Noch ne Meldung über dem Clonk
	var clonk = pTarget->GetMenuClonk();
	CastMsg(Format("$MsgItemDelivered$", ID), clonk, 0xffffff);
	return 1;
}
