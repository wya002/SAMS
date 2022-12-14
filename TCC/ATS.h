#pragma once
#include "Simulator.h"

class ATS : public Simulator
{
public :
	ATS();
	ATS(const char* addr, int portNo);
	void setTargetPosition(Position pos);
	Position getTargetPosition();

private :
	Position targetPos;
};

