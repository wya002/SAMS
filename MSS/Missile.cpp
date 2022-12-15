#include "Missile.h"

double Missile::getDistance()												// �Ÿ� ���� (�������ź�� ���� ���� ������ �Ÿ�)
{
	return sqrt(pow(McurPos.x - AcurPos.x, 2) + pow(McurPos.y - AcurPos.y, 2));
}
void Missile::setMcurPos()													// �������ź�� ���� ��ġ ���� (tracking ��ɿ� ���ؼ��� ����)
{
	trackinfo.track(AcurPos);
	McurPos = trackinfo.getMnextPos();
}
Position Missile::getMcurPos()												// �������ź�� ���� ��ġ �������� (���߿� TCC���� ������ ����)
{
	return McurPos;
}
void Missile::setAcurPos()													// �������ź�� �����ϰ� �ִ� �������� ��ġ ���� (ATS Ŭ���������� ������ ����)
{
	AcurPos = airthreatinfo.getCurPos();
}
MissileState Missile::getMstate()											// �������ź ���� �������� (���߿� TCC���� ������ ����)
{
	return Mstate;
}
void Missile::setMevent(int eventno)										// �������ź �̺�Ʈ ���� (eventno 1�� Success, �� �ܴ̿� Fail)
{
	if (eventno == 1)
		Mevent = MissileEvent::InterceptSuccess;
}
MissileEvent Missile::getMevent()											// �������ź �̺�Ʈ �������� (���߿� TCC���� ������ ����)
{
	return Mevent;
}
void Missile::setMstateCHASE()												// �������ź ���� CHASE�� ���� (�������ź�� ���������� ������� ��쿡�� ���� ����)
{
	Mstate = MissileState::CHASE;
}
void Missile::setMstateSTOP()												// �������ź ���� STOP���� ���� (�������ź�� ���������� ������� ��� or �ó����� �������� ���� ����)
{
	// calDistance�� Ư�� ��ġ ���ϸ� �¾Ҵٰ� �Ǵ�
	// interceptRange : �������ź�� ������������ �Ÿ��� interceptRange ���ϸ� �¾Ҵٰ� �Ǵ�

	double interceptRange = 20;
	bool isIntercept = getDistance() < interceptRange;

	if (isIntercept == true)
		Mevent = MissileEvent::InterceptSuccess;
	else
		Mevent = MissileEvent::InterceptFail;
}
