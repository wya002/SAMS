#pragma once
#include "Position.h"
#include "tracking.h"

enum class State {
	STBY,
	OPERATION,
	SHOOTDOWN,
	DONE
};

class AirThreat
{
public:
	void track();
	Position getATSCurPos();	// 통신으로 보내는 것
private:
	State state;
	const char* ip;
	Position initPos;
	Position targetPos;
	Position atsCurPos;
};