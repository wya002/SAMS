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
	Position getATSCurPos();	// ������� ������ ��
	void launch();
	void setInitPos(Position initpos, Position targetpos);
private:
	State ATSstate;
	Position initPos;
	Position targetPos;
	Position atsCurPos;
};