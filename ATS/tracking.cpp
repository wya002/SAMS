#include "Tracking.h"

void Tracking::setATSCurPos(Position pos)
{
	atsCurPos = pos;
}

Position Tracking::track(Position targetPos)
{
	Velocity atsCurVel;		// ATS 속도 계산
	atsCurVel.velX = (targetPos.x - atsCurPos.x) / sqrt(pow(targetPos.x - atsCurPos.x, 2) + pow(targetPos.y - atsCurPos.y, 2));
	atsCurVel.velY = (targetPos.y - atsCurPos.y) / sqrt(pow(targetPos.x - atsCurPos.x, 2) + pow(targetPos.y - atsCurPos.y, 2));

	if (targetPos.x == atsCurPos.x && targetPos.y == atsCurPos.y)
	{
		atsCurVel.velX = 0;
		atsCurVel.velY = 0;
	}

	// 계산된 ATS 속도를 기반으로 다음 timeStep 에서의 위치를 atsNextPos에 저장
	// 다음 위치 = 현재 위치 + timeStep * 현재 속도
	Position atsNextPos;
	atsNextPos.x = atsCurPos.x + timeStep * atsCurVel.velX;
	atsNextPos.y = atsCurPos.y + timeStep * atsCurVel.velY;
	
	return atsNextPos;
}