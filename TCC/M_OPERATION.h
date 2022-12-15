#pragma once
#include "IMode.h"

class M_OPERATION : public IMode
{
public :
	static M_OPERATION& getInstance();
	virtual void deploy(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue, Position atsInitPos, Position atsTargetPos, Position mssInitPos);
	virtual void start(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void pause(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void restart(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void done(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);

	M_OPERATION(const M_OPERATION& ref) = delete;
	M_OPERATION& operator=(const M_OPERATION& ref) = delete;

private:
	M_OPERATION() {};
	~M_OPERATION() {};
};

