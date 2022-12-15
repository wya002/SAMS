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
	void setAcurPos(Position MAcurPos);							// �������� ��ġ ���� (ATS Ŭ���������� ������ ����)
	void setinitMcurPos(Position initMcurPos);					// �������ź�� �ʱ� ��ġ ���� (launcher���� �޾ƿ�)
	void setMcurPos();											// �������ź�� ���� ��ġ ���� (tracking ��ɿ� ���ؼ��� ����)
	Position getMcurPos();										// ���� �������ź�� ��ġ �������� (���߿� TCC���� ������ ����)

	void setMstateCHASE();										// �������ź ���� CHASE�� ���� (�������ź�� ���������� ������� ��쿡�� ���� ����)
	void setMstateSTOP();										// �������ź ���� STOP���� ���� (�������ź�� ���������� ������� ��� or �ó����� �������� ���� ����)
	MissileState getMstate();									// �������ź ���� �������� (���߿� TCC���� ������ ����)
	void setMevent(int eventno);								// �������ź �̺�Ʈ üũ �� ���� (eventno 1�� Success, �� �ܿ��� Fail)
	bool checkEvent();											// �������ź �̺�Ʈ �߻� ���� üũ �� ����
	Position getAcurPos();
	queue<string> getMsgQueue();

private:
	queue<string> mQueue;
	int IP;
	Tracking trackinfo;
	ATS airthreatinfo;
	Position McurPos;											// ���� �������ź�� ��ġ (���� : m)
	Position AcurPos;											// ���� ���� ������ ��ġ (���� : m)
	MissileEvent Mevent = MissileEvent::InterceptFail;			// �������ź �̺�Ʈ (��� / ��� ����)
	MissileState Mstate;										// �������ź ���� (STOP / CHASE)
	double InterceptRange = 2;									// ��� �Ÿ� ���ϸ� ��� �̺�Ʈ �߻��� ������? (���� : pixel)
};
