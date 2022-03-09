#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <iostream>

double searchExpression(double x) {
	return log(x) - 5 * pow(sin(x), 2);
}

void outputData(double startSection, double endSection, double crossingPoin, int numberOccurences) {
	printf("\n Section [%lf %lf]", startSection, endSection);
	printf("\n x = %lf  y= %lf.  Number of iteration: [%d] ", crossingPoin, searchExpression(crossingPoin), numberOccurences);
	printf("\n------------------------------------------------------------------------");
}

void iterationMethod(double startInterval, double a1, double eps, double b1, double endInterval) {
	int k = 1;

	for (a1; a1 < b1; a1 = a1 + eps) {
		if (fabs(searchExpression(a1)) < eps) {
			outputData(startInterval, endInterval, a1, k);
		}

		k++;
	}
}

void halfDivisionMethod(double startInterval, double a1, double eps, double b1, double endInterval) {
	int k = 1;
	while (fabs(searchExpression(a1)) > eps) {
		double c1 = (a1 + b1) / 2;
		if (searchExpression(a1) * searchExpression(c1) < 0)
		{
			b1 = c1;
		}
		else
		{
			a1 = c1;
		}
		k++;

	}
	outputData(startInterval, endInterval, a1, k);
}


void iterationAbstraction(double startInterval, double endInterval, double eps, double h, void(*f)(double, double, double, double, double)) {
	double c;

	for (startInterval; startInterval < endInterval; startInterval = startInterval + h) {
		c = startInterval + h;

		if (searchExpression(startInterval) * searchExpression(c) < 0){
			double a1 = startInterval;
			double b1 = c;
			f(startInterval, a1, eps, b1, c);
		}

	}
};


void main() {
	double a = 2;
	double b = 6;
	double eps = exp(-4);
	double h = (b - a) / 30;

	printf("************ Iteration method ******************\n");
	iterationAbstraction(a, b, eps, h, iterationMethod);

	printf("\n\n********* Intersection method ***********\n");
	iterationAbstraction(a, b, eps, h, halfDivisionMethod);

	return;
} 



