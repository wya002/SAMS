#pragma once

#include "TypeDef.h"
#include "Missile.h"
#include <cmath>
#include <iostream>

// setLinitPos -> launch
class Launcher
{
public:
	void launch();													// 발사 명령
	void setLinitPos(Position setLauncherinitPos);					// 발사대 초기 위치 설정 (setinitPos = TCC로 부터 받아오는 정보)
	void setLstateSTOP();											// 발사대 상태를 STOP으로 변경
	LauncherState getLstate();										// 발사대 상태 가져오기
	Position getLinitPos();											// 발사대 초기 위치 반환
	Missile& getMissileinfo();

private:
	const double RadarRange = 300;									// 탐지 가능 범위 (단위 : m)
	Missile missileinfo;											// Launcher에서 가지고 있는 Missile 객체
	LauncherState Lstate;											// 발사대 상태 (enum class)
	Position LinitPos;												// 발사대 위치 (=대공유도탄 초기 발사 위치) (단위 : m)
	Position AcurPos;												// 공중위협 위치 (단위 : m)
};
