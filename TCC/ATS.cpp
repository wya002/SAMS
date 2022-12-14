#include "ATS.h"

ATS::ATS()
{
	targetPos = { 0,0 };
}

ATS::ATS(const char * addr, int portNo)
{
	ip = addr;
	port = portNo;
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