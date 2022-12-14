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
	Position getATSCurPos();	// ������� ������ ��
private:
	State state;
	const char* ip;
	Position initPos;
	Position targetPos;
	Position atsCurPos;
};