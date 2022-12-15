#pragma once
#include "IMode.h"

class M_STBY : public IMode
{
public :
	static M_STBY& getInstance();
	virtual void deploy(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue, Position atsInitPos, Position atsTargetPos, Position mssInitPos);
	virtual void start(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void pause(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void restart(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void done(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);

	M_STBY(const M_STBY& ref) = delete;
	M_STBY& operator=(const M_STBY& ref) = delete;

private:
	M_STBY() {};
	~M_STBY() {};
};