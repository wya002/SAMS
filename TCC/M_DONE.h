#pragma once
#include "IMode.h"

class M_DONE : public IMode
{
public:
	static M_DONE& getInstance();
	virtual void deploy();
	virtual void start();
	virtual void pause();
	virtual void restart();
	virtual void done();

	M_DONE(const M_DONE& ref) = delete;
	M_DONE& operator=(const M_DONE& ref) = delete;

private:
	M_DONE() {};
	~M_DONE() {};
};