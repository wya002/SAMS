#include "Launcher.h"

void Launcher::launch()															// �߻� ��� ���� (Missile����)
{
	// �߻� ��� ������ MissileState�� CHASE�� ����
	if (Lstate == LauncherState::STOP)
		missileinfo.setMstateCHASE();
}
void Launcher::setLinitPos(Position setLauncherinitPos)							// �߻�� �ʱ� ��ġ ���� (setLauncherinitPos = TCC�� ���� �޾ƿ��� ����)
{
	// �ܺο��� �߻�� �ʱ� ��ġ���� �޾Ƽ� �ʱ� ��ġ���� �缳��
	LinitPos = setLauncherinitPos;
}
Position Launcher::getLinitPos()												// �߻�� �ʱ� ��ġ ��ȯ
{
	return LinitPos;
}
void Launcher::setLstateSTOP()													// �߻�� ���¸� STOP���� ����
{
	Lstate = LauncherState::STOP;
}
void Launcher::setLstateLAUNCH()												// �߻�� ���¸� LAUNCH�� ����
{
	Lstate = LauncherState::LAUNCH;
}
LauncherState Launcher::getLstate()												// �߻�� ���� ��������
{
	return Lstate;
}

