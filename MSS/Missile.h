#pragma once

#include "Typedef.h"
#include "ATS.h"
#include "tracking.h"
#include <cmath>

class Missile
{
public:
	double getDistance();										// 거리 측정 (대공유도탄-공중위협 거리)
	void setcurMPos();											// 대공유도탄의 현재 위치 갱신 (tracking 명령에 의해서만 갱신)
	void setcurAPos();											// 공중위협 위치 갱신 (ATS 클래스에서만 정보를 받음)
	Position getcurMPos();										// 현재 대공유도탄의 위치 가져오기 (나중에 TCC에게 보내줄 정보)
	void setMstateCHASE();										// 대공유도탄 상태 CHASE로 변경 (대공유도탄이 공중위협을 요격했을 경우에만 변경 가능)
	void setMstateSTOP();										// 대공유도탄 상태 STOP으로 변경 (대공유도탄이 공중위협을 요격했을 경우 or 시나리오 중지에만 변경 가능)
	MissileState getMstate();									// 대공유도탄 상태 가져오기 (나중에 TCC에게 보내줄 정보)
	void setMevent(int eventno);								// 대공유도탄 이벤트 변경 (eventno 1은 Success, 2는 Fail)
	MissileEvent getMevent();									// 대공유도탄 이벤트 가져오기 (나중에 TCC에게 보내줄 정보)
	void track();												// 대공유도탄 위치 변경 (공중위협을 따라 추적)

private:
	int IP;
	Position curMPos;											// 현재 대공유도탄의 위치 (단위 : m)
	Position curAPos;											// 현재 공중 위협의 위치 (단위 : m)
	MissileEvent Mevent = MissileEvent::InterceptFail;			// 대공유도탄 이벤트 (요격 / 요격 실패)
	MissileState Mstate = MissileState::STOP;					// 대공유도탄 상태 (STOP / CHASE)
};
