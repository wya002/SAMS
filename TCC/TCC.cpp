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

ATS& TCC::getATS() 
{
	return ats;
}

MSS& TCC::getMSS()
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

void TCC::deploy(double ats_Init_x, double ats_Init_y, double ats_target_x, double ats_target_y, double mss_Init_x, double mss_Init_y)
{
	ats.setInitPosition({ ats_Init_x ,ats_Init_y });
	ats.setTargetPosition({ ats_target_x ,ats_target_y }); 
	mss.setInitPosition({ mss_Init_x ,mss_Init_y });

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

void TCC::initTcc()
{
	TCC tcc;


	UDP tccUdp = UDP(tcc.getATS().getPort(), &tcc.getTccMsgQueue(), &tcc.getMssMsgQueue());
	UDP mssUdp = UDP(tcc.getMSS().getPort(), &tcc.getTccMsgQueue(), &tcc.getMssMsgQueue());

	thread t([&]() { tccUdp.receiveData(); });
	//thread t2([&]() { mssUdp.receiveData(); });

	thread t3;
	bool finishedATSConnect = false;
	while (!finishedATSConnect)
		if (tccUdp.getReceived())
		{
			finishedATSConnect = true;
			t3 = thread([&]() { tccUdp.sendData(); });
		};

	//thread t4;
	//bool finishedMSSConnect = false;
	//while (!finishedMSSConnect)
	//	if (mssUdp.getReceived())
	//	{
	//		t4 = thread([&]() { mssUdp.sendData(); });
	//		finishedMSSConnect = true;
	//	};


	t.join();
	//t2.join();
	t3.join();
	//t4.join();
}