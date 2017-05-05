/* Bunker */

#strict

func SoundOpenDoor()
{
  Sound("BK_DoorOpen");
}

func SoundCloseDoor()
{
  Sound("BK_DoorClose");
}

func EjectStuff()
{
  while (Contents())
  {
    Exit(Contents(), 8, 15);
  }
}

func Collection2()
{
  SetAction("OpenDoor");
}