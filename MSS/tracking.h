#pragma once

#include "Typedef.h"
#include <cmath>

// Missile.h���� �����ϴ� ��� : setMcurPos() -> track() -> getMnextPos()
class Tracking
{
public:
	void setMcurPos(Position McurPos_set);						// �������ź�� ���� ��ġ�� ����
	void track(Position AcurPos);								// �������ź�� ��ġ�� ���� timestep�� ��ġ�� �̵�
	Position getMnextPos();										// �������ź�� ���� ��ġ ��������

private:
	const double Mvel = 200;									// �̻��� �ӵ�(����) TBD (���� : m/s)
	const double timestep = 0.1;								// timestep (���� : sec, ���� 0.1s = 100ms)
	Position McurPos; 											// �������ź ���� ��ġ (���� : m)
	Position MnextPos;											// �������ź ���� ��ġ (���� : m)
	Velocity McurVel;											// �������ź ���� �ӵ� (���� : m/s)
};
