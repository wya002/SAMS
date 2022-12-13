#pragma once
#include "Position.h"

class Simulator
{
public :
	Simulator();
	~Simulator();

	int getIp();
	void setCurPosition(Position pos);
	void setInitPosition(Position pos);
	Position getCurPosition();
	Position getInitPosition();

private :
	int ip;
	Position initPos;
	Position curPos;
};

