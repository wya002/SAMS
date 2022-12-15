#include "M_DONE.h"
#include "M_IDLE.h"
#include "TCC.h"
#include <iostream>

using namespace std;

M_DONE& M_DONE::getInstance() 
{
	static M_DONE mode_done;
	return mode_done;
}

void M_DONE::deploy(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue, Position atsInitPos, Position atsTargetPos, Position mssInitPos)
{

}

void M_DONE::start(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{

}

void M_DONE::pause(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{

}

void M_DONE::restart(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{

}

void M_DONE::done(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue) 
{
	//종료 조건 처리
	TCC::setMode(M_IDLE::getInstance());
	cout << "Done -> Idle" << endl;
}


