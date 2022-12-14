#include "AirThreat.h"

void AirThreat::launch()
{
	while (atsState == State::OPERATION)
	{
		Tracking tracking;
		atsCurPos = tracking.track(targetPos);

		// UDP로 current position을 보내야함
		udpSend.setATSCurPos(atsCurPos);
	}
}

void AirThreat::setInitPos(Position initpos, Position targetpos)
{
	initPos = initpos;
	targetPos = targetpos;
}
