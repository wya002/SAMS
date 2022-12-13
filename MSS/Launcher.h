#pragma once
#include "TypeDef.h"
#include "Missile.h"
#include <cmath>

class Launcher
{
public:
	void launch();												// 발사 명령
	void scenariostop();										// 발사 중지 명령
	LauncherState getLstate();									// 발사대 상태 가져오기
	void setinitPos(Position setinitPos);						// 발사대 위치 설정 (setinitPos = TCC로 부터 받아오는 정보)
	bool validateRadarRange();									// 레이다 탐지 여부 확인
	double calDistance();										// 거리 측정 (발사대와 공중위협 사이의 거리)
	Position getinitPos();										// 발사대 초기 위치 가져오기

private:
	const double RadarRange = 300;								// 탐지 가능 범위 (단위 : m)
	Missile missileinfo;										// Launcher에서 가지고 있는 Missile 객체
	LauncherState Lstate = LauncherState::STOP;					// 발사대 상태 (enum class)
	Position initPos;											// 발사대 위치 (=대공유도탄 초기 발사 위치) (단위 : m)
	Position curAPos;											// 공중위협 위치 (단위 : m)
};
