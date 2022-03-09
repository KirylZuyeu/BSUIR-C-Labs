#include <stdio.h>
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

using namespace std;

void main()
{
	double t2;
	double n1;
	double n2;
	double sum;

	printf_s("Your task is to enter values ​​n1 and n2 and find value of t2\n");
	printf_s("Enter the value, n1 = : ");
	scanf_s("%lf", &n1);

	printf_s("Enter the value, n2 = : ");
	scanf_s("%lf", &n2);

	sum = n1 + n2;

	if (M_PI <= sum && sum < 5) {+
		printf_s("The t2 value calculated by, t2 = pow(sin((M_PI * n1 + exp(n2))), 2)\n");
		t2 = pow(sin((M_PI * n1 + exp(n2))), 2);
	}
	else if (sum >= 5) {
		printf_s("The t2 value calculated by, t2 = pow(sin((M_PI * n2 + n1)), 2)\n");
		t2 = pow(sin((M_PI * n2 + n1)), 2);
	}
	else {
		printf_s("Incorrect data entered, or the expression has no solution\n");
	}

	printf_s("The result of expression is, t2 = %lf\n", t2);

	return;
}
