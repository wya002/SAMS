#include "Launcher.h"

void Launcher::launch()															// 발사 명령
{
	// 발사 명령 내리면 Mstate를 CHASE로 변경
	missileinfo.setMstateCHASE();
}
void Launcher::scenariostop()
{
	missileinfo.setMstateSTOP();
}
LauncherState Launcher::getLstate()
{
	return Lstate;
}
void Launcher::setinitPos(Position setinitPos)									// 발사대 위치 설정 (TCC로 부터 받아오는 정보)
{
	initPos = setinitPos;
}
bool Launcher::validateRadarRange()												// 레이다 탐지 여부 확인
{
	// 발사대와 공중 위협의 사이의 calDistance 계산 결과가 RadarRange 보다 작으면 true
	// 그 이외의 결과는 false 를 반환

	// AADistance는 현재 공중위협과 발사대 사이의 거리
	double AADistance = calDistance();

	if (AADistance <= RadarRange)
		return true;
	else
		return false;
}
double Launcher::calDistance()													// 거리 측정 (발사대와 공중위협 사이의 거리)
{
	return sqrt(pow(initPos.x - curAPos.x, 2) + pow(initPos.y - curAPos.y, 2));
}
Position Launcher::getinitPos()
{
	return initPos;
}
