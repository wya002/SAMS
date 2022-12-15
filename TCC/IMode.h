#pragma once
#include <queue>
#include <string>
#include "Position.h"

using namespace std;

class IMode
{
public :
	virtual void deploy(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue, Position atsInitPos, Position atsTargetPos, Position mssInitPos) = 0;
	virtual void start(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue) = 0;
	virtual void pause(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue) = 0;
	virtual void restart(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue) = 0;
	virtual void done(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue) = 0;
};