#include "Launcher.h"

void Launcher::launch()
{
	if (status == "START")
	{
		airThreat.launch();
	}
}
