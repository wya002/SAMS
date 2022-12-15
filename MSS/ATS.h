#pragma once

#include "Typedef.h"

class ATS
{
public:
	void setACurPos(Position setAPos);				// 공중위협 현재 위치를 설정하는 함수
	Position getACurPos();							// 공중위협 현재 위치를 가져오는 함수
private:
	Position AcurPos;								// 공중위협 현재 위치
};
