#include <stdio.h>
#include <iostream>
using namespace std;

void main()
{
	double alpha, z1, z2;

	scanf_s("%f", &alpha);

	z1 = cos(alpha) + cos(2 * alpha) + cos(6 * alpha) + cos(7 * alpha);
	z2 = 4 * cos(alpha / 2) * cos((5. / 2) * alpha) * cos(4 * alpha);

	printf_s("This is a result of z1 = %g", z1);
	printf_s("This is a result of z2 = %g", z2);

	system("pause");
}

