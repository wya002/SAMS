#include <iostream>
#include "TCC.h"
#include "M_IDLE.h"
#include <typeinfo>
#include "UDP.h"
#include <thread>

using namespace std;

IMode* TCC::mode = &M_IDLE::getInstance();

TCC::TCC()
{
	ats = ATS("192.168.0.150", 9000);
	mss = MSS("127.0.0.1", 5000);
}

ATS TCC::getATS() 
{
	return ats;
}

MSS TCC::getMSS()
{
	return mss;
}

void TCC::setMode(IMode& m)
{ 
	mode = &m; 
}

IMode& TCC::getMode()
{
	return *mode;
}

queue<string>& TCC::getTccMsgQueue()
{
	return atsMsgQueue;
}

queue<string>& TCC::getMssMsgQueue()
{
	return mssMsgQueue;
}

void TCC::start() 
{ 
	mode->start(&atsMsgQueue, &mssMsgQueue);
}

void TCC::deploy()
{
	mode->deploy(&atsMsgQueue, &mssMsgQueue, ats.getInitPosition(), ats.getTargetPosition(), mss.getInitPosition());
}

void TCC::pause() 
{
	mode->pause(&atsMsgQueue, &mssMsgQueue);
}

void TCC::restart()
{
	mode->restart(&atsMsgQueue, &mssMsgQueue);
}

void TCC::done()
{
	mode->done(&atsMsgQueue, &mssMsgQueue);
}


int main()
{
	TCC tcc;

	UDP tccUdp = UDP(tcc.getATS().getPort(), &tcc.getTccMsgQueue());
	UDP mssUdp = UDP(tcc.getMSS().getPort(), &tcc.getMssMsgQueue());

	thread t([&]() { tccUdp.receiveData(); });
	thread t2([&]() { mssUdp.receiveData(); });

	thread t3;
	bool finishedATSConnect = false;
	while (!finishedATSConnect)
		if (tccUdp.getReceived())
		{
			finishedATSConnect = true;
			t3 = thread([&]() { tccUdp.sendData(); });
		};

	thread t4;
	bool finishedMSSConnect = false;
	while (!finishedMSSConnect)
		if (mssUdp.getReceived())
		{
			t4 = thread([&]() { mssUdp.sendData(); });
			finishedMSSConnect = true;
		};

	while (true) {
		int number;

		cout << "\n1 : 배포\n2 : 시작\n3 : 중지\n4 : 재시작\n5:종료" << endl;
		cin >> number;

		cout << typeid(tcc.getMode()).name() << endl;

		switch (number) {
		case 1:
			tcc.deploy();
			break;
		case 2:
			tcc.start();
			break;
		case 3:
			tcc.pause();
			break;
		case 4:
			tcc.restart();
			break;
		case 5:
			tcc.done();
			break;

		}
	}
	t.join();
	t2.join();
	t3.join();
	t4.join();

}