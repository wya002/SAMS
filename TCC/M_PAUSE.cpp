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
	cout << "모의 프로그램 종료 후 배포를 진행하세요." << endl;
}

void M_PAUSE::start(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	restart(atsMsgQueue, mssMsgQueue);
}

void M_PAUSE::pause(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	cout << "모의 프로그램이 현재 중지 상태입니다." << endl;
}

void M_PAUSE::restart(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	//재시작 처리
	atsMsgQueue->push("AS:START");
	mssMsgQueue->push("MS:START");

	TCC::setMode(M_OPERATION::getInstance());
	cout << "Pause -> Restart" << endl;
}

void M_PAUSE::done(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	//종료처리
	atsMsgQueue->push("AS:DONE");
	mssMsgQueue->push("MS:DONE");

	TCC::setMode(M_DONE::getInstance());
	cout << "Cancel Scenario" << endl;
	cout << "Pause -> Done" << endl;
}