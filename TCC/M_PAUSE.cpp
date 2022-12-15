#include "M_PAUSE.h"
#include "M_OPERATION.h"
#include "M_DONE.h"
#include "TCC.h"
#include <iostream>

using namespace std;

M_PAUSE& M_PAUSE::getInstance() 
{
	static M_PAUSE mode_pause;
	return mode_pause;
}

void M_PAUSE::deploy(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue, Position atsInitPos, Position atsTargetPos, Position mssInitPos)
{
	cout << "���� ���α׷� ���� �� ������ �����ϼ���." << endl;
}

void M_PAUSE::start(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	restart(atsMsgQueue, mssMsgQueue);
}

void M_PAUSE::pause(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	cout << "���� ���α׷��� ���� ���� �����Դϴ�." << endl;
}

void M_PAUSE::restart(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	//����� ó��
	atsMsgQueue->push("AS:START");
	mssMsgQueue->push("MS:START");

	TCC::setMode(M_OPERATION::getInstance());
	cout << "Pause -> Restart" << endl;
}

void M_PAUSE::done(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	//����ó��
	atsMsgQueue->push("AS:DONE");
	mssMsgQueue->push("MS:DONE");

	TCC::setMode(M_DONE::getInstance());
	cout << "Cancel Scenario" << endl;
	cout << "Pause -> Done" << endl;
}