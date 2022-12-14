#pragma once
#include "ScenarioManager.h"
#include "ATS.h"
#include "MSS.h"
#include "IMode.h"
#include <queue>
#include <string>

using namespace std;

class TCC
{
public:
	TCC();
	static void setMode(IMode& mode);
	IMode& getMode();
	ATS getATS();
	MSS getMSS();
	queue<string>& getMsgQueue();
	void start();
	void deploy();
	void pause();
	void restart();
	void done();


private:
	queue<string> mQueue;
	static IMode* mode;
	ScenarioManager senarioManager;
	ATS ats;              
	MSS mss;
};

