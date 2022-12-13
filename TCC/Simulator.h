#pragma once
#include "Position.h"
#include <string>

using namespace std;

class Simulator
{
public :
	Simulator();

	string getIp();
	void setInitPosition(Position pos);
	void setCurPosition(Position pos);
	Position getInitPosition();
	Position getCurPosition();

protected :
	string ip;
	string port;
	Position initPos;
	Position curPos;
};

