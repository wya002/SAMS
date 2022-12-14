#include "Tracking.h"

void Tracking::setMcurPos(Position McurPos_set)
{
	McurPos = McurPos_set;
}
void Tracking::track(Position AcurPos)															// 대공유도탄의 위치를 다음 timestep의 위치로 이동
{
	// Missile 속도 계산
	McurVel.velX = (AcurPos.x - McurPos.x) / sqrt(pow(AcurPos.x - McurPos.x, 2) + pow(AcurPos.y - McurPos.y, 2));
	McurVel.velY = (AcurPos.y - McurPos.y) / sqrt(pow(AcurPos.x - McurPos.x, 2) + pow(AcurPos.y - McurPos.y, 2));

	if (AcurPos.x == McurPos.x && AcurPos.y == McurPos.y)
	{
		McurVel.velX = 0;
		McurVel.velY = 0;
	}

	// 계산된 Missile 속도를 기반으로 다음 timestep 에서의 위치를 MnextPos에 저장
	// 다음 위치 = 현재 위치 + timestep * 현재 속도
	MnextPos.x = McurPos.x + timestep * McurVel.velX;
	MnextPos.y = McurPos.y + timestep * McurVel.velY;
}
Position Tracking::getMnextPos()
{
	return MnextPos;
}
