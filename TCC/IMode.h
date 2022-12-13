#pragma once

class IMode
{
public :
	virtual void deploy() = 0;
	virtual void start() = 0;
	virtual void pause() = 0;
	virtual void restart() = 0;
	virtual void done() = 0;
};