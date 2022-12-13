#pragma once
#include "ScenarioManager.h"
#include "ATS.h"
#include "MSS.h"
#include "IMode.h"

class TCC
{
public:
	TCC();
	static void setMode(IMode& mode);
	void start();
	void deploy();
	void pause();
	void restart();
	void done();


private:
	static IMode* mode;
	ScenarioManager senarioManager;
	ATS ats;
	MSS mss;
};

