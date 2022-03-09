#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include<errno.h> 


#define PATH "firstInput.txt"

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
        str = (char*)realloc(str, j * sizeof(char));

        if (str == NULL) {
            printf("Error allocating memory\n");
            delete[]str;
            exit(0);
        }

        i++;
        j++;
    }
    *(str + i) = '\0';
    return str;
}

char* encryptor(char* input, int stringLen) {
    char* str = input;
    char* output;
    int i = 0, j = 2, n = 0;

    output = new char[sizeof(char)];

    if (!output) {
        printf_s("Error allocating memory\n");
        exit(1);
    }

    while (i < stringLen) {
        switch (str[i]) {
        case 'ñ':
        case 'ë':
        case 'ò':
            if (str[i + 1] == 'ó') {
                j += 3;
                output = (char*)realloc(output, j * sizeof(char));
                output[n] = 'ó';
                n++;
                output[n] = 'ó';
                n++;
                output[n] = str[i];
                n++;
            }
            else {
                j++;
                output = (char*)realloc(output, j * sizeof(char));
                output[n] = str[i];
                n++;
            }
            j++;
            output = (char*)realloc(output, j * sizeof(char));
            i++;
            break;
        default:
            j++;
            output = (char*)realloc(output, j * sizeof(char));
            output[n] = str[i];
            n++;
            break;
        }
        i++;
    }
    *(output + n) = '\0';
    return output;
}

char* decryptor(char* input, int stringLen) {
    char* str = input;
    char* output;
    int i = 0, j = 2, n = 0;

    output = new char[sizeof(char)];

    if (!output) {
        printf_s("Error allocating memory\n");
        exit(1);
    }

    while (i < stringLen) {
        if (str[i] == 'ó' && str[i + 1] == 'ó') {
            switch (str[i + 2]) {
            case 'ñ':
            case 'ë':
            case 'ò':
                j += 2;
                output = (char*)realloc(output, j * sizeof(char));
                output[n] = str[i + 2];
                n++;
                output[n] = 'ó';
                n++;
                i += 2;
                break;
            default:
                j++;
                output = (char*)realloc(output, j * sizeof(char));
                output[n] = str[i];
                n++;
                break;
            }
        }
        else {
            j++;
            output = (char*)realloc(output, j * sizeof(char));
            output[n] = str[i];
            n++;
        }
        i++;
    }
    *(output + n) = '\0';
    return output;
}

int lengthOfSrting(char* s) {
    int c = 0;
    while (*(s + c) != '\0') {
        c++;
    }
    return c;
}

