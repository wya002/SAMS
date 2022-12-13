#include "Launcher.h"

void Launcher::launch()															// �߻� ���
{
	// �߻� ��� ������ Mstate�� CHASE�� ����
	missileinfo.setMstateCHASE();
}
void Launcher::scenariostop()
{
	missileinfo.setMstateSTOP();
}
LauncherState Launcher::getLstate()
{
	return Lstate;
}
void Launcher::setinitPos(Position setinitPos)									// �߻�� ��ġ ���� (TCC�� ���� �޾ƿ��� ����)
{
	initPos = setinitPos;
}
bool Launcher::validateRadarRange()												// ���̴� Ž�� ���� Ȯ��
{
	// �߻��� ���� ������ ������ calDistance ��� ����� RadarRange ���� ������ true
	// �� �̿��� ����� false �� ��ȯ

	// AADistance�� ���� ���������� �߻�� ������ �Ÿ�
	double AADistance = calDistance();

	if (AADistance <= RadarRange)
		return true;
	else
		return false;
}
double Launcher::calDistance()													// �Ÿ� ���� (�߻��� �������� ������ �Ÿ�)
{
	return sqrt(pow(initPos.x - curAPos.x, 2) + pow(initPos.y - curAPos.y, 2));
}
Position Launcher::getinitPos()
{
	return initPos;
}
