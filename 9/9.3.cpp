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
    int key;
    char fullName[30];
    char pasport[30];
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;


Node* getFreeNode(int value, Node* parent) {
    Node* tmp = (Node*)malloc(sizeof(Node));

    printf("Введите Ф.И.О. key = %d элемента структуры: ", value);
    gets_s(tmp->fullName);
    printf("Введите серию паспорта key = %d элемента структуры: ", value);
    gets_s(tmp->pasport);

    tmp->left = tmp->right = NULL;
    tmp->key = value;

    printf("\n");

    tmp->parent = parent;
    return tmp;
}

Node* getNodeByValue(Node* root, int value) {
    while (root) {
        if (root->key > value) {
            root = root->left;
            continue;
        }
        else if (root->key < value) {
            root = root->right;
            continue;
        }
        else {
            return root;
        }
    }
    return NULL;
}

void insert(Node** head) {
    int value;

    printf("Введите key значиние добавляемого элемента: ");
    scanf_s("%d", &value);
    getchar();

    Node* target = getNodeByValue(*head, value);
    if (target != NULL) {
        printf("Введенное значение будет проигнорировано, тк дерево уже содержит такое значение кулюча.\n");
        printf("Новый элемент не добавлен.\n");
        return;
    }

    Node* tmp = NULL;
    Node* ins = NULL;
    if (*head == NULL) {
        *head = getFreeNode(value, NULL);
        return;
    }



    tmp = *head;
    while (tmp) {
        if (value > tmp->key) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            }
            else {
                tmp->right = getFreeNode(value, tmp);
                return;
            }
        }
        else if (value < tmp->key) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            }
            else {
                tmp->left = getFreeNode(value, tmp);
                return;
            }
        }
        else {
            printf("Некоректно введенны данные.");
            return;
        }

    }
}

void getMaxLeft(Node** root, int * maxValueLeft) {
    Node* tmp = (*root)->left;
    if (tmp) {
        int maxOfLeft = tmp->key;
        while (tmp) {
            if (maxOfLeft < tmp->key) {
                maxOfLeft = tmp->key;
            }
            tmp = tmp->right;
        }

        printf("Максимальное значение ключа левой ветви maxLeft = %d\n", maxOfLeft);
        *maxValueLeft = maxOfLeft;
    }
    else {
        printf("Левая ветвь дерева пуста.");
    }
}


Node* getMinNode(Node* root) {
    while (root->left) {
        root = root->left;
    }
    return root;
}

Node* getMaxNode(Node* root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}


void printByKey(Node* root) {
    int targetKey;
    printf("Введите key интересующего элемента списка: ");
    scanf_s("%d", &targetKey);
    getchar();

    Node* target = getNodeByValue(root, targetKey);

    printf("key = %d, fullname = %s, pasportNumber = %s\n", target->key, target->fullName, target->pasport);
}

void removeNodeByPtr(Node* target) {
    if (target->left && target->right) {
        Node* localMax = getMaxNode(target->left);
        target->key = localMax->key;
        removeNodeByPtr(localMax);
        return;
    }
    else if (!target->parent) {
        printf("Вы пытаетесь удалить корень дерева, для данной функции подойдет пункт меню номер 7.");
    }
    else if (target->left) {
        if (target == target->parent->left) {
            target->parent->left = target->left;
        }
        else {
            target->parent->right = target->left;
        }
        free(target);
    }
    else {
        if (target == target->parent->right) {
            target->parent->right = target->right;
        }
        else {
            target->parent->left = target->right;
        }
        free(target);
    }
}

void deleteTree(Node* root) {
    if (root == NULL) return;

    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

void deleteValue(Node* root) {
    int targetKey;
    printf("Введите key удаляемого элемента списка: ");
    scanf_s("%d", &targetKey);
    getchar();
    Node* target = getNodeByValue(root, targetKey);
    removeNodeByPtr(target);
}

void deleteSide(Node* root) {
    if (root == NULL) return;

    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

void deleteNode(Node* root, int targetKey) {
    Node* target = getNodeByValue(root, targetKey);
    if (target == target->parent->right) {
        target->parent->right = NULL;
    }
    else {
        target->parent->left = NULL;
    }
    deleteSide(target);
}

void printTree(Node* root, const char* dir, int level) {
    if (root) {
        printf("lvl %d %s key = %d, fullname = %s, pasportNumber = %s\n", level, dir, root->key, root->fullName, root->pasport);
        printTree(root->left, "left", level + 1);
        printTree(root->right, "right", level + 1);
    }
}

void main() {
    int mood = '1';

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Node* root = NULL;
    Node* reserve = NULL;
    Node* target = NULL;

    printf("Выберите один из следующих пунктов меню: \n");
    printf("[  1  ] Создане/пересоздание структуры типа «дерево».\n");
    printf("[  2  ] Добавление новой записи.\n");
    printf("[  3  ] Вывод информации по заданному ключу.\n");
    printf("[  4  ] Удаление информации по заданному ключу.\n");
    printf("[  5  ] Вывод информации по всей структуре.\n");
    printf("[  6  ] Удаление из левой ветви записи с максимальным значением ключа и её наследников.\n");
    printf("[  7  ] Удаление структуры типа «дерево».\n");
    printf("[  8  ] Очистка консоли.\n");
    printf("[z | Z] Выход.\n");

    while (mood != 'Z' && mood != 'z') {
        printf("\nВыбираемый пункт меню: ");
        scanf_s("%c", &mood);
        getchar();

        switch (mood) {
        case '1':
            if (root != NULL) {
                printf("Пересоздание дерева...\n");
                root = NULL;
            }
            else {
                printf("Создание дерева...\n");
            }
            int N;
            printf("Введите количество элементов дерева: ");
            scanf_s("%d", &N);
            getchar();

            if (N == 0) {
                return;
            }

            while (N-- != 0) {
                insert(&root);
            }
            printf("«Дерево» создано/пересоздано.\n");
            break;
        case '2':
            insert(&root);
            break;
        case '3':
            printByKey(root);
            break;
        case '4':
            deleteValue(root);
            break;
        case '5':
            if (root) {
                printTree(root, "root", 0);
            }
            else {
                printf("Дерево отсутствует.\n\n");
            }
            break;
        case '6':
            if (root->left) {
                int maxValueLeft;
                getMaxLeft(&root, &maxValueLeft);
                deleteNode(root, maxValueLeft);
            }
            else {
                printf("У дерева отсутствует левая ветвь данных.\n\n");
            }
            break;
        case '7':
            if (root != NULL) {
                deleteTree(root);
                printf("Дерево удалено.\n\n");
                root = reserve;
            }
            else {
                printf("Дерево отсутствует.\n\n");
            }
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
