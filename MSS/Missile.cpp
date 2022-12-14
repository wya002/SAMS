#include "Missile.h"

double Missile::getDistance()												// 거리 측정 (대공유도탄과 공중 위협 사이의 거리)
{
	return sqrt(pow(McurPos.x - AcurPos.x, 2) + pow(McurPos.y - AcurPos.y, 2));
}
void Missile::setMcurPos()													// 대공유도탄의 현재 위치 갱신 (tracking 명령에 의해서만 갱신)
{
	trackinfo.track(AcurPos);
	McurPos = trackinfo.getMnextPos();
}
Position Missile::getMcurPos()												// 대공유도탄의 현재 위치 가져오기 (나중에 TCC에게 보내줄 정보)
{
	return McurPos;
}
void Missile::setAcurPos()													// 대공유도탄이 인지하고 있는 공중위협 위치 설정 (ATS 클래스에서만 정보를 받음)
{
	AcurPos = airthreatinfo.getCurPos();
}
MissileState Missile::getMstate()											// 대공유도탄 상태 가져오기 (나중에 TCC에게 보내줄 정보)
{
	return Mstate;
}
void Missile::setMevent(int eventno)										// 대공유도탄 이벤트 변경 (eventno 1은 Success, 그 이외는 Fail)
{
	if (eventno == 1)
		Mevent = MissileEvent::InterceptSuccess;
}
MissileEvent Missile::getMevent()											// 대공유도탄 이벤트 가져오기 (나중에 TCC에게 보내줄 정보)
{
	return Mevent;
}
void Missile::setMstateCHASE()												// 대공유도탄 상태 CHASE로 변경 (대공유도탄이 공중위협을 요격했을 경우에만 변경 가능)
{
	Mstate = MissileState::CHASE;
}
void Missile::setMstateSTOP()												// 대공유도탄 상태 STOP으로 변경 (대공유도탄이 공중위협을 요격했을 경우 or 시나리오 중지에만 변경 가능)
{
	// calDistance가 특정 수치 이하면 맞았다고 판단
	// interceptRange : 대공유도탄과 공중위협과의 거리가 interceptRange 이하면 맞았다고 판단

	double interceptRange = 20;
	bool isIntercept = getDistance() < interceptRange;

	if (isIntercept == true)
		Mevent = MissileEvent::InterceptSuccess;
	else
		Mevent = MissileEvent::InterceptFail;
}
