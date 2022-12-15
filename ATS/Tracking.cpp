#include "Tracking.h"

void Tracking::setATSCurPos(Position pos)
{
	this->atsCurPos = pos;
}

Position Tracking::track(State state, Position atsNextPos, Position targetPos)
{
	double a = (targetPos.y - atsNextPos.y) / (targetPos.x - atsNextPos.x);
	double b = (targetPos.x * atsNextPos.y - atsNextPos.x * targetPos.y) / (targetPos.x - atsNextPos.x);
	
	if ((atsNextPos.y == targetPos.y) && (atsNextPos.x == targetPos.x))
	{
		state = State::DONE;
	}
	else if (state == State::PAUSE)
	{
		return { atsNextPos.x, atsNextPos.y };
	}
	atsNextPos.x += 1;
	atsNextPos.y = (a * atsNextPos.x) + b;

	this->setATSCurPos({atsNextPos.x, atsNextPos.y});

	return this->getATSCurPos();
}

Position Tracking::getATSCurPos()
{
	return atsCurPos;
}

Position Tracking::getNextATSCurPos()
{
	return atsNextPos;
}
