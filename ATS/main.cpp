#include <iostream>
#include "Launcher.h"
#include "AirThreat.h"
#include "Tracking.h"
#include "TCC.h"
#include "UDPSocket.h"
#include "main.h"

using namespace std;


int main()
{
	double initX = 10;
	double initY = 302.34;
	double targetX = 12.20;
	double targetY = 32.34;
	double atscurX;
	double atscurY;

	Launcher launcher;

	launcher.getAirThreat().setInitPos({ initX, initY }, { targetX, targetY });
	launcher.getAirThreat().setATSCurPos({ initX, initY });


	TCC tcc = TCC("127.0.0.1", 9000);
	UDPSocket udp = UDPSocket(tcc, launcher.getAirThreat());

	thread t([&]() { udp.sendData(); });
	thread t2([&]() { udp.receiveData(); });

	while (true)
	{
		if (!launcher.getisLaunched() && launcher.getAirThreat().getState() == State::START) {
			launcher.launch();
		}
	}

	t.join();
	t2.join();

}
