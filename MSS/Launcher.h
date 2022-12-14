#pragma once

#include "TypeDef.h"
#include "Missile.h"
#include <cmath>

class Launcher
{
public:
	void launch();													// �߻� ���
	void setLinitPos(Position setLauncherinitPos);					// �߻�� �ʱ� ��ġ ���� (setinitPos = TCC�� ���� �޾ƿ��� ����)
	Position getLinitPos();											// �߻�� �ʱ� ��ġ ��ȯ
	void setLstateSTOP();											// �߻�� ���¸� STOP���� ����
	void setLstateLAUNCH();											// �߻�� ���¸� LAUNCH�� ����
	LauncherState getLstate();										// �߻�� ���� ��������

private:
	const double RadarRange = 300;									// Ž�� ���� ���� (���� : m)
	Missile missileinfo;											// Launcher���� ������ �ִ� Missile ��ü
	LauncherState Lstate = LauncherState::STOP;						// �߻�� ���� (enum class)
	Position LinitPos;												// �߻�� ��ġ (=�������ź �ʱ� �߻� ��ġ) (���� : m)
	Position AcurPos;												// �������� ��ġ (���� : m)
};
