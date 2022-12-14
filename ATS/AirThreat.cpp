#include "AirThreat.h"
#include "Tracking.h"

void AirThreat::track()
{
	Tracking t;
	t.track(targetPos);
}

Position AirThreat::getATSCurPos()
{
	return atsCurPos;
}
