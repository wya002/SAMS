#include "ATS.h"

void ATS::setCurPos(double setX, double setY)			// 공중위협 현재 위치를 설정하는 함수
{
	curPos.x = setX;
	curPos.y = setY;
}

Position ATS::getCurPos()								// 공중위협 현재 위치를 가져오는 함수
{
	return curPos;
}
