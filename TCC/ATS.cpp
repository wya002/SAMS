#include "ATS.h"

ATS::ATS()
{
	targetPos = { 0,0 };
}

ATS::ATS(string addr) 
{
	ip = addr;
	targetPos = { 0,0 };
}

void ATS::setTargetPosition(Position pos)
{
	targetPos = pos;
}

Position ATS::getTargetPosition()
{
	return targetPos;
}