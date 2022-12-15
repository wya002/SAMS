#pragma once
#include "IMode.h"

class M_PAUSE : public IMode
{
public :
	static M_PAUSE& getInstance();
	virtual void deploy(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue, Position atsInitPos, Position atsTargetPos, Position mssInitPos);
	virtual void start(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void pause(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void restart(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void done(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);

	M_PAUSE(const M_PAUSE& ref) = delete;
	M_PAUSE& operator=(const M_PAUSE& ref) = delete;

private:
	M_PAUSE() {};
	~M_PAUSE() {};
};

