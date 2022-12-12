#pragma once

# include "ATS.h"

struct Position
{
	double x;
	double y;
};

class Missile
{
public:
	virtual ~Missile() {}
private:
	int IP;
};
