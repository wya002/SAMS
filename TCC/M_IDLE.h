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

	//생성자, 복사생성자, 소멸자 호출 금지 (Singleton)
	M_IDLE(const M_IDLE& ref) = delete;
	M_IDLE& operator=(const M_IDLE& ref) = delete;

private :
	M_IDLE() {};
	~M_IDLE() {};
};

