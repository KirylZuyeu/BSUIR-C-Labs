#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <conio.h>
#include <math.h>
#include <process.h>

int reduceRowElements(int **arr, int size) {
	int result = 0;
	for (int c = 0; c < size; c++) {
		result += *(*(arr + 0) + c);
	}

	return result;

}

void main() {
	int **arr;
	int N, M;
	int i, j, k, l;

	int sumOfFirstRowElem;

	printf_s("Enter number of rows, N = ");
	scanf_s("%d", &N);

	if (N < 2) {
		printf_s("The length of array must be more then 0");
		exit(1);
	}

	printf_s("Enter number of colums, M = ");
	scanf_s("%d", &M);

	if (M < 2) {
		printf_s("The length of row must be more then 0 | 1");
		exit(1);
	}

	//Allocation of memory for array
	if (!(arr = new int* [N])) {
		printf_s("Not enough memory");
		exit(0);
	}

	//Allocation of memory for elements of array
	for (int i = 0; i < N; i++) {
		if (!(arr[i] = new int[M])) {
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

	//Finding sum of element for the first row of array
	sumOfFirstRowElem = reduceRowElements(arr, M);
	printf_s("\nSum of the elements for the first row of the array is Sum = %d \n", sumOfFirstRowElem);

	//Clearing memory
	for (int i = 0; i < N; i++) {
		delete[](*(arr + i));
	}
	delete[]arr;

	return;
}