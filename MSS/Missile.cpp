#include "Missile.h"

void Missile::setAcurPos(Position MAcurPos)									// �������ź�� �����ϰ� �ִ� �������� ��ġ ���� (ATS Ŭ���������� ������ ����)
{
	AcurPos = MAcurPos;
}
void Missile::setinitMcurPos(Position initMcurPos)
{
	McurPos = initMcurPos;
}

queue<string>  Missile::getMsgQueue()
{
	return mQueue;
}

void Missile::setMcurPos()													// �������ź�� ���� ��ġ ���� (tracking ��ɿ� ���ؼ��� ����)
{
	if (Mstate == MissileState::CHASE)
	{
		// setMcurPos()->track()->getMnextPos()
		trackinfo.setMcurPos(McurPos);
		trackinfo.track(AcurPos);
		Position _McurPos = trackinfo.getMnextPos();
		McurPos = _McurPos;
	}
}
Position Missile::getMcurPos()												// �������ź�� ���� ��ġ �������� (���߿� TCC���� ������ ����)
{
	return McurPos;
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
bool Missile::checkEvent()
{
	bool _isintercept = false;

	if (fabs(McurPos.x - AcurPos.x) < InterceptRange || fabs(McurPos.y - AcurPos.y) < InterceptRange)
		_isintercept = true;	

	return _isintercept;
}
void Missile::setMstateCHASE()												// �������ź ���� CHASE�� ���� (�������ź�� ���������� ������� ��쿡�� ���� ����)
{
	Mstate = MissileState::CHASE;
}
void Missile::setMstateSTOP()												// �������ź ���� STOP���� ���� (�������ź�� ���������� ������� ��� or �ó����� �������� ���� ����)
{
	// calDistance�� Ư�� ��ġ ���ϸ� �¾Ҵٰ� �Ǵ�
	// interceptRange : �������ź�� ������������ �Ÿ��� interceptRange ���ϸ� �¾Ҵٰ� �Ǵ�

	Mstate = MissileState::STOP;
}
Position Missile::getAcurPos()
{
	return AcurPos;
}
