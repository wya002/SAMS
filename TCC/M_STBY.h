#pragma once
#include "IMode.h"

class M_STBY : public IMode
{
public :
	static M_STBY& getInstance();
	virtual void deploy();
	virtual void start();
	virtual void pause();
	virtual void restart();
	virtual void done();

	M_STBY(const M_STBY& ref) = delete;
	M_STBY& operator=(const M_STBY& ref) = delete;

private:
	M_STBY() {};
	~M_STBY() {};
};