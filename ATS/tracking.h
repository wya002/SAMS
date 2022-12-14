#pragma once
#include "Position.h"
#include <cmath>

class Tracking
{
public:
	void setATSCurPos(Position pos);
	Position track(Position targetPos);
private:
	const double atsVel = 200;		// ATS �ӵ�
	const double timeStep = 0.1;	// �ɸ� �ð�
	Position atsCurPos;

};

struct Velocity
{
	double velX, velY;
};
