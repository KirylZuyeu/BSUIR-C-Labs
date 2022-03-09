#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Node {
    int value;
    struct _Node* next;
    struct _Node* prev;
} Node;


typedef struct _DblList {
    size_t size;
    Node* head;
    Node* tail;
} DblList;


void initializeDblList(DblList** list) {
    DblList* tmp = NULL;
    tmp = (DblList*)malloc(sizeof(DblList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    *list = tmp;
}

void pushFront(DblList* list, int data) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->value = data;
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;

    if (list->tail == NULL) {
        list->tail = tmp;
    }
    list->size++;
}

void createDblList(DblList* list) {
    int N;
    printf("Создание списка...\n");
    printf("Введите количество элементов списка: ");
    scanf_s("%d", &N);
    srand(time(0));

    if (N == 0) {
        return;
    }

    while (N-- != 0) {
        int num;
        num = rand() % 100;
        pushFront(list, num);
    }
}

void printDblList(DblList* list) {
    Node* tmp = list->head;
    while (tmp) {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

Node* getNthq(DblList* list, size_t index) {
    Node* tmp = NULL;
    size_t i;

    if (index < list->size / 2) {
        i = 0;
        tmp = list->head;
        while (tmp && i < index - 1) {
            tmp = tmp->next;
            i++;
        }
    }
    else {
        i = list->size - 1;
        tmp = list->tail;
        while (tmp && i > index) {
            tmp = tmp->prev;
            i--;
        }
    }

    return tmp;
}


void insert(DblList* list, size_t index, int value) {
    Node* elm = NULL;
    Node* ins = NULL;
    elm = getNthq(list, index);
    if (elm == NULL) {
        exit(5);
    }
    ins = (Node*)malloc(sizeof(Node));
    ins->value = value;
    ins->prev = elm;
    ins->next = elm->next;
    if (elm->next) {
        elm->next->prev = ins;
    }
    elm->next = ins;

    if (!elm->prev) {
        list->head = elm;
    }
    if (!elm->next) {
        list->tail = elm;
    }

    list->size++;
}


void pushBack(DblList* list, int value) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(3);
    }
    tmp->value = value;
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}


int popFront(DblList* list) {
    Node* prev;
    int tmp;
    if (list->head == NULL) {
        exit(2);
    }

    prev = list->head;
    list->head = list->head->next;
    if (list->head) {
        list->head->prev = NULL;
    }
    if (prev == list->tail) {
        list->tail = NULL;
    }
    tmp = prev->value;
    free(prev);

    list->size--;
}

void deleteNth(DblList* list, size_t index) {
    if (index == 0) {
        popFront(list);
    }
    else {
        Node* elm = NULL;
        int tmp = NULL;
        elm = getNthq(list, index);
        if (elm == NULL) {
            exit(5);
        }
        if (elm->prev) {
            elm->prev->next = elm->next;
        }
        if (elm->next) {
            elm->next->prev = elm->prev;
        }
        tmp = elm->value;

        if (!elm->prev) {
            list->head = elm->next;
        }
        if (!elm->next) {
            list->tail = elm->prev;
        }
        free(elm);
        list->size--;
    }
}

void popBack(DblList* list) {
    Node* next;
    int tmp;
    if (list->tail == NULL) {
        exit(4);
    }
    next = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) {
        list->tail->next = NULL;
    }
    if (next == list->head) {
        list->head = NULL;
    }
    tmp = next->value;
    free(next);

    list->size--;
}

