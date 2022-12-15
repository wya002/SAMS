#include "M_IDLE.h"
#include "M_STBY.h"
#include "TCC.h"
#include <iostream>

using namespace std;

M_IDLE& M_IDLE::getInstance() 
{
	static M_IDLE mode_idle;
	return mode_idle;
}

void M_IDLE::deploy(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue, Position atsInitPos, Position atsTargetPos, Position mssInitPos) 
{
	atsMsgQueue->push("AI:" + to_string(atsInitPos.x) + to_string(atsInitPos.y) + to_string(atsTargetPos.x) + to_string(atsTargetPos.y));
	mssMsgQueue->push("MI:" + to_string(mssInitPos.x) + to_string(mssInitPos.y));

	TCC::setMode(M_STBY::getInstance());
	cout << "IDLE -> STBY" << endl;
}

void M_IDLE::start(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	cout << "���� �� �ó����� ������ �ʿ��մϴ�." << endl;
}

void M_IDLE::pause(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	cout << "���� ���� �� �ߴ��� �Ұ��մϴ�." << endl;
}

void M_IDLE::restart(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	cout << "���� �� �ó����� ������ �ʿ��մϴ�." << endl;
}

void M_IDLE::done(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	cout << "���� ���� �� �ߴ��� �Ұ��մϴ�." << endl;
}


