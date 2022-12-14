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

		// UDP()�ε� ��������
	}
}

void AirThreat::setInitPos(Position initpos, Position targetpos)
{
	initPos = initpos;
	targetPos = targetpos;
}
