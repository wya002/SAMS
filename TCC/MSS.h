#pragma once
#include "Simulator.h"

class MSS : public Simulator
{
public :
	MSS() {};
	MSS(const char* addr, int portNo);
};

