#include <iostream>
#include "Launcher.h"
#include "AirThreat.h"
#include "Tracking.h"

using namespace std;

int main()
{
	double initX = 10;
	double initY = 302.34;
	double targetX = 12.20;
	double targetY = 32.34;
	double atscurX;
	double atscurY;
	
	AirThreat at;
	at.setState();
	at.setInitPos({ initX, initY }, { targetX, targetY });
	at.setATSCurPos({ initX, initY });
	at.launch();
	at.launch();
	at.launch();
	at.launch();
	

	Launcher launcher;
	launcher.launch();
}
