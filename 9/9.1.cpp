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

typedef struct Node {
    int value;
    struct Node* next;
} Node;

void push(Node** head, int data) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}

void insert(Node* head, int pos, int item) {
    unsigned i = 0;
    Node* tmp = NULL;

    while (i < pos - 1 && head->next) {
        head = head->next;
        i++;
    }
    tmp = (Node*)malloc(sizeof(Node));
    tmp->value = item;
    if (head->next) {
        tmp->next = head->next;
    }
    else {
        tmp->next = NULL;
    }
    head->next = tmp;
    
}

Node* getLast(Node* head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

void pushBack(Node* head, int value) {
    Node* last = getLast(head);
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->value = value;
    tmp->next = NULL;
    last->next = tmp;
}

void createList(Node** head) {
    Node* tmp = NULL;

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
        push(&tmp, num);
    }

    *head = tmp;

}

void printLinkedList(const Node* head) {
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}


void pop(Node** head) {
    Node* prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->value;
    (*head) = (*head)->next;
    free(prev);
}

Node* getNth(Node* head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    return head;
}

void deleteNth(Node** head, int n) {
    if (n == 0) {
        pop(head);
    }
    else {
        Node* prev = getNth(*head, n - 1);
        Node* elm = prev->next;
        int val = elm->value;

        prev->next = elm->next;
        free(elm);
    }
}

void popBack(Node** head) {
    Node* pFwd = NULL;
    Node* pBwd = NULL;
    if (!head) {
        exit(-1);
    }

    if (!(*head)) {
        exit(-1);
    }

    pFwd = *head;
    while (pFwd->next) {
        pBwd = pFwd;
        pFwd = pFwd->next;
    }

    if (pBwd == NULL) {
        free(*head);
        *head = NULL;
    }
    else {
        free(pFwd->next);
        pBwd->next = NULL;
    }
}


void deleteList(Node** head) {
    Node* prev = NULL;
    while ((*head)->next) {
        prev = (*head);
        (*head) = (*head)->next;
        free(prev);
    }
    free(*head);
}

int length(Node* head) {
    int length = 0;

    if (head == NULL) {
        return length;
    }
    else {
        do {
            length++;
            head = head->next;
        } while (head);
    }

    return length;
}

void findExtreme(Node* head, int* min, int* max) {
    Node* MIN = head;
    Node* MAX = head;

    int minVal = MIN->value;
    int maxVal = MAX->value;

    while (head) {
        if (head->value < minVal) {
            minVal = head->value;
        }
        if (head->value > maxVal) {
            maxVal = head->value;
        }
        head = head->next;
    }

    printf("Минимальное число списка: %d\t\nМаксимальное число списка: %d\t\n", minVal, maxVal);
    *min = minVal;
    *max = maxVal;
}

Node* changeExtreme(Node* head, int min, int max) {
    Node* tmp = NULL;
    while (head) {

        if (head->value == min) {
            push(&tmp, max);
        }
        else if (head->value == max) {
            push(&tmp, min);
        }
        else {
            push(&tmp, head->value);
        }
        head = head->next;
    }

    return tmp;
}

Node* reverse(Node* head) {
    Node* tmp = NULL;
    while (head) {
        push(&tmp, head->value);
        head = head->next;
    }

    return tmp;
}

void main() {
    int mood = '1';

    int mortal;
    int size;
    int rate;
    int gount;

    int min;
    int max;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Node* reserve = NULL;
    Node* head = NULL;

    printf("Выберите один из следующих пунктов меню: \n");
    printf("[  1  ] Создане/пересоздание списка случайных целых чисел.\n");
    printf("[  2  ] Просмотр списка.\n");
    printf("[  3  ] Добавление нового элемента списка по указаной позиции.\n");
    printf("[  4  ] Удаление элемента списка по указанной позиции.\n");
    printf("[  5  ] Меняем местами элементы содержащие максимальное и минимальное значения.\n");
    printf("[  6  ] Вывод длинны списка.\n");
    printf("[  7  ] Удаление списка.\n");
    printf("[  8  ] Очистка консоли.\n");
    printf("[z | Z] Выход.\n");


    while (mood != 'Z' && mood != 'z') {
        printf("\nВыбираемый пункт меню: ");
        scanf_s("%c", &mood);
        getchar();

        switch (mood) {
        case '1':
            createList(&head);
            getchar();
            printf("Список создан.\n");
            break;
        case '2':
            mortal = length(head);

            if (mortal == 0) {
                printf("Список пуск.\n");
            }
            else {
                printLinkedList(head);
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

            size = length(head);
            if (posAdd == 0) {
                push(&head, itemAdd);
            }
            else {
                if (posAdd > size) {
                    printf("Так как введенный индекс элемента превышает/равен длинне списка Length = %d, элемент будет добавлен в конец.\n", size);
                }
                insert(head, posAdd, itemAdd);
            }
            break;
        case '4':
            int posDel;
            printf("Введите индекс удаляемого элемента, Index Del = ");
            scanf_s("%d", &posDel);
            getchar();

            rate = length(head);

            if (posDel < 0) {
                printf("Вводимое значение индекса должно быть положительным числом ... ");
            } else if (posDel >= 0 && posDel < rate) {
                deleteNth(&head, posDel);
            }
            else {
                if (posDel != rate) {
                    printf("Так как вводимая значение индекса удаляяемого элемента превышает/равно длинне списка, будет удален последний элемент списка.");
                }
                popBack(&head);
            }
            break;
        case '5':
            gount = length(head);
            
            if (gount < 2) {
                printf("Для выполнения обмена, значение длинны списка должно быть больше 1 ...");
            }
            else {
                findExtreme(head, &min, &max);
                head = changeExtreme(head, min, max);
                head = reverse(head);
            }

            break;
        case '6':
            printf("Длинна списка составляет length = %d\n", length(head));
            break;
        case '7':
            deleteList(&head);
            head = reserve;
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







