#pragma once

#include "Typedef.h"

class ATS
{
public:
	void setACurPos(Position setAPos);				// �������� ���� ��ġ�� �����ϴ� �Լ�
	Position getACurPos();							// �������� ���� ��ġ�� �������� �Լ�
private:
	Position AcurPos;								// �������� ���� ��ġ
};
