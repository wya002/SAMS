#pragma once

#include "Typedef.h"

class ATS
{
public:
	void setCurPos(double setX, double setY);		// �������� ���� ��ġ�� �����ϴ� �Լ�
	Position getCurPos();							// �������� ���� ��ġ�� �������� �Լ�
private:
	Position curPos;								// �������� ���� ��ġ
};
