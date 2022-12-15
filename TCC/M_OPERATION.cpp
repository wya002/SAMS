#include "M_OPERATION.h"
#include "M_PAUSE.h"
#include "M_DONE.h"
#include "TCC.h"
#include <iostream>

using namespace std;

M_OPERATION& M_OPERATION::getInstance() 
{
	static M_OPERATION mode_operation;
	return mode_operation;
}

void M_OPERATION::deploy(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue, Position atsInitPos, Position atsTargetPos, Position mssInitPos)
{
	cout << "���� ���α׷��� ����� �� ���� �����մϴ�." << endl;
}

void M_OPERATION::start(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	cout << "���� ���α׷��� ���� ���� ���Դϴ�." << endl;
}

void M_OPERATION::pause(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	//�ߴ� ó��
	atsMsgQueue->push("AS:PAUSE");
	mssMsgQueue->push("MS:PAUSE");

	TCC::setMode(M_PAUSE::getInstance());
	cout << "Operation -> Pause" << endl;
}

void M_OPERATION::restart(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	cout << "���� ���α׷��� ���� ���� ���Դϴ�." << endl;
}

void M_OPERATION::done(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	//��������
	atsMsgQueue->push("AS:DONE");
	mssMsgQueue->push("MS:DONE");

	//�������� ���� ���ϸ� Cancle �̺�Ʈ �����ؾ���!!!
	 
	//���� ���� : cancle , ATS ��ǥ���� ����, M
	TCC::setMode(M_DONE::getInstance());
	cout << "Project End" << endl;
	cout << "Operation -> Done" << endl;
}