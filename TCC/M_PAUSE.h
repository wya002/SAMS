#pragma once
#include "IMode.h"

class M_PAUSE : public IMode
{
public :
	static M_PAUSE& getInstance();
	virtual void deploy();
	virtual void start();
	virtual void pause();
	virtual void restart();
	virtual void done();

	M_PAUSE(const M_PAUSE& ref) = delete;
	M_PAUSE& operator=(const M_PAUSE& ref) = delete;

private:
	M_PAUSE() {};
	~M_PAUSE() {};
};

