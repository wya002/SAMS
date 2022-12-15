#pragma once
#include "IMode.h"

class M_IDLE : public IMode
{
public :
	static M_IDLE& getInstance();
	virtual void deploy(queue<string>* atsMsgQueue, queue<string>* mssMsgQueue, Position atsInitPos, Position atsTargetPos, Position mssInitPos);
	virtual void start(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void pause(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void restart(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);
	virtual void done(queue<string> *atsMsgQueue, queue<string> *mssMsgQueue);

	//������, ���������, �Ҹ��� ȣ�� ���� (Singleton)
	M_IDLE(const M_IDLE& ref) = delete;
	M_IDLE& operator=(const M_IDLE& ref) = delete;

private :
	M_IDLE() {};
	~M_IDLE() {};
};

