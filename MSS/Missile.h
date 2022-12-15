#pragma once

#include "Typedef.h"
#include "ATS.h"
#include "Tracking.h"
#include <cmath>
#include <queue>
#include <string>

using namespace std;

// setAcurPos -> setMcurPos -> getMcurPos
class Missile
{
public:
	void setAcurPos(Position MAcurPos);							// 공중위협 위치 갱신 (ATS 클래스에서만 정보를 받음)
	void setinitMcurPos(Position initMcurPos);					// 대공유도탄의 초기 위치 설정 (launcher에서 받아옴)
	void setMcurPos();											// 대공유도탄의 현재 위치 갱신 (tracking 명령에 의해서만 갱신)
	Position getMcurPos();										// 현재 대공유도탄의 위치 가져오기 (나중에 TCC에게 보내줄 정보)

	void setMstateCHASE();										// 대공유도탄 상태 CHASE로 변경 (대공유도탄이 공중위협을 요격했을 경우에만 변경 가능)
	void setMstateSTOP();										// 대공유도탄 상태 STOP으로 변경 (대공유도탄이 공중위협을 요격했을 경우 or 시나리오 중지에만 변경 가능)
	MissileState getMstate();									// 대공유도탄 상태 가져오기 (나중에 TCC에게 보내줄 정보)
	void setMevent(int eventno);								// 대공유도탄 이벤트 체크 후 변경 (eventno 1은 Success, 그 외에는 Fail)
	bool checkEvent();											// 대공유도탄 이벤트 발생 여부 체크 후 변경
	Position getAcurPos();
	queue<string> getMsgQueue();

private:
	queue<string> mQueue;
	int IP;
	Tracking trackinfo;
	ATS airthreatinfo;
	Position McurPos;											// 현재 대공유도탄의 위치 (단위 : m)
	Position AcurPos;											// 현재 공중 위협의 위치 (단위 : m)
	MissileEvent Mevent = MissileEvent::InterceptFail;			// 대공유도탄 이벤트 (요격 / 요격 실패)
	MissileState Mstate;										// 대공유도탄 상태 (STOP / CHASE)
	double InterceptRange = 2;									// 어느 거리 이하면 요격 이벤트 발생할 것인지? (단위 : pixel)
};
