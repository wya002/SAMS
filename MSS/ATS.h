#pragma once

struct Position
{
	double x;
	double y;
};

class ATS
{
public:
	void setCurPos(double setX, double setY);		// �������� ���� ��ġ�� �����ϴ� �Լ�
	Position getCurPos();							// �������� ���� ��ġ�� �������� �Լ�
private:
	Position curPos;
};
