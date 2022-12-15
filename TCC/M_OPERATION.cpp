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
	cout << "모의 프로그램이 종료된 후 배포 가능합니다." << endl;
}

void M_OPERATION::start(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	cout << "모의 프로그램이 현재 진행 중입니다." << endl;
}

void M_OPERATION::pause(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	//중단 처리
	atsMsgQueue->push("AS:PAUSE");
	mssMsgQueue->push("MS:PAUSE");

	TCC::setMode(M_PAUSE::getInstance());
	cout << "Operation -> Pause" << endl;
}

void M_OPERATION::restart(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	cout << "모의 프로그램이 현재 진행 중입니다." << endl;
}

void M_OPERATION::done(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	//종료전달
	atsMsgQueue->push("AS:DONE");
	mssMsgQueue->push("MS:DONE");

	//종료조건 만족 못하면 Cancle 이벤트 실행해야함!!!
	 
	//종료 조건 : cancle , ATS 목표지점 도착, M
	TCC::setMode(M_DONE::getInstance());
	cout << "Project End" << endl;
	cout << "Operation -> Done" << endl;
}