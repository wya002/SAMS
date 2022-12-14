#pragma once
#include "Position.h"
#include "Tracking.h"
#include <queue>
#include <string>

using namespace std;

enum class State {
	STBY,
	OPERATION,
	SHOOTDOWN,
	DONE
};

class AirThreat
{
public:
	AirThreat() {};
	~AirThreat() {};
	queue<string>& getMsgQueue();
	void launch();
	void setInitPos(Position initpos, Position targetpos);

private:
	queue<string> mQueue;

	State atsState;
	Position initPos;
	Position targetPos;
	Position atsCurPos;
};