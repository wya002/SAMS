#include "M_IDLE.h"
#include "M_STBY.h"
#include "TCC.h"
#include <iostream>

using namespace std;

M_IDLE& M_IDLE::getInstance() {
	static M_IDLE mode_idle;
	return mode_idle;
}

void M_IDLE::deploy() {
	TCC::setMode(M_STBY::getInstance());
	cout << "IDLE -> STBY" << endl;
}

void M_IDLE::start() {
	cout << "시작 전 시나리오 배포가 필요합니다." << endl;
}

void M_IDLE::pause() {
	cout << "모의 시작 전 중단은 불가합니다." << endl;
}

void M_IDLE::restart() {
	cout << "시작 전 시나리오 배포가 필요합니다." << endl;
}

void M_IDLE::done() {
	cout << "모의 시작 전 중단은 불가합니다." << endl;
}


