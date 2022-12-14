#pragma once

#include "Typedef.h"

class ATS
{
public:
	void setCurPos(double setX, double setY);		// 공중위협 현재 위치를 설정하는 함수
	Position getCurPos();							// 공중위협 현재 위치를 가져오는 함수
private:
	Position curPos;								// 공중위협 현재 위치
};
