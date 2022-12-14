#pragma once
#include "IMode.h"

class M_DONE : public IMode
{
public:
	static M_DONE& getInstance();
	virtual void deploy(queue<string>&);
	virtual void start(queue<string>&);
	virtual void pause(queue<string>&);
	virtual void restart(queue<string>&);
	virtual void done(queue<string>&);

	M_DONE(const M_DONE& ref) = delete;
	M_DONE& operator=(const M_DONE& ref) = delete;

private:
	M_DONE() {};
	~M_DONE() {};
};