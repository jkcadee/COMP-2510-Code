#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

typedef struct Node* TreeNode;

TreeNode createTreeNode(int data) {
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

TreeNode insert(TreeNode root, int data) {
    if (!root) {
        return createTreeNode(data);
    }

    if (data <= root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }

    return root;
}

bool equals(TreeNode first, TreeNode second) {
    if (!first && !second) {
        return true;
    }

    if (!first || !second || first->data != second->data) {
        return false;
    }

    bool res1 = equals(first->left, second->left);
    bool res2 = equals(first->right, second->right);

    return res1 && res2;
}

bool containsPathWithSum(TreeNode root, int sum) {
    if (!root) {
        return false;
    }
    if (!root->left && !root->right) {
        return root->data == sum;
    }

    bool left = containsPathWithSum(root->left, sum - root->data);
    bool right = containsPathWithSum(root->right, sum - root->data);

    return right || left;
}

void mirror (TreeNode root) {
    if (!root) {
        return;
    }
    mirror(root->left);
    mirror(root->right);

    TreeNode tempLeftSide = root->left;
    root->left = root->right;
    root->right = tempLeftSide;
}

void printPreOrder(TreeNode root) {
    if (!root) {
        return;
    }

    printf(" %d", root->data);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

int main() {
    TreeNode testTreeRoot = NULL;
    testTreeRoot = insert(testTreeRoot, 4);
    testTreeRoot = insert(testTreeRoot, 2);
    testTreeRoot = insert(testTreeRoot, 6);
    testTreeRoot = insert(testTreeRoot, 1);
    testTreeRoot = insert(testTreeRoot, 3);
    testTreeRoot = insert(testTreeRoot, 5);
    testTreeRoot = insert(testTreeRoot, 7);

    TreeNode testTreeRoot2 = NULL;
    testTreeRoot2 = insert(testTreeRoot2, 4);
    testTreeRoot2 = insert(testTreeRoot2, 2);
    testTreeRoot2 = insert(testTreeRoot2, 6);
    testTreeRoot2 = insert(testTreeRoot2, 1);

    TreeNode testTreeRoot2Equals = NULL;
    testTreeRoot2Equals = insert(testTreeRoot2Equals, 4);
    testTreeRoot2Equals = insert(testTreeRoot2Equals, 2);
    testTreeRoot2Equals = insert(testTreeRoot2Equals, 6);
    testTreeRoot2Equals = insert(testTreeRoot2Equals, 1);

    TreeNode testTreeRoot3 = NULL;
    testTreeRoot3 = insert(testTreeRoot3, 1);
    testTreeRoot3 = insert(testTreeRoot3, 2);
    testTreeRoot3 = insert(testTreeRoot3, 6);

    TreeNode testTreeRoot4 = NULL;

//    printf("%d\n", containsPathWithSum(testTreeRoot4, 0));
//
//    printf("%d\n", containsPathWithSum(testTreeRoot3, 9));

    mirror(testTreeRoot2);
//    printPreOrder(testTreeRoot2);

    printf("%d\n", equals(testTreeRoot2Equals, testTreeRoot2));

//    mirror(testTreeRoot);
//    printPreOrder(testTreeRoot);

    return 0;
}
