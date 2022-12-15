#include "M_STBY.h"
#include "M_OPERATION.h"
#include "TCC.h"
#include <iostream>

using namespace std;

M_STBY& M_STBY::getInstance() 
{
	static M_STBY mode_stby;
	return mode_stby;
}

void M_STBY::deploy(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue, Position atsInitPos, Position atsTargetPos, Position mssInitPos)
{
	cout << "�̹� ���� �����Դϴ�." << endl;
}

void M_STBY::start(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{

	atsMsgQueue->push("AS:START");
	mssMsgQueue->push("MS:START");

	TCC::setMode(M_OPERATION::getInstance());
	cout << "STBY -> Start" << endl;
}

void M_STBY::pause(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	cout << "���� ���� �� �ߴ��� �Ұ��մϴ�." << endl;
}

void M_STBY::restart(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	start(atsMsgQueue, mssMsgQueue);
}

void M_STBY::done(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	cout << "���� ���� �� �ߴ��� �Ұ��մϴ�." << endl;
}