#pragma once
#include "IMode.h"

class M_STBY : public IMode
{
public :
	static M_STBY& getInstance();
	virtual void deploy(queue<string>&);
	virtual void start(queue<string>&);
	virtual void pause(queue<string>&);
	virtual void restart(queue<string>&);
	virtual void done(queue<string>&);

	M_STBY(const M_STBY& ref) = delete;
	M_STBY& operator=(const M_STBY& ref) = delete;

private:
	M_STBY() {};
	~M_STBY() {};
};