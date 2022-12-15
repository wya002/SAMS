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
	static void sendInitPos();
	IMode& getMode();
	ATS& getATS();
	MSS& getMSS();
	queue<string>& getTccMsgQueue();
	queue<string>& getMssMsgQueue();
	void initTcc();
	void start();
	void deploy(double ats_Init_x, double ats_Init_y, double ats_target_x, double ats_target_y, double mss_Init_x, double mss_Init_y);
	void pause();
	void restart();
	void done();

private:
	queue<string> atsMsgQueue;
	queue<string> mssMsgQueue;
	static IMode* mode;
	ScenarioManager senarioManager;
	ATS ats;              
	MSS mss;
};

