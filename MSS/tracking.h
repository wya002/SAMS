#pragma once

#include "Typedef.h"
#include <cmath>

class tracking
{
public:
	void calVelocity();											// ���� �������ź ���������� �������ź �ӵ� ���
	void track();												// �������ź�� ��ġ�� ���� timestep�� ��ġ�� �̵�
	Position getcurMPos();										// Missile�� ���� ��ġ�� �������� �Լ� (Missile���� �����ϴ� ��)

private:
	const double velM = 2;										// �̻��� �ӵ�(����) TBD (���� : m/s)
	const double timestep = 0.5;								// timestep (���� : sec, ���� 0.5s = 500ms)
	Position curPos; 											// �������ź ���� ��ġ (���� : m)
	Velocity curVel;											// �������ź ���� �ӵ� (���� : m/s)
	Position curAPos;											// ���� ������ ���� ��ġ (���� : m)
};
