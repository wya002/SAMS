#pragma once
#include "Position.h"
#include "Tracking.h"
#include "UDPSocket.h"
#include "Launcher.h"

enum class State {
	STBY,
	OPERATION,
	SHOOTDOWN,
	DONE
};

class AirThreat
{
public:
	void launch();
	void setInitPos(Position initpos, Position targetpos);
private:
	UDPSocket udpSend;
	Launcher launcher;

	State atsState;
	Position initPos;
	Position targetPos;
	Position atsCurPos;
};