/*-- Neues Objekt --*/

#strict

func Initialize() {
   
  return(1);
}
public func Check() {
 
 var stText;
 var r;
 var g;
 var b;
 var i = ScriptCounter();
 
 r = i/2;
 g = 255-(i/2);
 b = 0;
 
 if(Inside(i,0,100)) stText = ".....";
 if(Inside(i,100,200)) stText = "....";
 if(Inside(i,200,300)) stText = "...";
 if(Inside(i,300,400)) stText = "..";   
 if(Inside(i,400,500)) stText = "!"; 
  for(var pObj in FindObjects(Find_ID(FRCA) ))
  {
    Message("<c %x>%s</c>",pObj,RGB(r,g,b),stText);
  }
 if(i >= 500) RemoveObject();  
  return(1);
}
