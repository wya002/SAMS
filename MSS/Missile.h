#pragma once

#include "Typedef.h"
#include "ATS.h"
#include "tracking.h"
#include <cmath>

class Missile
{
public:
	double getDistance();										// �Ÿ� ���� (�������ź-�������� �Ÿ�)
	void setcurMPos();											// �������ź�� ���� ��ġ ���� (tracking ��ɿ� ���ؼ��� ����)
	void setcurAPos();											// �������� ��ġ ���� (ATS Ŭ���������� ������ ����)
	Position getcurMPos();										// ���� �������ź�� ��ġ �������� (���߿� TCC���� ������ ����)
	void setMstateCHASE();										// �������ź ���� CHASE�� ���� (�������ź�� ���������� ������� ��쿡�� ���� ����)
	void setMstateSTOP();										// �������ź ���� STOP���� ���� (�������ź�� ���������� ������� ��� or �ó����� �������� ���� ����)
	MissileState getMstate();									// �������ź ���� �������� (���߿� TCC���� ������ ����)
	void setMevent(int eventno);								// �������ź �̺�Ʈ ���� (eventno 1�� Success, 2�� Fail)
	MissileEvent getMevent();									// �������ź �̺�Ʈ �������� (���߿� TCC���� ������ ����)
	void track();												// �������ź ��ġ ���� (���������� ���� ����)

private:
	int IP;
	Position curMPos;											// ���� �������ź�� ��ġ (���� : m)
	Position curAPos;											// ���� ���� ������ ��ġ (���� : m)
	MissileEvent Mevent = MissileEvent::InterceptFail;			// �������ź �̺�Ʈ (��� / ��� ����)
	MissileState Mstate = MissileState::STOP;					// �������ź ���� (STOP / CHASE)
};
