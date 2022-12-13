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
	cout << "���� ���α׷� ���� �� ������ �����ϼ���." << endl;
}

void M_PAUSE::start() {
	restart();
}

void M_PAUSE::pause() {
	cout << "���� ���α׷��� ���� ���� �����Դϴ�." << endl;
}

void M_PAUSE::restart() {
	//����� ó�� 
	TCC::setMode(M_OPERATION::getInstance());
	cout << "Pause -> Restart" << endl;
}

void M_PAUSE::done() {
	//����ó��
	cout << "Cancel Scenario" << endl;
	cout << "Pause -> Done" << endl;
}