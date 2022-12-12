#pragma once
struct Position
{
	double x;
	double y;
};

class ATS
{
public:
	void setCurPos(Position curPos, double setX, double setY);		// 공중위협 현재 위치를 설정오는 함수
	Position getCurPos(Position curPos);							// 공중위협 현재 위치를 가져오는 함수
private:
	int IP;
	Position curPos;
};

void ATS::setCurPos(Position curPos, double setX, double setY)		// 공중위협 위치를 설정하는 함수
{
	curPos.x = setX;
	curPos.y = setY;
}
Position ATS::getCurPos(Position curPos)							// 공중위협 위치를 가져오는 함수
{
	return curPos;
}
