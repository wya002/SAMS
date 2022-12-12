#include "tracking.h"
#include <cmath>

double tracking::calDistance(Position pos1, Position pos2)						// ������ �� ���� ������ �Ÿ� ����	
{
	double distance = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
	return distance;
}
Velocity tracking::calVelocity(Position curMPos, Position curAPos)				// ���� �������ź ���������� �������ź �ӵ�
{
	// curMPos�� ���� �������ź ��ġ (x1, y1)
	// curAPos�� ���� �������� ��ġ (x2, y2)
	// velM�� �̻��� �ӵ�(����)��

	curVel.velX = velM * sqrt(pow(curAPos.x - curMPos.x, 2) / (pow(curAPos.x - curMPos.x, 2) + pow(curAPos.y - curMPos.y, 2)));
	curVel.velY = velM * sqrt(pow(curAPos.y - curMPos.y, 2) / (pow(curAPos.x - curMPos.x, 2) + pow(curAPos.y - curMPos.y, 2)));

	return curVel;
}
void tracking::track()															// ���� timestep������ �������ź�� ��ġ�� �̵���Ű�� �Լ�
{
	// ���� ��ġ = ���� ��ġ + timestep * ���� �ӵ�

	Position nextPos;
	nextPos.x = curPos.x + timestep * curVel.velX;
	nextPos.y = curPos.y + timestep * curVel.velY;
	curPos = nextPos;
}
bool tracking::validateRadarRange()												// ���̴� Ž�� ���� Ȯ��
{
	// �߻� ��ġ�� ���� ������ ��ġ ������ calDistance ��� ����� RadarRange ���� ������ true
	// �� �̿��� ����� false �� ��ȯ

	// AADistance�� ���� ���������� �߻�� ������ �Ÿ�

	double AADistance = calDistance(initPos, curAPos);

	if (AADistance <= RadarRange)
		return true;
	else
		return false;
}
