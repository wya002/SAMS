#pragma once
#include "IMode.h"

class M_IDLE : public IMode
{
public :
	static M_IDLE& getInstance();
	virtual void deploy(queue<string>&);
	virtual void start(queue<string>&);
	virtual void pause(queue<string>&);
	virtual void restart(queue<string>&);
	virtual void done(queue<string>&);

	//������, ���������, �Ҹ��� ȣ�� ���� (Singleton)
	M_IDLE(const M_IDLE& ref) = delete;
	M_IDLE& operator=(const M_IDLE& ref) = delete;

private :
	M_IDLE() {};
	~M_IDLE() {};
};

