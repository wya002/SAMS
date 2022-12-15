#pragma once
#include "AirThreat.h"

class Launcher
{
public:
	Launcher();
	~Launcher();
	void launch();
	bool getisLaunched();
	AirThreat& getAirThreat();

private:
	AirThreat airThreat;
	bool isLaunched;
};