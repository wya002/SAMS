#include "AirThreat.h"
#include "TCC.h"
#include "UDPSocket.h"

queue<string>& AirThreat::getMsgQueue()
{
	return mQueue;
}

void AirThreat::launch()
{
	while (atsState == State::START)
	{
		track.track(atsState, this->atsCurPos, targetPos);
		this->setATSCurPos(track.getATSCurPos());
		std::cout << track.getATSCurPos().x << ", " << track.getATSCurPos().y << std::endl;
		break;		// ��� ������ ���� ���Ҵ�.
		// UDP�� current position�� ��������
		//udpSend.setATSCurPos(atsCurPos);
	}
}

void AirThreat::setInitPos(Position initpos, Position targetpos)
{
	initPos = initpos;
	targetPos = targetpos;
}

void AirThreat::setATSCurPos(Position pos)
{
	this->atsCurPos = pos;
}

void AirThreat::setState()
{
	atsState = State::START;
}

State AirThreat::getState()
{
	return atsState;
}
