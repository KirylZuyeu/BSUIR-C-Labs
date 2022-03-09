#include <stdio.h>
#include <iostream>

using namespace std;

void main()
{
	double a;
	double b;
	double h;
	int n;

	double S;
	double Y;
	double fabsYS;

	int fact;

	/*printf_s("Enter the value, a = : ");
	scanf_s("%lf", &a);
	printf_s("Enter the value, b = : ");
	scanf_s("%lf", &b);
	printf_s("Enter the value, h = : ");
	scanf_s("%lf", &h);
	printf_s("Enter the value, n = : ");
	scanf_s("%d", &n);*/

	a = 0.1;
	b = 1.0;
	h = 0.1;
	printf_s("Enter the value, n = : ");
	scanf_s("%d", &n);


	printf_s("\nTable of entered values \n");

	printf_s("|---------------------------------------|\n");
	printf_s("|    a    |    b    |    h    |    n    |\n");
	printf_s("|---------------------------------------|\n");
	printf_s("|   %.2lf  |   %.2lf  |   %.2lf  |    %d   |\n", a, b, h, n);
	printf_s("|---------------------------------------|\n\n");

	printf_s("Table of output calculations \n");

	printf_s("|-------------------------------------------|\n");
	printf_s("|    x    |   S(x)  |   Y(x)  | |Y(x)-S(x)| |\n");
	printf_s("|-------------------------------------------|\n");

	for (double x = a; x < b; x += h) {
		double S = 0;
		double total = 1;
		
		for (int k = 0; k <= n; k++) {
			if (k != 0) {
				total = total * k;
				S = S + ((2 * k + 1) / total * pow(x, 2 * k));
				continue;
			}
			else {
				S = S + total;
			}
			
		}
		Y = (1 + 2 * pow(x, 2)) * exp(pow(x, 2));
		fabsYS = fabs(Y - S);
		printf_s("|   %.2lf  |   %.2lf  |   %.2lf  |     %.2lf    |\n", x, S, Y, fabsYS);
	}

	printf_s("|-------------------------------------------|\n");

	return;
}
