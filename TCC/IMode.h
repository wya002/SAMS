#pragma once
#include <queue>
#include <string>

using namespace std;

class IMode
{
public :
	virtual void deploy(queue<string>&) = 0;
	virtual void start(queue<string>&) = 0;
	virtual void pause(queue<string>&) = 0;
	virtual void restart(queue<string>&) = 0;
	virtual void done(queue<string>&) = 0;
};