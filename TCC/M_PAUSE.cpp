#include "M_PAUSE.h"
#include "M_OPERATION.h"
#include "TCC.h"
#include <iostream>

using namespace std;

M_PAUSE& M_PAUSE::getInstance() {
	static M_PAUSE mode_pause;
	return mode_pause;
}

void M_PAUSE::deploy(queue<string>& mQueue) {
	cout << "���� ���α׷� ���� �� ������ �����ϼ���." << endl;
}

void M_PAUSE::start(queue<string>& mQueue) {
	restart(mQueue);
}

void M_PAUSE::pause(queue<string>& mQueue) {
	cout << "���� ���α׷��� ���� ���� �����Դϴ�." << endl;
}

void M_PAUSE::restart(queue<string>& mQueue) {
	//����� ó�� 
	TCC::setMode(M_OPERATION::getInstance());
	cout << "Pause -> Restart" << endl;
}

void M_PAUSE::done(queue<string>& mQueue) {
	//����ó��
	cout << "Cancel Scenario" << endl;
	cout << "Pause -> Done" << endl;
}