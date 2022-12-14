#pragma once
#include "AirThreat.h"

class Launcher
{
public:
	void launch();
private:
	AirThreat airThreat;
	int oder = 0;	// 발사 명령 1 아니면 0
};