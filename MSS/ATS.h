#pragma once
struct Position
{
	double x;
	double y;
};

class ATS
{
public:
	void setCurPos(Position curPos, double setX, double setY);		// �������� ���� ��ġ�� �������� �Լ�
	Position getCurPos(Position curPos);							// �������� ���� ��ġ�� �������� �Լ�
private:
	int IP;
	Position curPos;
};

void ATS::setCurPos(Position curPos, double setX, double setY)		// �������� ��ġ�� �����ϴ� �Լ�
{
	curPos.x = setX;
	curPos.y = setY;
}
Position ATS::getCurPos(Position curPos)							// �������� ��ġ�� �������� �Լ�
{
	return curPos;
}
