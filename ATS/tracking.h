#pragma once
#include "Position.h"
#include <cmath>

class Tracking
{
public:
	void setATSCurPos(Position pos);
	Position track(Position targetPos);
private:
	const double atsVel = 200;		// ATS 속도
	const double timeStep = 0.1;	// 걸린 시간
	Position atsCurPos;

};

struct Velocity
{
	double velX, velY;
};
