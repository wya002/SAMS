#pragma once
#include "Simulator.h"

class ATS : private Simulator
{
public :
	ATS();
	ATS(string addr);
	void setTargetPosition(Position pos);
	Position getTargetPosition();

private :
	Position targetPos;
};

