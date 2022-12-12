#pragma once

struct Position
{
	double x;
	double y;
};
struct Velocity
{
	double velX;
	double velY;
};

class tracking
{
public:
	double calDistance(Position pos1, Position pos2);
	Velocity calVelocity(Position curMPos, Position curAPos);
	void track();
	bool validateRadarRange();
private:
	const double velM = 50;					// 미사일 속도(고정) TBD (단위 : m/s)
	const double RadarRange = 3000;			// 탐지 가능 범위 (단위 : m)
	Position initPos;						// 발사대 위치 (단위 : m)
	Position curPos; 						// 현재 위치 (단위 : m)
	Velocity curVel;						// 현재 속도 (단위 : m/s)
	double timestep;						// timestep (단위 : sec)
	Position curAPos;						// 공중 위협의 현재 위치 (단위 : m)
};
