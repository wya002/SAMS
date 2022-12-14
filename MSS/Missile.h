#pragma once

#include "Typedef.h"
#include "ATS.h"
#include "Tracking.h"
#include <cmath>

class Missile
{
public:
	double getDistance();										// �Ÿ� ���� (�������ź�� ���� ���� ������ �Ÿ�)
	void setMcurPos();											// �������ź�� ���� ��ġ ���� (tracking ��ɿ� ���ؼ��� ����)
	Position getMcurPos();										// ���� �������ź�� ��ġ �������� (���߿� TCC���� ������ ����)
	void setAcurPos();											// �������� ��ġ ���� (ATS Ŭ���������� ������ ����)
	void setMstateCHASE();										// �������ź ���� CHASE�� ���� (�������ź�� ���������� ������� ��쿡�� ���� ����)
	void setMstateSTOP();										// �������ź ���� STOP���� ���� (�������ź�� ���������� ������� ��� or �ó����� �������� ���� ����)
	MissileState getMstate();									// �������ź ���� �������� (���߿� TCC���� ������ ����)
	void setMevent(int eventno);								// �������ź �̺�Ʈ ���� (eventno 1�� Success, 2�� Fail)
	MissileEvent getMevent();									// �������ź �̺�Ʈ �������� (���߿� TCC���� ������ ����)

private:
	int IP;
	Tracking trackinfo;
	ATS airthreatinfo;
	Position McurPos;											// ���� �������ź�� ��ġ (���� : m)
	Position AcurPos;											// ���� ���� ������ ��ġ (���� : m)
	MissileEvent Mevent = MissileEvent::InterceptFail;			// �������ź �̺�Ʈ (��� / ��� ����)
	MissileState Mstate = MissileState::STOP;					// �������ź ���� (STOP / CHASE)
};
