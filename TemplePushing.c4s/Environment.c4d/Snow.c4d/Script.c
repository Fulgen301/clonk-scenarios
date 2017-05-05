/*-- Snow effect --*/

#strict

protected func Initialize() {
  if(!IsNewgfx()) RemoveObject();
  SetPosition(0,0);
}

func Snowing() {
  for(var x; x<4; x++) 
  {
    CreateParticle("Snow2",Random(LandscapeWidth()),0,0,25,RandomX(5,15),0);
    CreateParticle("Snow2",Random(LandscapeWidth()),0,0,21,RandomX(10,20),0);
    CreateParticle("Snow2",Random(LandscapeWidth()),0,0,17,RandomX(15,25),0);
    CreateParticle("Snow2",Random(LandscapeWidth()),0,0,35,RandomX(20,30),0);
  }
}
  
