#include "Launcher.h"

void Launcher::launch()															// 발사 명령 전달 (Missile에게)
{
	// 발사 명령 내리면 MissileState를 CHASE로 변경
	if (Lstate == LauncherState::STOP)
		missileinfo.setMstateCHASE();
}
void Launcher::setLinitPos(Position setLauncherinitPos)							// 발사대 초기 위치 설정 (setLauncherinitPos = TCC로 부터 받아오는 정보)
{
	// 외부에서 발사대 초기 위치값을 받아서 초기 위치값을 재설정
	LinitPos = setLauncherinitPos;
}
Position Launcher::getLinitPos()												// 발사대 초기 위치 반환
{
	return LinitPos;
}
void Launcher::setLstateSTOP()													// 발사대 상태를 STOP으로 변경
{
	Lstate = LauncherState::STOP;
}
void Launcher::setLstateLAUNCH()												// 발사대 상태를 LAUNCH로 변경
{
	Lstate = LauncherState::LAUNCH;
}
LauncherState Launcher::getLstate()												// 발사대 상태 가져오기
{
	return Lstate;
}

