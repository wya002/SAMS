#include <iostream>
#include "ATS.h"

using namespace std;

int main()
{
	ATS ats;
	ats.setCurPos(3.23, 5.42);
	double x = ats.getCurPos().x;
	double y = ats.getCurPos().y;
	cout << x << " " << y << endl;
	return 0;
}
