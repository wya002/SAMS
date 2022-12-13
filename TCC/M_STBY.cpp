#include "M_STBY.h"
#include "M_OPERATION.h"
#include "TCC.h"
#include <iostream>

using namespace std;

M_STBY& M_STBY::getInstance() {
	static M_STBY mode_stby;
	return mode_stby;
}

void M_STBY::deploy() {
	cout << "이미 배포 상태입니다." << endl;
}

void M_STBY::start() {
	TCC::setMode(M_OPERATION::getInstance());
	cout << "STBY -> Start" << endl;
}

void M_STBY::pause() {
	cout << "모의 시작 전 중단은 불가합니다." << endl;
}

void M_STBY::restart() {
	start();
}

void M_STBY::done() {
	cout << "모의 시작 전 중단은 불가합니다." << endl;
}