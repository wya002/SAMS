#pragma once
#include "IMode.h"

class M_OPERATION : public IMode
{
public :
	static M_OPERATION& getInstance();
	virtual void deploy();
	virtual void start();
	virtual void pause();
	virtual void restart();
	virtual void done();

	M_OPERATION(const M_OPERATION& ref) = delete;
	M_OPERATION& operator=(const M_OPERATION& ref) = delete;

private:
	M_OPERATION() {};
	~M_OPERATION() {};
};

