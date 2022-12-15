#include "Missile.h"

void Missile::setAcurPos(Position MAcurPos)									// 대공유도탄이 인지하고 있는 공중위협 위치 설정 (ATS 클래스에서만 정보를 받음)
{
	AcurPos = MAcurPos;
}
void Missile::setinitMcurPos(Position initMcurPos)
{
	McurPos = initMcurPos;
}

queue<string>  Missile::getMsgQueue()
{
	return mQueue;
}

void Missile::setMcurPos()													// 대공유도탄의 현재 위치 갱신 (tracking 명령에 의해서만 갱신)
{
	if (Mstate == MissileState::CHASE)
	{
		// setMcurPos()->track()->getMnextPos()
		trackinfo.setMcurPos(McurPos);
		trackinfo.track(AcurPos);
		Position _McurPos = trackinfo.getMnextPos();
		McurPos = _McurPos;
	}
}
Position Missile::getMcurPos()												// 대공유도탄의 현재 위치 가져오기 (나중에 TCC에게 보내줄 정보)
{
	return McurPos;
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
bool Missile::checkEvent()
{
	bool _isintercept = false;

	if (fabs(McurPos.x - AcurPos.x) < InterceptRange || fabs(McurPos.y - AcurPos.y) < InterceptRange)
		_isintercept = true;	

	return _isintercept;
}
void Missile::setMstateCHASE()												// 대공유도탄 상태 CHASE로 변경 (대공유도탄이 공중위협을 요격했을 경우에만 변경 가능)
{
	Mstate = MissileState::CHASE;
}
void Missile::setMstateSTOP()												// 대공유도탄 상태 STOP으로 변경 (대공유도탄이 공중위협을 요격했을 경우 or 시나리오 중지에만 변경 가능)
{
	// calDistance가 특정 수치 이하면 맞았다고 판단
	// interceptRange : 대공유도탄과 공중위협과의 거리가 interceptRange 이하면 맞았다고 판단

	Mstate = MissileState::STOP;
}
Position Missile::getAcurPos()
{
	return AcurPos;
}
