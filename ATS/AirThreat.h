#pragma once
#include "Position.h"

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
private:
	State state;
	const char* ip;
	Position initPos;
	Position targetPos;
	Position currentPos;
};