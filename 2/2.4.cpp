#include <stdio.h>
#include <iostream>
using namespace std;

void main()
{
	double x;
	double y;
	double z;
	double s;
	double minTop;
	double maxXY;
	double maxYZ;
	
	// This is a verification that the entered number not a number
	printf_s("Your task is to enter different values ​​of the numbers x, y, z\n");
	inputAll:
	printf_s("Enter the value of a number, x = : ");
	if (scanf_s("%lf", &x) != 1) {
		printf_s("You entered not a number of x\n");
		return;
	}
	inputYZ:
	printf_s("Enter the value of a number, y = : ");
	if (scanf_s("%lf", &y) != 1) {
		printf_s("You entered not a number of y\n");
		return;
	}
	printf_s("Enter the value of a number, z = : ");
	if (scanf_s("%lf", &z) != 1) {
		printf_s("You entered not a number of z\n");
		return;
	}
	

	if (x == y || y == z || z == x) {
		printf_s("You need to enter different values of numbers x, y, z - do this again\n");
		goto inputAll;
	}

	maxXY = x > y ? x : y;
	maxYZ = y > z ? y : z;

	if (maxXY == maxYZ) {
		printf_s("You need to enter different values of numbers x, y, z with condition that x > y and/or z > y - do this again\n");
		goto inputAll;
	}

	minTop = maxXY > maxYZ ? maxYZ : maxXY;

	if (maxYZ == 0) {
		printf_s("You need to enter different values ​​of y and z with the condition that the largest among them will not be equal 0\n");
		goto inputYZ;
	}

	s = minTop / maxYZ;

	printf_s("The result of expression is, s = %lf\n", s);

	return;
}


