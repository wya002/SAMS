#include <iostream>
#include "TCC.h"
#include "M_IDLE.h"

using namespace std;


IMode* TCC::mode = &M_IDLE::getInstance();

TCC::TCC()
{
	ats = ATS("192.168.0.100");
	mss = MSS("192.168.0.200");
}


void TCC::setMode(IMode& m)
{ 
	mode = &m; 
}

void TCC::start() 
{ 
	mode->start(); 
}

void TCC::deploy()
{
	mode->deploy();
}

void TCC::pause() 
{
	mode->pause();
}

void TCC::restart()
{
	mode->restart();
}

void TCC::done()
{
	mode->done();
}

int main()
{
	TCC tcc;
	while (true) {
		int number;

		cout << "1 : 배포\n2 : 시작\n3 : 중지\n4 : 재시작\n5:종료" << endl;
		cin >> number;

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
}
