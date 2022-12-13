#include "tracking.h"

void tracking::calVelocity()													// 현재 대공유도탄 지점에서의 대공유도탄 속도 계산
{
	// 공중위협 위치를 기반으로 대공유도탄의 속도 계산
	
	// curPos는 현재 대공유도탄 위치 (x1, y1)
	// curAPos는 현재 공중위협 위치 (x2, y2)
	// velM은 미사일 속도(고정)값

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
void tracking::track()															// 대공유도탄의 위치를 다음 timestep의 위치로 이동
{
	// 다음 위치 = 현재 위치 + timestep * 현재 속도
	// nextPos를 계산하고 그 값을 curPos에 대입

	Position nextPos;
	nextPos.x = curPos.x + timestep * curVel.velX;
	nextPos.y = curPos.y + timestep * curVel.velY;
	curPos = nextPos;
}
Position tracking::getcurMPos()													// Missile의 현재 위치를 가져오는 함수 (Missile에게 전달하는 값)
{
	return curPos;
}
