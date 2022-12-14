#include "AirThreat.h"

void AirThreat::launch()
{
	while (atsState == State::OPERATION)
	{
		Tracking tracking;
		atsCurPos = tracking.track(targetPos);

		// UDP�� current position�� ��������
		udpSend.setATSCurPos(atsCurPos);
	}
}

void AirThreat::setInitPos(Position initpos, Position targetpos)
{
	initPos = initpos;
	targetPos = targetpos;
}
