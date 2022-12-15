#include "Launcher.h"

void Launcher::launch()															// �߻� ��� ���� (Missile����)
{
	// �߻� ��� ������ MissileState�� CHASE�� ����
	if (Lstate == LauncherState::STOP)
	{
		Lstate = LauncherState::LAUNCH;
	}
}
void Launcher::setLinitPos(Position setLauncherinitPos)							// �߻�� �ʱ� ��ġ ���� (setLauncherinitPos = TCC�� ���� �޾ƿ��� ����)
{
	// �ܺο��� �߻�� �ʱ� ��ġ���� �޾Ƽ� �ʱ� ��ġ���� �缳��
	LinitPos = setLauncherinitPos;
}
void Launcher::setLstateSTOP()													// �߻�� ���¸� STOP���� ����
{
	Lstate = LauncherState::STOP;
}
LauncherState Launcher::getLstate()												// �߻�� ���� ��������
{
	return Lstate;
}
Position Launcher::getLinitPos()
{
	return LinitPos;
}
Missile& Launcher::getMissileinfo()
{
	return missileinfo;
}
