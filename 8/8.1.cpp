#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <Windows.h>
#include<errno.h> 

#define PATH "Library.dat"

typedef struct {
    int regNumber;
    char author[50];
    char name[50];
    int year;
    int numOfStr;
} BOOK;

typedef struct {
    BOOK* arr;
    size_t count;
} LIBRARY;

void createFile() {
    FILE* fileLibrary;
    errno_t errCreate;
    errCreate = fopen_s(&fileLibrary, PATH, "wb+");
    if (errCreate == 0) {
        printf("\nФайл %s создан/перезаписан.\n", PATH);
    }
    else {
        printf("\nФайл %s не создан.\n", PATH);
    }

    if (fileLibrary) {
        errCreate = fclose(fileLibrary);
    }
}

void saveFile(BOOK* st, int size) {
    FILE* fileLibrary;
    errno_t errSave;
    errSave = fopen_s(&fileLibrary, PATH, "rb+");

    if (fileLibrary) {
        if (errSave == 0) {
            for (int i = 0; i < size; i++) {
                fwrite(&st[i], sizeof(BOOK), 1, fileLibrary);
            }
        }
    }

    if (fileLibrary) {
        errSave = fclose(fileLibrary);
    }
}

void loadFile(LIBRARY* p) {
    FILE* fileLibrary;
    errno_t errLoad;
    int sizeLibrary;

    BOOK* e;
    errLoad = fopen_s(&fileLibrary, PATH, "rb+");
    if (errLoad == 0) {
        fseek(fileLibrary, 0, SEEK_END);
        sizeLibrary = ftell(fileLibrary);
        fseek(fileLibrary, 0, SEEK_SET);

        int size = sizeLibrary / sizeof(BOOK);

        e = (BOOK*)realloc(p->arr, size * sizeof(BOOK));
        p->arr = e;
        p->count = size;

        for (int i = 0; i < size; i++) {
            fread(&p->arr[i], sizeof(BOOK), 1, fileLibrary);
        }
    }

    if (fileLibrary) {
        errLoad = fclose(fileLibrary);
    }
}


static void addBook(LIBRARY* p) {
    BOOK* e;

    e = (BOOK*)realloc(p->arr, (p->count + 1) * sizeof(BOOK));

    p->arr = e;
    e = &p->arr[p->count];

    printf("Введите регистрационный номер %d книги : ", p->count + 1);
    scanf_s("%d", &(e->regNumber));
    getchar();
    printf("Введите автора %d книги : ", p->count + 1);
    gets_s(e->author);
    printf("Введите имя %d книги : ", p->count + 1);
    gets_s(e->name);
    printf("Введите год издания %d книги : ", p->count + 1);
    scanf_s("%d", &(e->year));
    printf("Введите количество страниц %d книги : ", p->count + 1);
    scanf_s("%d", &(e->numOfStr));
    getchar();

    p->count++;

}

static void deleteBook(LIBRARY* p) {
    int size = p->count;
    int i, pos;

    /* Input element position to delete */
    printf("Введите позицию удаляемой книги:");
    scanf("%d", &pos);
    getchar();

    if (pos < 0 || pos > size) {
        printf("Неверноя позиция! Выбирайте позицию от 1 до %d", size);
    }
    else {
        for (i = pos - 1; i < size - 1; i++) {
            p->arr[i].regNumber = p->arr[i + 1].regNumber;
            memcpy(&p->arr[i].author, &p->arr[i + 1].author, sizeof(p->arr[i + 1].author));
            memcpy(&p->arr[i].name, &p->arr[i + 1].name, sizeof(p->arr[i + 1].name));
            p->arr[i].year = p->arr[i + 1].year;
            p->arr[i].numOfStr = p->arr[i + 1].numOfStr;
        }
        p->count--;
    }
}

static void changeBook(LIBRARY* p) {
    int pos;

    printf("Введите позицию изменяемой книги:");
    scanf("%d", &pos);
    getchar();
    printf("Введите регистрационный номер %d книги : ", pos);
    scanf_s("%d", &(p->arr[pos - 1].regNumber));
    getchar();
    printf("Введите автора %d книги : ", pos);
    gets_s(p->arr[pos - 1].author);
    printf("Введите имя %d книги : ", pos);
    gets_s(p->arr[pos - 1].name);
    printf("Введите год издания %d книги : ", pos);
    scanf_s("%d", &(p->arr[pos - 1].year));
    printf("Введите количество страниц %d книги : ", pos);
    scanf_s("%d", &(p->arr[pos - 1].numOfStr));
    getchar();

}


static void copyLibrary(LIBRARY* p, LIBRARY* b) {
    int sizeLibrary;
    b->arr = NULL;
    b->count = 0;

    BOOK* e;

    int size = sizeof(BOOK) * p->count / sizeof(BOOK);

    e = (BOOK*)calloc(size, sizeof(BOOK));

    b->arr = e;

    for (int i = 0; i < p->count; i++) {
        b->arr[i].regNumber = p->arr[i].regNumber;
        memcpy(&b->arr[i].author, &p->arr[i].author, strlen(p->arr[i].author));
        memcpy(&b->arr[i].name, &p->arr[i].name, strlen(p->arr[i].name));
        b->arr[i].year = p->arr[i].year;
        b->arr[i].numOfStr = p->arr[i].numOfStr;
        b->count++;
    }
}

