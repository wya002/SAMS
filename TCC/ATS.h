#pragma once
#include "Simulator.h"

class ATS : public Simulator
{
public :
	Position getTargetPosition;

private :
	Position targetPosition;
};

