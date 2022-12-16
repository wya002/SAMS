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

void TCCLibrary::WrapperClass::pause()
{
	tcc->pause();
}

void TCCLibrary::WrapperClass::done()
{
	tcc->done();
}
void TCCLibrary::WrapperClass::restart()
{
	tcc->restart();
}
void TCCLibrary::WrapperClass::launch()
{
	tcc->launch();
}
void TCCLibrary::WrapperClass::getConnect()
{
	this->atsConnect = tcc->getAtsConnect();
	this->mssConnect = tcc->getMssConnect();
}