static void sortLibraryByYear(LIBRARY* b) {
    int i, j;
    BOOK* temp;

    temp = (BOOK*)calloc(1, sizeof(BOOK));

    for (i = 0; i < b->count - 1; i++) {
        for (j = 0; j < (b->count - 1 - i); j++) {
            if (b->arr[j].year > b->arr[j + 1].year) {
                *temp = b->arr[j];
                b->arr[j] = b->arr[j + 1];
                b->arr[j + 1] = *temp;
            }
        }
    }
};

static void filterLibrary(LIBRARY* b, LIBRARY* f) {
    int pos;
    int index = 0;

    printf("Введите год, по которому будут фильтроваться записи: ");
    scanf("%d", &pos);
    getchar();
    BOOK* e;

    f->arr = NULL;
    f->count = 0;

    for (int i = 0; i < b->count; i++) {
        if (pos < b->arr[i].year) {
            e = (BOOK*)realloc(f->arr, (f->count + 1) * sizeof(BOOK));

            f->arr = e;

            f->arr[index].regNumber = b->arr[i].regNumber;
            memcpy(f->arr[index].author, b->arr[i].author, sizeof(b->arr[i].author));
            memcpy(f->arr[index].name, b->arr[i].name, sizeof(b->arr[i].name));
            f->arr[index].year = b->arr[i].year;
            f->arr[index].numOfStr = b->arr[i].numOfStr;
            index++;
            f->count++;
        }
    }

};

static void sortLibraryByAuthor(LIBRARY* b) {
    int i, j;
    BOOK* temp;

    temp = (BOOK*)calloc(1, sizeof(BOOK));
    if (b->count > 1) {
        for (i = 0; i < b->count - 1; i++) {
            for (j = 0; j < (b->count - 1 - i); j++) {
                if (strcmp(b->arr[j].author, b->arr[j + 1].author) > 0) {
                    *temp = b->arr[j];
                    b->arr[j] = b->arr[j + 1];
                    b->arr[j + 1] = *temp;
                }

            }
        }
    }
};

void main(void) {
    char key = '1';

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    LIBRARY p;
    size_t i;

    LIBRARY b;
    LIBRARY f;

    /* Initialize */
    p.arr = NULL;
    p.count = 0;

    printf("Выберите один из следующих пунктов меню: \n");
    printf("[  1  ] Создане нового файла библиотеки.\n");
    printf("[  2  ] Просмотр файла библиотеки.\n");
    printf("[  3  ] Добавление новой записи книги в файле библиотеки.\n");
    printf("[  4  ] Изменение записи книги в файле библиотеки.\n");
    printf("[  5  ] Удаление записи книги из файла библиотеки.\n");
    printf("[  6  ] Вывод записей книг изданных посде выбранного года, в алфавитном порядке.\n");
    printf("[  7  ] Очистка консоли.\n");
    printf("[z | Z] Выход.\n");


    while (key != 'Z' && key != 'z') {
        printf("\nВыбираемый пункт меню: ");
        scanf_s("%c", &key);
        getchar();

        switch (key) {
        case '1':
            createFile();
            break;
        case '2':
            saveFile(p.arr, p.count);
            loadFile(&p);

            if (p.count == 0) {
                printf("\nФайл %s пуст.\n", PATH);
            }
            else {
                for (i = 0; i < p.count; i++) {
                    BOOK* book = &p.arr[i];
                    printf("%-5d %-5d %-20s %-20s %5d %5d \n", i + 1, (*book).regNumber, (*book).author, (*book).name, (*book).year, (*book).numOfStr);
                }
            }
            break;
        case '3':
            loadFile(&p);
            addBook(&p);
            saveFile(p.arr, p.count);
            break;
        case '4':
            loadFile(&p);
            changeBook(&p);
            saveFile(p.arr, p.count);
            break;
        case '5':
            loadFile(&p);
            deleteBook(&p);
            createFile();
            saveFile(p.arr, p.count);
            break;
        case '6':
            copyLibrary(&p, &b);
            sortLibraryByYear(&b);
            filterLibrary(&b, &f);
            sortLibraryByAuthor(&f);
            for (i = 0; i < f.count; i++) {
                BOOK* book = &f.arr[i];
                printf("%-5d %-5d %-20s %-20s %5d %5d \n", i + 1, (*book).regNumber, (*book).author, (*book).name, (*book).year, (*book).numOfStr);
            }
            break;
        case '7':
            system("cls");
            printf("Консоль очищена.\n\n");
            break;
        default:
            if (key != 'Z' && key != 'z') {
                system("cls");
                printf("Вам следует выбрать один из режимов, повторите еще раз ...\n\n");
            }
            else {
                printf("\nМеню закрыто.\n");
            }
            break;
        }
    }
    return;
}