#include "AirThreat.h"
#include "TCC.h"
#include "UDPSocket.h"

queue<string>& AirThreat::getMsgQueue()
{
	return mQueue;
}

void AirThreat::launch()
{
	while (atsState == State::OPERATION)
	{
		Tracking tracking;
		atsCurPos = tracking.track(targetPos);

		// UDP�� current position�� ��������
		//udpSend.setATSCurPos(atsCurPos);
		//udpSend.setMsgQueue(&mQueue);
	}
}

void AirThreat::setInitPos(Position initpos, Position targetpos)
{
	initPos = initpos;
	targetPos = targetpos;
}


int main()
{
	AirThreat at;
	TCC tcc = TCC("127.0.0.1", 5000);
	UDPSocket udp = UDPSocket(tcc, &at.getMsgQueue());

	//udp.setATSCurPos({ 1,2 });
}

