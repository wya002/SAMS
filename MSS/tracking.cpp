#include "tracking.h"
#include <cmath>

double tracking::calDistance(Position pos1, Position pos2)						// 임의의 두 지점 사이의 거리 측정	
{
	double distance = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
	return distance;
}
Velocity tracking::calVelocity(Position curMPos, Position curAPos)				// 현재 대공유도탄 지점에서의 대공유도탄 속도
{
	// curMPos는 현재 대공유도탄 위치 (x1, y1)
	// curAPos는 현재 공중위협 위치 (x2, y2)
	// velM은 미사일 속도(고정)값

	curVel.velX = velM * sqrt(pow(curAPos.x - curMPos.x, 2) / (pow(curAPos.x - curMPos.x, 2) + pow(curAPos.y - curMPos.y, 2)));
	curVel.velY = velM * sqrt(pow(curAPos.y - curMPos.y, 2) / (pow(curAPos.x - curMPos.x, 2) + pow(curAPos.y - curMPos.y, 2)));

	return curVel;
}
void tracking::track()															// 다음 timestep에서의 대공유도탄의 위치로 이동시키는 함수
{
	// 다음 위치 = 현재 위치 + timestep * 현재 속도

	Position nextPos;
	nextPos.x = curPos.x + timestep * curVel.velX;
	nextPos.y = curPos.y + timestep * curVel.velY;
	curPos = nextPos;
}
bool tracking::validateRadarRange()												// 레이다 탐지 여부 확인
{
	// 발사 위치와 공중 위협의 위치 사이의 calDistance 계산 결과가 RadarRange 보다 작으면 true
	// 그 이외의 결과는 false 를 반환

	// AADistance는 현재 공중위협과 발사대 사이의 거리

	double AADistance = calDistance(initPos, curAPos);

	if (AADistance <= RadarRange)
		return true;
	else
		return false;
}
