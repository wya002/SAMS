#include "Tracking.h"

void Tracking::setMcurPos(Position McurPos_set)
{
	McurPos = McurPos_set;
}
void Tracking::track(Position AcurPos)															// �������ź�� ��ġ�� ���� timestep�� ��ġ�� �̵�
{
	// Missile �ӵ� ���
	McurVel.velX = (AcurPos.x - McurPos.x) / sqrt(pow(AcurPos.x - McurPos.x, 2) + pow(AcurPos.y - McurPos.y, 2));
	McurVel.velY = (AcurPos.y - McurPos.y) / sqrt(pow(AcurPos.x - McurPos.x, 2) + pow(AcurPos.y - McurPos.y, 2));

	if (AcurPos.x == McurPos.x && AcurPos.y == McurPos.y)
	{
		McurVel.velX = 0;
		McurVel.velY = 0;
	}

	// ���� Missile �ӵ��� ������� ���� timestep ������ ��ġ�� MnextPos�� ����
	// ���� ��ġ = ���� ��ġ + timestep * ���� �ӵ�
	MnextPos.x = McurPos.x + timestep * McurVel.velX;
	MnextPos.y = McurPos.y + timestep * McurVel.velY;
}
Position Tracking::getMnextPos()
{
	return MnextPos;
}
