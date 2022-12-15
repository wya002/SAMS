#pragma once

#include "TypeDef.h"
#include "Missile.h"
#include <cmath>
#include <iostream>

// setLinitPos -> launch
class Launcher
{
public:
	void launch();													// �߻� ���
	void setLinitPos(Position setLauncherinitPos);					// �߻�� �ʱ� ��ġ ���� (setinitPos = TCC�� ���� �޾ƿ��� ����)
	void setLstateSTOP();											// �߻�� ���¸� STOP���� ����
	LauncherState getLstate();										// �߻�� ���� ��������
	Position getLinitPos();											// �߻�� �ʱ� ��ġ ��ȯ
	Missile& getMissileinfo();

private:
	const double RadarRange = 300;									// Ž�� ���� ���� (���� : m)
	Missile missileinfo;											// Launcher���� ������ �ִ� Missile ��ü
	LauncherState Lstate;											// �߻�� ���� (enum class)
	Position LinitPos;												// �߻�� ��ġ (=�������ź �ʱ� �߻� ��ġ) (���� : m)
	Position AcurPos;												// �������� ��ġ (���� : m)
};
