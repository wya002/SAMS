#pragma once

#include "Typedef.h"
#include <cmath>

class tracking
{
public:
	void calVelocity();											// 현재 대공유도탄 지점에서의 대공유도탄 속도 계산
	void track();												// 대공유도탄의 위치를 다음 timestep의 위치로 이동
	Position getcurMPos();										// Missile의 현재 위치를 가져오는 함수 (Missile에게 전달하는 값)

private:
	const double velM = 2;										// 미사일 속도(고정) TBD (단위 : m/s)
	const double timestep = 0.5;								// timestep (단위 : sec, 현재 0.5s = 500ms)
	Position curPos; 											// 대공유도탄 현재 위치 (단위 : m)
	Velocity curVel;											// 대공유도탄 현재 속도 (단위 : m/s)
	Position curAPos;											// 공중 위협의 현재 위치 (단위 : m)
};
