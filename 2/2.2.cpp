#include <stdio.h>
#include <iostream>
using namespace std;

void main()
{
	double x, y, z, beta;
	x = 16.55e-3;
	y = -2.75;
	z = 0.15;

	beta = (sqrt(10 * (pow(x, 1. / 3) + pow(x, y + 2)))) * (pow(asin(z), 2) - fabs(x - y));

	printf_s("This is a result of beta = %f\n", beta);

	system("pause");
}

