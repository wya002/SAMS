#pragma once
#include <Simulator.h>
#include <TCC.h>

using namespace std;
using namespace System;

namespace TCCLibrary {
	public ref class WrapperClass
	{
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	public:
		void deploy(double x1, double y1, double x2, double y2, double mx, double my);

		double getATSX1() { return ATSX1; };
		double getATSX2() { return ATSX2; };
		double getATSY1() { return ATSY1; };
		double getATSY2() { return ATSY2; };
		double getMSSX() { return MSSX; };
		double getMSSY() { return MSSY; };

	private:
		void setATSX1(double a) { ATSX1 = a; };
		void setATSX2(double a) { ATSX2 = a; };
		void setATSY1(double a) { ATSY1 = a; };
		void setATSY2(double a) { ATSY2 = a; };
		void setMSSX(double a) { MSSX = a; };
		void setMSSY(double a) { MSSY = a; };

		double ATSX1, ATSX2, ATSY1, ATSY2, MSSX, MSSY;
		TCC* tcc = new TCC();

	};
}
