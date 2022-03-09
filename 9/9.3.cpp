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

    printf("������� �.�.�. key = %d �������� ���������: ", value);
    gets_s(tmp->fullName);
    printf("������� ����� �������� key = %d �������� ���������: ", value);
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

    printf("������� key �������� ������������ ��������: ");
    scanf_s("%d", &value);
    getchar();

    Node* target = getNodeByValue(*head, value);
    if (target != NULL) {
        printf("��������� �������� ����� ���������������, �� ������ ��� �������� ����� �������� ������.\n");
        printf("����� ������� �� ��������.\n");
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
            printf("���������� �������� ������.");
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

        printf("������������ �������� ����� ����� ����� maxLeft = %d\n", maxOfLeft);
        *maxValueLeft = maxOfLeft;
    }
    else {
        printf("����� ����� ������ �����.");
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
    printf("������� key ������������� �������� ������: ");
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
        printf("�� ��������� ������� ������ ������, ��� ������ ������� �������� ����� ���� ����� 7.");
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
    printf("������� key ���������� �������� ������: ");
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

    printf("�������� ���� �� ��������� ������� ����: \n");
    printf("[  1  ] �������/������������ ��������� ���� �������.\n");
    printf("[  2  ] ���������� ����� ������.\n");
    printf("[  3  ] ����� ���������� �� ��������� �����.\n");
    printf("[  4  ] �������� ���������� �� ��������� �����.\n");
    printf("[  5  ] ����� ���������� �� ���� ���������.\n");
    printf("[  6  ] �������� �� ����� ����� ������ � ������������ ��������� ����� � � �����������.\n");
    printf("[  7  ] �������� ��������� ���� �������.\n");
    printf("[  8  ] ������� �������.\n");
    printf("[z | Z] �����.\n");

    while (mood != 'Z' && mood != 'z') {
        printf("\n���������� ����� ����: ");
        scanf_s("%c", &mood);
        getchar();

        switch (mood) {
        case '1':
            if (root != NULL) {
                printf("������������ ������...\n");
                root = NULL;
            }
            else {
                printf("�������� ������...\n");
            }
            int N;
            printf("������� ���������� ��������� ������: ");
            scanf_s("%d", &N);
            getchar();

            if (N == 0) {
                return;
            }

            while (N-- != 0) {
                insert(&root);
            }
            printf("������� �������/�����������.\n");
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
                printf("������ �����������.\n\n");
            }
            break;
        case '6':
            if (root->left) {
                int maxValueLeft;
                getMaxLeft(&root, &maxValueLeft);
                deleteNode(root, maxValueLeft);
            }
            else {
                printf("� ������ ����������� ����� ����� ������.\n\n");
            }
            break;
        case '7':
            if (root != NULL) {
                deleteTree(root);
                printf("������ �������.\n\n");
                root = reserve;
            }
            else {
                printf("������ �����������.\n\n");
            }
            break;
        case '8':
            system("cls");
            printf("������� �������.\n\n");
            break;
        default:
            if (mood != 'Z' && mood != 'z') {
                system("cls");
                printf("��� ������� ������� ���� �� �������, ��������� ��� ��� ...\n\n");
            }
            else {
                printf("\n���� �������.\n");
            }
            break;
        }
    }

    return;
}
