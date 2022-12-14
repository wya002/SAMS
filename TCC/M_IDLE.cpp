#include "M_IDLE.h"
#include "M_STBY.h"
#include "TCC.h"
#include <iostream>

using namespace std;

M_IDLE& M_IDLE::getInstance() {
	static M_IDLE mode_idle;
	return mode_idle;
}

void M_IDLE::deploy(queue<string>& mQueue) {
	TCC::setMode(M_STBY::getInstance());
	cout << "IDLE -> STBY" << endl;
}

void M_IDLE::start(queue<string>& mQueue) {
	cout << "���� �� �ó����� ������ �ʿ��մϴ�." << endl;
}

void M_IDLE::pause(queue<string>& mQueue) {
	cout << "���� ���� �� �ߴ��� �Ұ��մϴ�." << endl;
}

void M_IDLE::restart(queue<string>& mQueue) {
	cout << "���� �� �ó����� ������ �ʿ��մϴ�." << endl;
}

void M_IDLE::done(queue<string>& mQueue) {
	cout << "���� ���� �� �ߴ��� �Ұ��մϴ�." << endl;
}


