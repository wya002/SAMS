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

void tracking::track()						// 대공유도탄 track
{

}
bool tracking::validateRadarRange()			// 레이다 탐지 여부 확인
{

}
