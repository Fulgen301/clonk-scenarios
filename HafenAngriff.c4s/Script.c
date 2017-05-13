/*-- Hafen Angriff --*/

#strict 2

func Initialize() {
   
  return ScriptGo(true);
}


func InitializePlayer(int iPlr){
             Local(0,GetCrew(iPlr))=25;  //Beim ersten mal nicht warten weil ist langweilig 
                               }

func OnClonkCreation(object pClonk){

     //Waffen sind toll
     GiveWeapons(pClonk);
     if(GetPlayerTeam(GetOwner(pClonk))==2){GiveExplosivs(pClonk);Local(0,pClonk)=10;}
     
     //Erster Beitritt des Spielers?
     if(Global(GetOwner(pClonk))){
            JoinClonk(pClonk);
            return 1;
                     }
     
     //Spieler warten lassen 
     for(var n in FindObjects(Find_ID(HEP_)))
             if(LocalN("Number",n)==GetPlayerTeam(GetOwner(pClonk)))
                             pClonk->Enter(n);
     AddEffect("Waiting",pClonk,43,36,pClonk);
     
     return 2;
}

global func FxWaitingTimer(object pClonk){
                     Local(0,pClonk)++;
                     if(Local(0,pClonk)>25){
                                  pClonk->Exit();
                                  JoinClonk(pClonk);
                                  return -1;
                                           }
                     PlayerMessage(GetOwner(pClonk),"Respawn in %d Sekunden",0,26-Local(0,pClonk));
                     
                                         } 

func GiveWeapons(object pClonk){
            CreateContents(WINC,pClonk);
            CreateContents(AMBO,pClonk);
                               }

func GiveExplosivs(object pClonk){
            CreateContents(DYNB,pClonk);
            CreateContents(IGNB,pClonk);
                                 }

//Der Clonk hat genug gewarted
global func JoinClonk(object pClonk){
               

               var Huts,Ships;
               Huts=FindObjects(Find_ID(HUT2));
               Ships=FindObjects(Find_Func("IsShip"));
               
               var shipx,shipy,i;
               i=Random(GetLength(Ships));
               shipx=GetX(Ships[i]);
               shipy=GetY(Ships[i])-40;
               

               //Prüfen ob er noch joinen kann
               if(GetPlayerTeam(GetOwner(pClonk))==1){
                                     if(!FindObject2(Find_ID(HUT2)))DestroyPlayer(GetOwner(pClonk));
                                     else pClonk->Enter(Huts[Random(GetLength(Huts))]);
                                                     }
               
               if(GetPlayerTeam(GetOwner(pClonk))==2){
                                     if(!FindObject2(Find_Func("IsShip")))DestroyPlayer(GetOwner(pClonk));
                                     else pClonk->SetPosition(shipx,shipy);
                                                     }
               
               
                              }
                              
func RelaunchPlayer(int iPlr){
         var clonk;
         MakeCrewMember(clonk=CreateObject(COWB,0,0,iPlr),iPlr);
         SetCursor(iPlr,clonk);
         CheckRespawn(iPlr);
                             }
                             
global func DestroyPlayer(int iPlr){
RemoveObject(GetCrew(iPlr));
EliminatePlayer(iPlr);
}

//Kann der Spieler noch Respawn
global func CheckRespawn(iPlr){
       if(GetPlayerTeam(iPlr)==1){
                               if(!FindObject2(Find_ID(HUT2)))DestroyPlayer(iPlr);}
       if(GetPlayerTeam(iPlr)==2){
                               if(!FindObject2(Find_Func("IsShip")))DestroyPlayer(iPlr);}
      
}

func Script100(){

    var items=[CC5P,CC5P,CC5P,CD5P,CD5P,CJ5P];

    for(var n in FindObjects(Find_ID(HUT2))){
                   n->CreateContents(GUNP);
                   n->CreateContents(items[Random(6)]);}
}
