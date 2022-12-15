#include "AirThreat.h"
#include "TCC.h"
#include <thread>

queue<string>& AirThreat::getMsgQueue()
{
	return mQueue;
}

void AirThreat::launch()
{
	while (true)
	{
		if (atsState == State::START) 
		{
			track.track(atsState, this->atsCurPos, targetPos);
			this->setATSCurPos(track.getATSCurPos());
			//std::cout << track.getATSCurPos().x << ", " << track.getATSCurPos().y << std::endl;

			mQueue.push("MP:" + to_string(track.getATSCurPos().x) + to_string(track.getATSCurPos().y));

			this_thread::sleep_for(500ms);
		}
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

void AirThreat::setState(State state)
{
	atsState = state;
}

State AirThreat::getState()
{
	return atsState;
}
