#include "ATS.h"

void ATS::setCurPos(double setX, double setY)			// �������� ���� ��ġ�� �����ϴ� �Լ�
{
	curPos.x = setX;
	curPos.y = setY;
}

Position ATS::getCurPos()								// �������� ���� ��ġ�� �������� �Լ�
{
	return curPos;
}
