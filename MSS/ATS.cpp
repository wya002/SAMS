#include "ATS.h"

void ATS::setACurPos(Position setAPos)					// 공중위협 현재 위치를 설정하는 함수
{
	AcurPos = setAPos;
}
Position ATS::getACurPos()								// 공중위협 현재 위치를 가져오는 함수
{
	return AcurPos;
}