void deleteDblList(DblList** list) {
    Node* tmp = (*list)->head;
    Node* next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

int length(DblList* list) {
    int length = 0;

    if (list == NULL) {
        return length;
    }
    else {
        length = list->size;
    }
    return length;
}

void findMin(DblList* list, int* min) {
    Node* tmp = list->head;
    int minVal = tmp->value;
    int minIndex = list->size;
    while (tmp) {
        if (minVal > tmp->value) {
            minVal = tmp->value;
        }
        tmp = tmp->next;
    }

    printf("Минимальное число двунаправленного списка, MIN = %d\t\n", minVal);
    *min = minVal;
}

void createTillMin(DblList** taskDblList, DblList* list, int min) {
    Node* tmp = list->head;
    DblList* ntmp = NULL;

    ntmp = (DblList*)malloc(sizeof(DblList));
    ntmp->size = 0;
    ntmp->head = ntmp->tail = NULL;

    int num;
    do {
        num = tmp->value;
        pushBack(ntmp, num);
        tmp = tmp->next;
    } while (num != min);

    *taskDblList = ntmp;
}


void main() {
    int mood = '1';

    int mortal;
    int size;
    int rate;
    int gount;

    int min;
    int index;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    DblList* list = NULL;
    DblList* reserve = NULL;

    DblList* taskList = NULL;

    printf("Выберите один из следующих пунктов меню: \n");
    printf("[  1  ] Создане/пересоздание двунаправленного списка случайных целых чисел.\n");
    printf("[  2  ] Просмотр двунаправленного списка.\n");
    printf("[  3  ] Добавление нового элемента двунаправленного списка по указаному индексу.\n");
    printf("[  4  ] Удаление элемента двунаправленного списка по указанному индексу.\n");
    printf("[  5  ] Удаление элементов двунаправленного списка, находящихся после минимального элемента.\n");
    printf("[  6  ] Вывод длинны двунаправленного списка.\n");
    printf("[  7  ] Удаление двунаправленного списка.\n");
    printf("[  8  ] Очистка консоли.\n");
    printf("[z | Z] Выход.\n");


    while (mood != 'Z' && mood != 'z') {
        printf("\nВыбираемый пункт меню: ");
        scanf_s("%c", &mood);
        getchar();

        switch (mood) {
        case '1':
            initializeDblList(&list);
            createDblList(list);
            getchar();
            printf("Двунаправленный писок создан.\n");
            break;
        case '2':
            mortal = length(list);
            if (mortal == 0) {
                printf("Двунаправленный cписок пуск.\n");
            }
            else {
                printDblList(list);
            }
            break;
        case '3':
            int posAdd;
            int itemAdd;
            printf("Введите индекс добавления элемента, Index Add = ");
            scanf_s("%d", &posAdd);
            printf("Введите значение добавляемого элемента: ");
            scanf_s("%d", &itemAdd);
            getchar();

            size = length(list);
            if (posAdd == 0) {
                pushFront(list, itemAdd);
            }
            else {
                if (posAdd >= size) {
                    printf("Так как введенный индекс элемента превышает/равен длинне двунаправленного списка Length = %d, элемент будет добавлен в конец.\n", size);
                }
                insert(list, posAdd, itemAdd);
            }
            break;
        case '4':
            int posDel;
            printf("Введите индекс удаляемого элемента, Index Del = ");
            scanf_s("%d", &posDel);
            getchar();

            rate = length(list);

            if (posDel < 0) {
                printf("Вводимое значение индекса должно быть положительным числом ... ");
            }
            else if (posDel >= 0 && posDel < rate) {
                deleteNth(list, posDel);
            }
            else {
                if (posDel != rate) {
                    printf("Так как вводимое значение индекса удаляяемого элемента превышает/равен длинне списка, будет удален последний элемент списка.");
                }
                popBack(list);
            }
            break;
        case '5':
            gount = length(list);

            if (gount < 1) {
                printf("Для удаления элементов списка после наbменьшего значения, длинны списка должно быть больше 0 ...");
            }
            else {
                findMin(list, &min);
                createTillMin(&taskList, list, min);
            }

            list = taskList;
            break;
        case '6':
            printf("Длинна двунаправленного списка составляет length = %d\n", length(list));
            break;
        case '7':
            if (list != NULL) {
                deleteDblList(&list);
            }
            list = reserve;
            break;
        case '8':
            system("cls");
            printf("Консоль очищена.\n\n");
            break;
        default:
            if (mood != 'Z' && mood != 'z') {
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

