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
	cout << "���� �� �ó����� ������ �ʿ��մϴ�." << endl;
}

void M_IDLE::pause() {
	cout << "���� ���� �� �ߴ��� �Ұ��մϴ�." << endl;
}

void M_IDLE::restart() {
	cout << "���� �� �ó����� ������ �ʿ��մϴ�." << endl;
}

void M_IDLE::done() {
	cout << "���� ���� �� �ߴ��� �Ұ��մϴ�." << endl;
}


