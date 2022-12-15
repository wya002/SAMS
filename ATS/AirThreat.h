#pragma once
#include "Position.h"
#include "Tracking.h"
#include "UDPSocket.h"
#include <iostream>

class AirThreat
{
public:
	void launch();
	void setInitPos(Position initpos, Position targetpos);
	void setATSCurPos(Position pos);
	void setState();
	State getState();
private:
	//UDPSocket udpSend;
	Tracking track;
	State atsState;
	Position initPos;
	Position targetPos;
	Position atsCurPos;
};