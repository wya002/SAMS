#include "Missile.h"

double Missile::getDistance()												// �Ÿ� ���� (�������ź�� ���� ���� ������ �Ÿ�)
{
	return sqrt(pow(curMPos.x - curAPos.x, 2) + pow(curMPos.y - curAPos.y, 2));
	
}
void Missile::setcurMPos()													// �������ź�� ���� ��ġ ���� (tracking ��ɿ� ���ؼ��� ����)
{
	tracking trackinfo;
	curMPos = trackinfo.getcurMPos();
}
void Missile::setcurAPos()													// �������ź�� �����ϰ� �ִ� �������� ��ġ ���� (ATS Ŭ���������� ������ ����)
{
	ATS atsinfo;
	curAPos = atsinfo.getCurPos();
}
Position Missile::getcurMPos()												// �������ź�� ���� ��ġ �������� (���߿� TCC���� ������ ����)
{
	return curMPos;
}
MissileState Missile::getMstate()
{
	return Mstate;
}
void Missile::setMevent(int eventno)
{
	if (eventno == 1)
		Mevent = MissileEvent::InterceptSuccess;
	else
		Mevent = MissileEvent::InterceptFail;
}
MissileEvent Missile::getMevent()
{
	return Mevent;
}
void Missile::setMstateCHASE()
{
	Mstate = MissileState::CHASE;
}
void Missile::setMstateSTOP()												// �������ź ���� STOP���� ���� (�������ź�� ���������� ������� ��� or �ó����� �������� ���� ����)
{
	// calDistance�� Ư�� ��ġ ���ϸ� �¾Ҵٰ� �Ǵ�
	bool isIntercept = getDistance() < 0.5;

	if (isIntercept == true)
		Mevent = MissileEvent::InterceptSuccess;
	else
		Mevent = MissileEvent::InterceptFail;
}
void Missile::track()														// �ٽ� �����غ���
{
	tracking trackinfo;
	trackinfo.track();
}
