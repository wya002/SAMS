#include "AirThreat.h"
#include "Tracking.h"

Position AirThreat::getATSCurPos()
{
	return atsCurPos;
}

void AirThreat::launch()
{
	while (ATSstate == State::OPERATION)
	{
		Tracking tracking;
		atsCurPos = tracking.track(targetPos);

		// UDP()로도 보내야함
	}
}

void AirThreat::setInitPos(Position initpos, Position targetpos)
{
	initPos = initpos;
	targetPos = targetpos;
}
