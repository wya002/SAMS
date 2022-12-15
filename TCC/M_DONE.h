#pragma once
#include "IMode.h"

class M_DONE : public IMode
{
public:
	static M_DONE& getInstance();
	virtual void deploy(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue, Position atsInitPos, Position atsTargetPos, Position mssInitPos);
	virtual void start(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void pause(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void restart(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void done(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);

	M_DONE(const M_DONE& ref) = delete;
	M_DONE& operator=(const M_DONE& ref) = delete;

private:
	M_DONE() {};
	~M_DONE() {};
};