#strict 2

global func FindObjects(noOverload)
{
	if (GetType(noOverload) == C4V_Bool) return _inherited(...);
	else return _inherited(Find_Layer(GetObjectLayer()), noOverload, ...);
}

global func FindObjectsAllLayers()
{
	return FindObjects(true, ...);
}

global func FindObject2(noOverload)
{
	if (GetType(noOverload) == C4V_Bool) return _inherited(...);
	else return _inherited(Find_Layer(GetObjectLayer()), noOverload, ...);
}

global func FindObject2AllLayers()
{
	return FindObject2(true, ...);
}

global func FindObject(a, b, c, d, e, f, g, h, i, object findNext)
{
	var ret = findNext, layer = GetObjectLayer();
	for (;;)
	{
		ret = _inherited(a, b, c, d, e, f, g, h, i, ret);
		if (!ret || ret->GetObjectLayer() == layer) return ret;
	}
}

global func FindObjectOwner(a, b, c, d, e, f, g, h, i, object findNext)
{
	var ret = findNext, layer = GetObjectLayer();
	for (;;)
	{
		ret = _inherited(a, b, c, d, e, f, g, h, i, ret);
		if (!ret || ret->GetObjectLayer() == layer) return ret;
	}
}
