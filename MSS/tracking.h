#pragma once

struct Position
{
	double x;
	double y;
};

class tracking
{
public:
	void track();
	bool validateRadarRange();
private:
	int velX = 2;
	int velY = 2;
};

void tracking::track()						// �������ź track
{

}
bool tracking::validateRadarRange()			// ���̴� Ž�� ���� Ȯ��
{

}
