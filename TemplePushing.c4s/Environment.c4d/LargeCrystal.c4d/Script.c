/*-- Groﬂer Kristall --*/

#strict 2

protected func Initialize() 
{
 var rand=1;
 if(Random(2) == 1)rand=-1;
 SetObjDrawTransform(1000*rand,0,0,0,1000);
}

protected func Activity()
{
	var cnt;
	cnt=5;
    while(cnt--) CreateParticle("MaterialSpark", GetX(this)-GetX()+Random(13)-6, GetY(this)-GetY()+RandomX(11),0,-1-Random(2),40,0x1f7fff);
}

public func Activate()
{
	return SetAction("Active");
}

func IsDecorativeCrystal() { return true; }
