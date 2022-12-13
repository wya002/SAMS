#pragma once
#include "Position.h"

class Scenario
{
public :
	void setInitPosition(Position pos);
	Position getInitPosition();
private :
	Position initPosition;
};