#include <stdio.h>
#include <iostream>


void main()
{
	double y;
	double z;
	double x;
	printf_s("Enter the value of number, z = ");

	if (scanf_s("%lf", &z) != 1) {
		printf_s("You entered not a number\n");
		return;
	}
	else if (z < 0) {
		x = z;
		printf_s("The value of x = %lf taken by branch, where x = z\n", x);
	}
	else {
		x = sin(z);
		printf_s("The value of x = %lf taken by branch, where x = sin(z)\n", x);
	}

	y = 2. / 3 * pow(sin(x), 2) - 3. / 4 * pow(cos(x), 2);

	printf_s("This is a result of y = %lf\n", y);


	return;
}

