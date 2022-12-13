#include "M_OPERATION.h"
#include "M_PAUSE.h"
#include "M_DONE.h"
#include "TCC.h"
#include <iostream>

using namespace std;

M_OPERATION& M_OPERATION::getInstance() {
	static M_OPERATION mode_operation;
	return mode_operation;
}

void M_OPERATION::deploy() {
	cout << "���� ���α׷��� ����� �� ���� �����մϴ�." << endl;
}

void M_OPERATION::start() {
	cout << "���� ���α׷��� ���� ���� ���Դϴ�." << endl;
}

void M_OPERATION::pause() {
	//�ߴ� ó��
	TCC::setMode(M_PAUSE::getInstance());
	cout << "Operation -> Pause" << endl;
}

void M_OPERATION::restart() {
	cout << "���� ���α׷��� ���� ���� ���Դϴ�." << endl;
}

void M_OPERATION::done() {
	//������·� �ó����� ��� ����
	
	//�������� ���� ���ϸ� Cancle �̺�Ʈ �����ؾ���!!!
	 
	//���� ���� : cancle , ATS ��ǥ���� ����, M
	TCC::setMode(M_DONE::getInstance());
	cout << "Project End" << endl;
	cout << "Operation -> Done" << endl;
}