#include <iostream>
#include "TCC.h"
#include "M_IDLE.h"
#include <typeinfo>
#include "UDP.h"

using namespace std;

IMode* TCC::mode = &M_IDLE::getInstance();

TCC::TCC()
{
	queue<string> tmp({ "helllloooooo", "I am", "Woojin", "how are you?", "i wanna go home" });
	mQueue = tmp;
	ats = ATS("127.0.0.1", 5000);
	mss = MSS("192.168.0.200", 9000);
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

queue<string>& TCC::getMsgQueue()
{
	return mQueue;
}

void TCC::start() 
{ 
	mode->start(mQueue);
}

void TCC::deploy()
{
	mode->deploy(mQueue);
}

void TCC::pause() 
{
	mode->pause(mQueue);
}

void TCC::restart()
{
	mode->restart(mQueue);
}

void TCC::done()
{
	mode->done(mQueue);
}

int main()
{
	TCC tcc;
	UDP udp = UDP(tcc.getATS().getPort(), &tcc.getMsgQueue());
	

	/*
	while (true) {
		int number;

		cout << "1 : 배포\n2 : 시작\n3 : 중지\n4 : 재시작\n5:종료" << endl;
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
	*/
	
}