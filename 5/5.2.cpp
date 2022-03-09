#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <conio.h>
#include <math.h>
#include <process.h>

bool hasNegative(int** arr, int row, int sizeOfColums) {
	bool containNegative = false;
	for (int v = 0; v < sizeOfColums; v++) {
		if (*(*(arr + row) + v) < 0) {
			containNegative = true;
			break;
		}
	}

	return containNegative;
}

int reduceRowElements(int** arr, int row, int size) {
	int result = 0;
	for (int c = 0; c < size; c++) {
		result += *(*(arr + row) + c);
	}

	return result;
}

void main() {
	int** arr;
	int N, M;
	int i, j, k, l;

	int sumNegResult = 0;

	printf_s("Enter number of rows, N = ");
	scanf_s("%d", &N);

	if (N < 1) {
		printf_s("The length of array must be more then 0");
		exit(1);
	}

	printf_s("Enter number of colums, M = ");
	scanf_s("%d", &M);

	if (M < 1) {
		printf_s("The length of row must be more then 0");
		exit(1);
	}

	//Allocation of memory for array
	if (!(arr = (int**)malloc(sizeof(int*)*N))) {
		printf_s("Not enough memory");
		exit(0);
	}

	//Allocation of memory for elements of array
	for (int i = 0; i < N; i++) {
		if (!(*(arr + i) = (int*)malloc(sizeof(int)*M))) {
			printf_s("Not enough memory");
			delete[]arr;
			exit(0);
		}
	}

	// Filling of array
	for (i = 0; i < N; i++) {
		printf_s("Enter elements of row [%d]\n", i);

		for (j = 0; j < M; j++) {
			printf_s("arr[%d][%d] = ", i, j);
			scanf_s("%d", *(arr + i) + j);
		}
	}

	printf_s("----Array was created----\n");

	//Drawing table by elements of array
	for (i = 0; i < N; i++) {
		for (k = 0; k < M; k++) {
			printf_s(" -------");
		}
		printf_s("\n");
		for (j = 0; j < M; j++) {
			printf_s("|   %d   ", *(*(arr + i) + j));
		}
		printf_s("|");
		printf_s("\n");

		if (i == N - 1) {
			for (l = 0; l < M; l++) {
				printf_s(" -------");
			}
		}
	}

	//Finding sum of element for the rows that have negative elements
	for (int h = 0; h < N; h++) {
		if (hasNegative(arr, h, M)) {
			int sumRow = reduceRowElements(arr, h, M);
			sumNegResult += sumRow;
			printf_s("\nRow with index = %d has negative element and sum of elements for this row equal, Sum[arr[%d]] = %d\n", h, h, sumRow);
		}
	}

	if (sumNegResult != 0) {
		printf_s("\n The common sum of rows that have negative elements equal, CommonSum = %d \n", sumNegResult);
	}
	else {
		printf_s("\n The current array don't have negative elements.\n");
	}

	//Clearing memory
	for (int i = 0; i < N; i++) {
		free(*(arr + i));
	}
	free(arr);

	return;
}