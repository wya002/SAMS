#pragma once
#include "Position.h"
#include <iostream>

class Tracking
{
public:
	void setATSCurPos(Position pos);
	Position track(State state, Position atsNextPos, Position targetPos);
	Position getATSCurPos();
	Position getNextATSCurPos();
private:
	Position atsCurPos;
	Position atsNextPos;
};
