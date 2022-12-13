#include "M_PAUSE.h"
#include "M_OPERATION.h"
#include "TCC.h"
#include <iostream>

using namespace std;

M_PAUSE& M_PAUSE::getInstance() {
	static M_PAUSE mode_pause;
	return mode_pause;
}

void M_PAUSE::deploy() {
	cout << "모의 프로그램 종료 후 배포를 진행하세요." << endl;
}

void M_PAUSE::start() {
	restart();
}

void M_PAUSE::pause() {
	cout << "모의 프로그램이 현재 중지 상태입니다." << endl;
}

void M_PAUSE::restart() {
	//재시작 처리 
	TCC::setMode(M_OPERATION::getInstance());
	cout << "Pause -> Restart" << endl;
}

void M_PAUSE::done() {
	//종료처리
	cout << "Cancel Scenario" << endl;
	cout << "Pause -> Done" << endl;
}