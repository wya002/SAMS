#pragma once
#include "Scenario.h"

class AirThreatScenario : public Scenario
{
public:
	void setTargetPosition(Position pos);
	Position getTargetPosition();
private :
	Position targetPosition;
};
