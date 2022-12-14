#pragma once

#include "Typedef.h"
#include <cmath>

// Missile.h에서 수행하는 기능 : setMcurPos() -> track() -> getMnextPos()
class Tracking
{
public:
	void setMcurPos(Position McurPos_set);						// 대공유도탄의 현재 위치를 설정
	void track(Position AcurPos);								// 대공유도탄의 위치를 다음 timestep의 위치로 이동
	Position getMnextPos();										// 대공유도탄의 다음 위치 가져오기

private:
	const double Mvel = 200;									// 미사일 속도(고정) TBD (단위 : m/s)
	const double timestep = 0.1;								// timestep (단위 : sec, 현재 0.1s = 100ms)
	Position McurPos; 											// 대공유도탄 현재 위치 (단위 : m)
	Position MnextPos;											// 대공유도탄 다음 위치 (단위 : m)
	Velocity McurVel;											// 대공유도탄 현재 속도 (단위 : m/s)
};
