#include "Tracking.h"

void Tracking::setATSCurPos(Position pos)
{
	atsCurPos = pos;
}

Position Tracking::track(Position targetPos)
{
	Velocity atsCurVel;		// ATS �ӵ� ���
	atsCurVel.velX = (targetPos.x - atsCurPos.x) / sqrt(pow(targetPos.x - atsCurPos.x, 2) + pow(targetPos.y - atsCurPos.y, 2));
	atsCurVel.velY = (targetPos.y - atsCurPos.y) / sqrt(pow(targetPos.x - atsCurPos.x, 2) + pow(targetPos.y - atsCurPos.y, 2));

	if (targetPos.x == atsCurPos.x && targetPos.y == atsCurPos.y)
	{
		atsCurVel.velX = 0;
		atsCurVel.velY = 0;
	}

	// ���� ATS �ӵ��� ������� ���� timeStep ������ ��ġ�� atsNextPos�� ����
	// ���� ��ġ = ���� ��ġ + timeStep * ���� �ӵ�
	Position atsNextPos;
	atsNextPos.x = atsCurPos.x + timeStep * atsCurVel.velX;
	atsNextPos.y = atsCurPos.y + timeStep * atsCurVel.velY;
	
	return atsNextPos;
}