#include "pch.h"
#include "TCCLibrary.h"

void TCCLibrary::WrapperClass::deploy(double x1, double y1, double x2, double y2, double mx, double my)
{
	tcc->deploy(x1,y1,x2,y2,mx,my);
}

void TCCLibrary::WrapperClass::Init()
{
	tcc->initTcc();
}


void TCCLibrary::WrapperClass::start()
{
	tcc->start();
}