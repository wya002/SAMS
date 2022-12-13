#pragma once
#include "Scenario.h"

class ScenarioManager
{
public :
	void save();
	void load();
	void getAirThreatScenario();
	void getMissileScenario();

private :
	Scenario airThreatScenario;
	Scenario missileScenario;
};

