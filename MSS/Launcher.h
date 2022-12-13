#pragma once
#include "TypeDef.h"
#include "Missile.h"
#include <cmath>

class Launcher
{
public:
	void launch();												// �߻� ���
	void scenariostop();										// �߻� ���� ���
	LauncherState getLstate();									// �߻�� ���� ��������
	void setinitPos(Position setinitPos);						// �߻�� ��ġ ���� (setinitPos = TCC�� ���� �޾ƿ��� ����)
	bool validateRadarRange();									// ���̴� Ž�� ���� Ȯ��
	double calDistance();										// �Ÿ� ���� (�߻��� �������� ������ �Ÿ�)
	Position getinitPos();										// �߻�� �ʱ� ��ġ ��������

private:
	const double RadarRange = 300;								// Ž�� ���� ���� (���� : m)
	Missile missileinfo;										// Launcher���� ������ �ִ� Missile ��ü
	LauncherState Lstate = LauncherState::STOP;					// �߻�� ���� (enum class)
	Position initPos;											// �߻�� ��ġ (=�������ź �ʱ� �߻� ��ġ) (���� : m)
	Position curAPos;											// �������� ��ġ (���� : m)
};
