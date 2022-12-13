#include "tracking.h"

void tracking::calVelocity()													// ���� �������ź ���������� �������ź �ӵ� ���
{
	// �������� ��ġ�� ������� �������ź�� �ӵ� ���
	
	// curPos�� ���� �������ź ��ġ (x1, y1)
	// curAPos�� ���� �������� ��ġ (x2, y2)
	// velM�� �̻��� �ӵ�(����)��

	if (curPos.x < curAPos.x && curPos.y < curAPos.y)
	{
		curVel.velX = velM * sqrt(pow(curAPos.x - curPos.x, 2) / (pow(curAPos.x - curPos.x, 2) + pow(curAPos.y - curPos.y, 2)));
		curVel.velY = velM * sqrt(pow(curAPos.y - curPos.y, 2) / (pow(curAPos.x - curPos.x, 2) + pow(curAPos.y - curPos.y, 2)));
	}
	else if (curPos.x < curAPos.x && curPos.y > curAPos.y)
	{
		curVel.velX = velM * sqrt(pow(curAPos.x - curPos.x, 2) / (pow(curAPos.x - curPos.x, 2) + pow(curAPos.y - curPos.y, 2)));
		curVel.velY = (-1) * velM * sqrt(pow(curAPos.y - curPos.y, 2) / (pow(curAPos.x - curPos.x, 2) + pow(curAPos.y - curPos.y, 2)));
	}
	else if (curPos.x > curAPos.x && curPos.y < curAPos.y)
	{
		curVel.velX = (-1) * velM * sqrt(pow(curAPos.x - curPos.x, 2) / (pow(curAPos.x - curPos.x, 2) + pow(curAPos.y - curPos.y, 2)));
		curVel.velY = velM * sqrt(pow(curAPos.y - curPos.y, 2) / (pow(curAPos.x - curPos.x, 2) + pow(curAPos.y - curPos.y, 2)));
	}
	else if (curPos.x > curAPos.x && curPos.y > curAPos.y)
	{
		curVel.velX = (-1) * velM * sqrt(pow(curAPos.x - curPos.x, 2) / (pow(curAPos.x - curPos.x, 2) + pow(curAPos.y - curPos.y, 2)));
		curVel.velY = (-1) * velM * sqrt(pow(curAPos.y - curPos.y, 2) / (pow(curAPos.x - curPos.x, 2) + pow(curAPos.y - curPos.y, 2)));
	}
	else
	{
		curVel.velX = 0;
		curVel.velY = 0;
	}
}
void tracking::track()															// �������ź�� ��ġ�� ���� timestep�� ��ġ�� �̵�
{
	// ���� ��ġ = ���� ��ġ + timestep * ���� �ӵ�
	// nextPos�� ����ϰ� �� ���� curPos�� ����

	Position nextPos;
	nextPos.x = curPos.x + timestep * curVel.velX;
	nextPos.y = curPos.y + timestep * curVel.velY;
	curPos = nextPos;
}
Position tracking::getcurMPos()													// Missile�� ���� ��ġ�� �������� �Լ� (Missile���� �����ϴ� ��)
{
	return curPos;
}
