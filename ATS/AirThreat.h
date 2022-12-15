#pragma once
#include "Position.h"
#include "Tracking.h"
#include <iostream>
#include <queue>
#include <string>

using namespace std;

class AirThreat
{
public:
	AirThreat() {};
	~AirThreat() {};
	queue<string>& getMsgQueue();
	void launch();
	void setInitPos(Position initpos, Position targetpos);
	void setATSCurPos(Position pos);
	void setState(State state);
	State getState();
private:
	queue<string> mQueue;
	Tracking track;
	volatile State atsState;
	Position initPos;
	Position targetPos;
	Position atsCurPos;
};