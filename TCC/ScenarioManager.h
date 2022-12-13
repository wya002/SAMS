#pragma once
#include "Scenario.h"
#include "AirThreatScenario.h"
#include "MissileScenario.h"

class ScenarioManager
{
public :
	ScenarioManager() {};
	void save();
	void load();
	void getAirThreatScenario(Scenario airThreatScenario);
	void getMissileScenario();
	
private :
	AirThreatScenario airThreatScenario;
	MissileScenario missileScenario;
};

