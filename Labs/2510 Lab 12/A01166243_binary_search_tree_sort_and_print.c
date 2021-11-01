#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
    void* data;
    struct Node *left;
    struct Node *right;
};

typedef struct Node* TreeNode;

TreeNode createTreeNode(void* data) {
    TreeNode treeNode = (TreeNode) malloc(sizeof(struct Node));
    if (treeNode == NULL) {
        perror("Memory issues!");
        exit(1);
    }

    treeNode->data = data;
    treeNode->left = NULL;
    treeNode->right = NULL;
    return treeNode;
}

bool stringCompare(void *data1, void *data2) {
    return strcmp(*(char**)data1, *(char**)data2) <= 0;
}

void printString(void *data) {
    printf(" %s", *(char**)data);
}

bool doubleCompare(void *data1, void *data2) {
    double first = *(double *)data1;
    double second = *(double *)data2;
    return (first <= second);
}

void printDouble(void *data) {
    printf(" %.2lf", *(double *)data);
}

bool intCompare(void *data1, void *data2) {
    int first = *(int *)data1;
    int second = *(int *)data2;
    return (first <= second);
}

void printInt(void *data) {
    printf(" %d", *(int *)data);
}

bool charCompare(void *data1, void *data2) {
    int first = *(char *)data1;
    int second = *(char *)data2;
    return (first <= second);
}

void printChar(void *data) {
    printf(" %c", *(char *)data);
}

TreeNode insert(TreeNode root, void* data, bool (*compare)(void*, void*)) {
    if (!root) {
        return createTreeNode(data);
    }

    if (compare(data, root->data)) {
        root->left = insert(root->left, data, compare);
    } else {
        root->right = insert(root->right, data, compare);
    }

    return root;
}

void printInOrder(TreeNode root, void (*print)(void*)) {
    if (!root) {
        return;
    }

    printInOrder(root->left, print);
    print(root->data);
    printInOrder(root->right, print);
}

void freeTreeNodes(TreeNode root) {
    if (!root) {
        return;
    }

    freeTreeNodes(root->left);
    freeTreeNodes(root->right);
    free(root);
}

void binarySearchTreeSort(void* array, bool (*compare)(void*, void*), void (*print)(void*), int arrayLength, size_t byteSize) {
    TreeNode root = NULL;

    for (int index = 0; index < arrayLength; index++) {
            root = insert(root, array + index * byteSize, compare);
    }

    printInOrder(root, print);
    freeTreeNodes(root);
}

int main() {
    int array[5] = {2, 5, 2, 3, 0};
    int arrayLength = 5;

    double arrD[5] = {0.0, 0.0, 0.000001, 0.0, -0.0000012};
    int arrayLength2 = 5;

    char* arrS[4] = {"Cel", "Bel", "Ael", "Del"};
    int arrayLength3 = 4;

    char arrC[7] = {'a', 'z', 'b', 'y', 'r', 'g', 'p'};
    int arrayLength4 = 7;

    binarySearchTreeSort(array, intCompare, printInt, arrayLength, sizeof(int));
    printf("\n");
    binarySearchTreeSort(arrD, doubleCompare, printDouble, arrayLength2, sizeof(double));
    printf("\n");
    binarySearchTreeSort(arrS, stringCompare, printString, arrayLength3, sizeof(char*));
    printf("\n");
    binarySearchTreeSort(arrC, charCompare, printChar, arrayLength4, sizeof(char));

    return 0;
}
