#pragma once
#include "Position.h"
#include "Tracking.h"

enum class State {
	STBY,
	OPERATION,
	SHOOTDOWN,
	DONE
};

class AirThreat
{
public:
	Position getATSCurPos();	// 통신으로 보내는 것
	void launch();
	void setInitPos(Position initpos, Position targetpos);
private:
	State ATSstate;
	Position initPos;
	Position targetPos;
	Position atsCurPos;
};