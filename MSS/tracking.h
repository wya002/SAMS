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
	const double velM = 50;					// �̻��� �ӵ�(����) TBD (���� : m/s)
	const double RadarRange = 3000;			// Ž�� ���� ���� (���� : m)
	Position initPos;						// �߻�� ��ġ (���� : m)
	Position curPos; 						// ���� ��ġ (���� : m)
	Velocity curVel;						// ���� �ӵ� (���� : m/s)
	double timestep;						// timestep (���� : sec)
	Position curAPos;						// ���� ������ ���� ��ġ (���� : m)
};