void main() {
    char key = '1';

    //Encoding on console input/output 
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //Input stream
    char* stringFirstInput;
    FILE* fileFirstInput;
    int stringFirstLength;
    errno_t errFirst;
    //Output stream
    char* stringSecondOutput = NULL;
    FILE* fileSecondOutput;
    int stringSecondLength;
    errno_t errSecond;
    //Input stream
    char* stringThirdInput;
    FILE* fileThirdInput;
    int stringThirdLength;
    errno_t errThird;
    //Output stream
    char* stringFourthOutput = NULL;
    FILE* fileFourthOutput;
    int stringFourthOutputLength;
    errno_t errFourthOutput;
    //Input stream
    char* stringFourthInput;
    FILE* fileFourthInput;
    int stringFourthInputLength;
    errno_t errFourtInput;

    while (key != 'Z' && key != 'z') {
        printf("Select one of the following items: \n");
        printf("[  1  ] Dynamically creating of a string and writing it to the file.\n");
        printf("[  2  ] Read a string from a file and print it.\n");
        printf("[  3  ] Encryption of the string, save it in the file and print it.\n");
        printf("[  4  ] Read a srting from a file and print it.\n");
        printf("[  5  ] Decryption of a string and save it in the file.\n");
        printf("[  6  ] Cleaning of memory.\n");
        printf("[  7  ] Cleaning of console.\n");
        printf("[z | Z] Exit of a menu.\n");

        printf("Entering mose is: ");
        scanf_s("%c", &key);
        getchar();
        //fflush(stdin);
        switch (key) {
        case '1':
            //1.Dynamic string creation and save it in fileFirstInput.txt
            errFirst = fopen_s(&fileFirstInput, PATH, "wb+");
            if (errFirst == 0) {
                printf("\nThe file %s was opened\n", PATH);
            }
            else {
                printf("\nThe file 'firstInput.txt' was not opened\n");
            }

            stringFirstInput = dynamicstring();
            stringFirstLength = lengthOfSrting(stringFirstInput);
            fwrite(stringFirstInput, sizeof(char), stringFirstLength, fileFirstInput);

            // Close stream for fileFirstInput
            if (fileFirstInput) {
                errFirst = fclose(fileFirstInput);
                if (errFirst == 0) {
                    printf("The file 'firstInput.txt' was closed\n\n");
                }
                else {
                    printf("The file 'firstInput.txt' was not closed\n\n");
                }
            }
            free(stringFirstInput);
            break;
        case '2':
            //2.Read string from a file and print it out
            errSecond = fopen_s(&fileSecondOutput, "firstInput.txt", "rb+");
            if (errSecond == 0) {
                fseek(fileSecondOutput, 0, SEEK_END);
                stringSecondLength = ftell(fileSecondOutput);
                fseek(fileSecondOutput, 0, SEEK_SET);
                stringSecondOutput = (char*)malloc(stringSecondLength + 1);
                if (!stringSecondOutput) {
                    errSecond = fclose(fileSecondOutput);
                    exit(1);
                }
                fread(stringSecondOutput, 1, stringSecondLength, fileSecondOutput);
                printf("\nThe file 'firstInput.txt' for Second Task was opened\n");
            }
            else {
                printf("\nThe file 'firstInput.txt' for the Second Task was not opened\n");
            }

            printf("Output string from a file are: ");
            for (int i = 0; i < stringSecondLength; i++) {
                printf("%c", stringSecondOutput[i]);
            }

            // Close stream if it isn't NULL
            if (fileSecondOutput) {
                errSecond = fclose(fileSecondOutput);
                if (errSecond == 0) {
                    printf("\nThe file 'firstInput.txt' for the Second Task was closed\n\n");
                }
                else {
                    printf("\nThe file 'firstInput.txt' for the Second Task was not closed\n\n");
                }
            }
            break;
        case '3':
            //3.Encryption of the string and save it in file
            stringThirdInput = encryptor(stringSecondOutput, stringSecondLength);
            printf("\nString after encryption are: ");
            stringThirdLength = lengthOfSrting(stringThirdInput);
            for (int i = 0; i < stringThirdLength; i++) {
                printf("%c", stringThirdInput[i]);
            }

            errThird = fopen_s(&fileThirdInput, "thirdInput.txt", "wb+");
            if (errThird == 0) {
                printf("\nThe file 'thirdInput.txt' was opened\n");
            }
            else {
                printf("\nThe file 'thirdInput.txt' was not opened\n");
            }

            fwrite(stringThirdInput, sizeof(char), stringThirdLength, fileThirdInput);
            printf("String after encryption was saved in 'fileThirdInput.txt'");

            // Close stream if it isn't NULL
            if (fileThirdInput) {
                errThird = fclose(fileThirdInput);
                if (errThird == 0) {
                    printf("\nThe file 'thirdInput.txt' was closed\n\n");
                }
                else {
                    printf("\nThe file 'thirdInput.txt' was not closed\n\n");
                }
            }
            free(stringThirdInput);
            break;
        case '4':
            //4.1Decryptor of hte string and save it in file
            errFourthOutput = fopen_s(&fileFourthOutput, "thirdInput.txt", "rb+");
            if (errFourthOutput == 0) {
                printf("\nThe file 'thirdInput.txt' for Fourth Task was opened\n");
                fseek(fileFourthOutput, 0, SEEK_END);
                stringFourthOutputLength = ftell(fileFourthOutput);
                fseek(fileFourthOutput, 0, SEEK_SET);
                stringFourthOutput = (char*)malloc(stringFourthOutputLength + 1);
                if (!stringFourthOutput) {
                    errFourthOutput = fclose(fileFourthOutput);
                    exit(1);
                }

                fread(stringFourthOutput, 1, stringFourthOutputLength, fileFourthOutput);
            }
            else {
                printf("The file 'thirdInput.txt' for Fourth Task was not opened\n");
            }


            printf("Output string from a file are: ");
            for (int i = 0; i < stringFourthOutputLength; i++) {
                printf("%c", stringFourthOutput[i]);
            }

            // Close stream if it isn't NULL
            if (fileFourthOutput) {
                errFourthOutput = fclose(fileFourthOutput);
                if (errFourthOutput == 0) {
                    printf("\nThe file 'thirdInput.txt' for Fourth Task was closed\n\n");
                }
                else {
                    printf("\nThe file 'thirdInput.txt' for Fourth Task was not closed\n\n");
                }
            }


            break;
        case '5':
            //4.2 Write data in file
            errFourtInput = fopen_s(&fileFourthInput, "fourthInput.txt", "wb+");
            if (errFourtInput == 0) {
                printf("\nThe file 'fourthInput.txt' was opened");
            }
            else {
                printf("\nThe file 'fourthInput.txt' was not opened");
            }

            stringFourthInput = decryptor(stringFourthOutput, stringFourthOutputLength);
            printf("\nString after decryption are: ");
            stringFourthInputLength = lengthOfSrting(stringFourthInput);
            for (int i = 0; i < stringFourthInputLength; i++) {
                printf("%c", stringFourthInput[i]);
            }

            fwrite(stringFourthInput, sizeof(char), stringFourthInputLength, fileFourthInput);
            printf("\nString after decryption was saved in 'fourthInput.txt'");

            // Close stream if it isn't NULL
            if (fileFourthInput) {
                errFourtInput = fclose(fileFourthInput);
                if (errFourtInput == 0) {
                    printf("\nThe file 'fourthInput.txt' was closed\n\n");
                }
                else {
                    printf("\nThe file 'fourthInput.txt' was not closed\n\n");
                }
            }
            free(stringFourthInput);
            break;
        case '6':
            free(stringSecondOutput);
            free(stringFourthOutput);
            printf("\nMemory was cleaned.\n\n");
            break;
        case '7':
            system("cls");
            printf("Console was cleaned.\n\n");
            break;
        default:
            if (key != 'Z' && key != 'z') {
                system("cls");
                printf("You need to choose some operating mode, do this again.\n\n");
            }
            else {
                printf("\nMenu was closed.\n");
            }
            break;
        }
    }


    return;
}
