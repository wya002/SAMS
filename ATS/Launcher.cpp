#include "TCC.h"
#include "UDPSocket.h"
#include "Launcher.h"

Launcher::Launcher()
{
	isLaunched = false;
}

Launcher::~Launcher() {}

void Launcher::launch()
{
	isLaunched = true;
	airThreat.launch();
}

AirThreat& Launcher::getAirThreat()
{
	return airThreat;
}

bool Launcher::getisLaunched()
{
	return isLaunched;
}

