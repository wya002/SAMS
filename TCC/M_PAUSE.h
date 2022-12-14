#pragma once
#include "IMode.h"

class M_PAUSE : public IMode
{
public :
	static M_PAUSE& getInstance();
	virtual void deploy(queue<string>&);
	virtual void start(queue<string>&);
	virtual void pause(queue<string>&);
	virtual void restart(queue<string>&);
	virtual void done(queue<string>&);

	M_PAUSE(const M_PAUSE& ref) = delete;
	M_PAUSE& operator=(const M_PAUSE& ref) = delete;

private:
	M_PAUSE() {};
	~M_PAUSE() {};
};

