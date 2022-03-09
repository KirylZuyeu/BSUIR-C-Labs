#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfSrting(char* s) {
    int c = 0;
    while (*(s + c) != '\0') {
        c++;
    }
    return c;
}

char* filterOfDividedByThree(char* input, int stringLen) {
    char* str = input;
    char* output;
    int i = 0, j = 2, n = 0;

    output = new char[sizeof(char)];

    if (!output) {
        printf_s("Error allocating memory\n");
        exit(1);
    }

    while (i < stringLen) {
        if ((int)*(input + i) % 3 != 0) {
            *(output + n) = *(input + i);
            n++;
            j++;
            output = (char*)realloc(output, j * sizeof(char));

            if (str == NULL) {
                printf("Error allocating memory\n");
                delete[]output;
                exit(0);
            }
        }
        i++;
    }
    *(output + n) = '\0';
    return output;
}

char* dynamicstring() {
    char* str = NULL;
    int i = 0, j = 2, c;
    str = new char[sizeof(char)];

    if (!str) {
        printf_s("Error allocating memory\n");
        exit(1);
    }

    printf("Enter String : ");

    while ((c = getc(stdin)) && c != '\n') {
        *(str + i) = c;
        j++;
        i++;
        str = (char*)realloc(str, j * sizeof(char));

        if (str == NULL) {
            printf("Error allocating memory\n");
            delete[]str;
            exit(0);
        }
    }
    *(str + i) = '\0';
    return str;
}

void main() {
    char* inputString;
    char* resultString = NULL;
    int lengthInput;
    int lengthResult;
    inputString = dynamicstring();
    //printf("\nThe entered string is : %s \n", inputString);
    lengthInput = lengthOfSrting(inputString);
    printf("Length of the entered string: %d\n", lengthInput);

    if (lengthInput % 3 == 0) {
        resultString = filterOfDividedByThree(inputString, lengthInput);
        lengthResult = lengthOfSrting(inputString);
        printf("\nThe result string is : %s \n", resultString);
    }
    else {
        printf("\nThe result string is : %s \n", inputString);

    }



    delete[]inputString;
    delete[]resultString;

    return;
}