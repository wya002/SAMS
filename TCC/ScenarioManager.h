#pragma once
#include "Scenario.h"

class ScenarioManager
{
public :
	ScenarioManager() {};
	void save();
	void load();
	void getAirThreatScenario();
	void getMissileScenario();

private :
	Scenario airThreatScenario;
	Scenario missileScenario;
};

