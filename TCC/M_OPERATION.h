#pragma once
#include "IMode.h"

class M_OPERATION : public IMode
{
public :
	static M_OPERATION& getInstance();
	virtual void deploy(queue<string>&);
	virtual void start(queue<string>&);
	virtual void pause(queue<string>&);
	virtual void restart(queue<string>&);
	virtual void done(queue<string>&);

	M_OPERATION(const M_OPERATION& ref) = delete;
	M_OPERATION& operator=(const M_OPERATION& ref) = delete;

private:
	M_OPERATION() {};
	~M_OPERATION() {};
};

