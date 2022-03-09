#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>

#include <conio.h>
#include <math.h>
#include <process.h>

int createArr(double** array, int* size) {
	int leng;
	double* arr;
	int i;

	printf_s("Enter size of the array: N = ");

	scanf_s("%d", &leng);

	if (leng < 1) {
		printf_s("The length of array must be more then 0");
		exit(1);
	}

	arr = new double[leng];

	if (!arr) {
		printf_s("Out of memory. Press any key: ");
		exit(1);
	}

	printf_s("Enter values of array:\n");
	for (i = 0; i < leng; i++) {
		printf_s("arrA[%d] = ", i);
		scanf_s("%lf", arr + i);
	}

	*size = leng;
	*array = arr;

	return 0;
}

void checkHasNegavite(double* arr, int size, int *posNegFirst, int *posNegSecond) {
	bool checkNegativFirst = false;
	bool checkNegativSecond = false;
	int indexFirst;
	int indexSecond;
	for (int i = 0; i < size; i++) {
		if (*(arr + i) < 0) {
			if (!checkNegativFirst) {
				checkNegativFirst = true;
				indexFirst = i;
				continue;
			}
			else {
				checkNegativSecond = true;
				indexSecond = i;
				break;
			}
		}
	}
	if (checkNegativFirst == false || checkNegativSecond == false) {
		printf_s("Doesn't have conditions of the current task, you need add two negative numbers at list. Try it again ...");
		exit(0);
	}

	*posNegFirst = indexFirst;
	*posNegSecond = indexSecond;

	return;
}

void outPutArray(double* arr, int size) {
	printf_s("The array is: ");
	for (int i = 0; i < size; i++) {
		printf("%0.0lf ", *(arr + i));
	}
}

double sumOnInterval(double* arr, int *posStart, int *posEnd) {
	int startIteration = *posStart + 1;
	int endIteration = *posEnd;
	double sum = 0;

	for (startIteration; startIteration < endIteration; startIteration++) {
		sum = sum + *(arr + startIteration);
	}

	return sum;
}

auto cloneArray(double* array, int size) {
	double* clone;
	clone = new double[size];
	for (int i = 0; i < size; ++i)
	{
		*(clone + i) = *(array + i);
	}
	printf_s("\nClone of array was created\n");
	return clone;
}

static int counterBubbleSort = 0;

void bubbleSort(double* arr, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = (size - 1); j > i; j--) {
			if (*(arr + j - 1) > *(arr + j)) {
				int temp = *(arr + j - 1);
				*(arr + j - 1) = *(arr + j);
				*(arr + j) = temp;
				counterBubbleSort++;
			}
		}
	}
}

static int counterHoaraSort = 0;

void hoaraSort(double* arr, int first, int last) {
	int i = first, j = last;
	double tmp, x = *(arr + ((first + last) / 2));

	do {
		while (*(arr + i) < x) {
			i++;
		}
		while (*(arr + j) > x) {
			j--;
		}
		if (i <= j) {
			if (i < j) {
				tmp = *(arr + i);
				*(arr + i) = *(arr + j);
				*(arr + j) = tmp;
				counterHoaraSort++;
			}
			i++;
			j--;
		}
	} while (i <= j);

	if (i < last) {
		hoaraSort(arr, i, last);
	}
	if (first < j) {
		hoaraSort(arr, first, j);
	}
}

int binarySearch(double* arr, int left, int right, int key) {
	int middle;

	if (left > right) {
		return -1;
	}
	middle = (left + right) / 2;

	if (*(arr + middle) == key) {
		return middle;
	}
	else if (key > *(arr + middle)) {
		return binarySearch(arr, middle + 1, right, key);
	}
	else {
		return binarySearch(arr, left, middle - 1, key);
	}
}

int main() {
	double* arr;
	int arrSize;
	int negativePosFirst;
	int negativePosSecond;

	int first;
	int last;

	double sumResult;

	double* cloneArr;

	double el;


	printf_s("Creating array A(N)\n");
	createArr(&arr, &arrSize);

	//Ñheck for compliance with the terms of the assignment
	checkHasNegavite(arr, arrSize, &negativePosFirst, &negativePosSecond);

	outPutArray(arr, arrSize);

	printf_s("\n\nFinding of the sum value between two first negative elements of array\n");
	sumResult = sumOnInterval(arr, &negativePosFirst, &negativePosSecond);
	printf_s("Sum = %0.0lf\n", sumResult);

	cloneArr = cloneArray(arr, arrSize);
	outPutArray(cloneArr, arrSize);


	//Bubble Sort
	printf_s("\n\nBubble Sort\n");

	// Start measuring time
	auto beginBubbleSort = std::chrono::high_resolution_clock::now();
	bubbleSort(arr, arrSize);
	// Stop measuring time and calculate the elapsed time
	auto endBubbleSort = std::chrono::high_resolution_clock::now();
	auto elapsedBubbleSort = std::chrono::duration_cast<std::chrono::nanoseconds>(endBubbleSort - beginBubbleSort);
	double timeBubbleSort = elapsedBubbleSort.count() * 1e-9;
	outPutArray(arr, arrSize);
	printf("\nThe time that take Bubble Sort measured: %.8f seconds.\n", timeBubbleSort);
	printf("The number of iteration that take Bubble Sort measured: %d\n", counterBubbleSort);

	//Hoara Sort
	printf_s("\n\nHoara Sort\n");
	first = 0;
	last = arrSize - 1;

	// Start measuring time
	auto beginHoaraSort = std::chrono::high_resolution_clock::now();
	hoaraSort(cloneArr, first, last);
	// Stop measuring time and calculate the elapsed time
	auto endHoaraSort = std::chrono::high_resolution_clock::now();
	auto elapsedHoaraSort = std::chrono::duration_cast<std::chrono::nanoseconds>(endHoaraSort - beginHoaraSort);
	double timeHoaraSort = elapsedBubbleSort.count() * 1e-9;
	outPutArray(cloneArr, arrSize);
	printf("\nThe time that take Hoara Sort measured: %.8f seconds.\n", timeHoaraSort);
	printf("The number of iteration that take Hoara Sort measured: %d\n", counterHoaraSort);

	if (timeBubbleSort > timeHoaraSort) {
		printf("\nAs we can see, that the Hoara Sort work faster then Bubble Sort.\n");
	}
	else if (timeBubbleSort < timeHoaraSort) {
		printf("\nAs we can see, that the Bubble Sort work faster then Hoara Sort.\n");
	}
	else {
		printf("\nAs we can see, that the Hoara Sort and Bubble Sort take equal time.\n");
	}

	if (counterBubbleSort > counterHoaraSort) {
		printf("\nAs we can see, that the Hoara Sort take less iteration then Bubble Sort.\n");
	}
	else if (counterBubbleSort < counterHoaraSort) {
		printf("\nAs we can see, that the Bubble Sort take less iteration then Hoara Sort.\n");
	}
	else {
		printf("\nAs we can see, that the Hoara Sort and Bubble Sort have equal number of iteration.\n");
	}


	printf_s("\nEnter the element, that need to find: ");
	scanf_s("%lf", &el);

	int index = binarySearch(arr, first, last, el);

	(index == -1) ? printf("Element is not present in array") : printf("Element is present at index %d", index);

	free(arr);
	free(cloneArr);

	return 0;
}