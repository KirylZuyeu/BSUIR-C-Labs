#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <conio.h>
#include <math.h>
#include <process.h>

int createArr(double** array, int* size, int order) {
	int leng;
	double* arr;
	int i;

	if (order == 0) {
		printf_s("Enter size of the array: N = ");
	}
	else {
		printf_s("Enter size of the array: M = ");
	}
	scanf_s("%d", &leng);

	if (leng < 1) {
		printf_s("The length of array must be more then 0");
		exit(1);
	}

	arr = (double*)malloc(leng * sizeof(double));

	if (!arr) {
		printf_s("Out of memory. Press any key: ");
		exit(1);
	}

	printf_s("Enter values of array:\n");
	for (i = 0; i < leng; i++) {
		if (order == 0) {
			printf_s("arrA[%d] = ", i);
		}
		else {
			printf_s("arrB[%d] = ", i);
		}
		scanf_s("%lf", arr + i);
	}

	*size = leng;
	*array = arr;

	return 0;
}

int findMinArrIndex(double arr[], int size) {

	double minValue = *arr + 0;
	int index = 0;
	for (int i = 0; i < size; i++) {
		if (minValue > *arr + i) {
			minValue = *arr + i;
			index = i;
		}
	}

	return index;
}

void outPutArray(double* arr, int size, int minValue, int minIndex, int pointer) {
	if (pointer == 0) {
		printf_s("Array that contain the smallest element is A(N)\n");
	}
	else {
		printf_s("\nArray that contain the smallest element is B(M)\n");
	}
	printf_s("The array is: ");
	for (int i = 0; i < size; i++) {
		printf("%0.0lf ", *arr + i);
	}
	printf_s("\nMinimum value in array is = %d, and his index = %d\n", minValue, minIndex);
}

int main() {
	double* arrA, minAvalue;
	double* arrB, minBvalue;
	int arrSizeA, minAindex;
	int arrSizeB, minBindex;
	int order;

	// Array A

	order = 0;
	printf_s("Creating the first array A(N)\n");
	createArr(&arrA, &arrSizeA, order);

	// Array B
	order = 1;
	printf_s("Creating the second array B(M)\n");
	createArr(&arrB, &arrSizeB, order);


	minAindex = findMinArrIndex(arrA, arrSizeA);
	minAvalue = arrA[minAindex];

	minBindex = findMinArrIndex(arrB, arrSizeB);
	minBvalue = arrB[minBindex];

	if (minAvalue > minBvalue) {
		order = 1;
		outPutArray(arrB, arrSizeB, minBvalue, minBindex, order);
	}
	else if (minAvalue < minBvalue) {
		order = 0;
		outPutArray(arrA, arrSizeA, minAvalue, minAindex, order);
	}
	else if (minAvalue == minBvalue) {
		printf_s("Every array have the same smallest element, that equal = %0.0lf", minAvalue);
	}
	else {
		printf_s("incorrect data entered");
	}

	free(arrA);
	free(arrB);

	return 0;
}