#include "M_DONE.h"
#include "M_IDLE.h"
#include "TCC.h"
#include <iostream>

using namespace std;

M_DONE& M_DONE::getInstance() {
	static M_DONE mode_done;
	return mode_done;
}

void M_DONE::deploy() {

}

void M_DONE::start() {

}

void M_DONE::pause() {

}

void M_DONE::restart() {

}

void M_DONE::done() {
	//종료 조건 처리
	TCC::setMode(M_IDLE::getInstance());
	cout << "Done -> Idle" << endl;
}


