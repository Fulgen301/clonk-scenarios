/*-- Snowball --*/

#strict 2

#include ICE1
#include SNWB

protected func Departure(object container)
{
	// Throw only if the container was a clonk
	if (!(container->GetOCF() & OCF_CrewMember)) return 1;
}
