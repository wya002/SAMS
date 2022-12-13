#include "Missile.h"

double Missile::getDistance()												// 거리 측정 (대공유도탄과 공중 위협 사이의 거리)
{
	return sqrt(pow(curMPos.x - curAPos.x, 2) + pow(curMPos.y - curAPos.y, 2));
	
}
void Missile::setcurMPos()													// 대공유도탄의 현재 위치 갱신 (tracking 명령에 의해서만 갱신)
{
	tracking trackinfo;
	curMPos = trackinfo.getcurMPos();
}
void Missile::setcurAPos()													// 대공유도탄이 인지하고 있는 공중위협 위치 설정 (ATS 클래스에서만 정보를 받음)
{
	ATS atsinfo;
	curAPos = atsinfo.getCurPos();
}
Position Missile::getcurMPos()												// 대공유도탄의 현재 위치 가져오기 (나중에 TCC에게 보내줄 정보)
{
	return curMPos;
}
MissileState Missile::getMstate()
{
	return Mstate;
}
void Missile::setMevent(int eventno)
{
	if (eventno == 1)
		Mevent = MissileEvent::InterceptSuccess;
	else
		Mevent = MissileEvent::InterceptFail;
}
MissileEvent Missile::getMevent()
{
	return Mevent;
}
void Missile::setMstateCHASE()
{
	Mstate = MissileState::CHASE;
}
void Missile::setMstateSTOP()												// 대공유도탄 상태 STOP으로 변경 (대공유도탄이 공중위협을 요격했을 경우 or 시나리오 중지에만 변경 가능)
{
	// calDistance가 특정 수치 이하면 맞았다고 판단
	bool isIntercept = getDistance() < 0.5;

	if (isIntercept == true)
		Mevent = MissileEvent::InterceptSuccess;
	else
		Mevent = MissileEvent::InterceptFail;
}
void Missile::track()														// 다시 생각해보기
{
	tracking trackinfo;
	trackinfo.track();
}
