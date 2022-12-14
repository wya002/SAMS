#pragma once
#include "Position.h"

class Simulator
{
public :
	Simulator();

	const char* getIp();
	int getPort();
	void setInitPosition(Position pos);
	void setCurPosition(Position pos);
	Position getInitPosition();
	Position getCurPosition();

protected :
	const char* ip;
	int port;
	Position initPos;
	Position curPos;
};

