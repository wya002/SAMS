#include "Launcher.h"

void Launcher::launch()															// 발사 명령 전달 (Missile에게)
{
	// 발사 명령 내리면 MissileState를 CHASE로 변경
	if (Lstate == LauncherState::STOP)
	{
		Lstate = LauncherState::LAUNCH;
	}
}
void Launcher::setLinitPos(Position setLauncherinitPos)							// 발사대 초기 위치 설정 (setLauncherinitPos = TCC로 부터 받아오는 정보)
{
	// 외부에서 발사대 초기 위치값을 받아서 초기 위치값을 재설정
	LinitPos = setLauncherinitPos;
}
void Launcher::setLstateSTOP()													// 발사대 상태를 STOP으로 변경
{
	Lstate = LauncherState::STOP;
}
LauncherState Launcher::getLstate()												// 발사대 상태 가져오기
{
	return Lstate;
}
Position Launcher::getLinitPos()
{
	return LinitPos;
}
Missile& Launcher::getMissileinfo()
{
	return missileinfo;
}
