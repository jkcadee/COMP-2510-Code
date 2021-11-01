#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

typedef struct Node* DLink;

DLink createNode(int data, DLink next, DLink prev) {
    DLink link = (DLink) malloc(sizeof(struct Node));
    if (link == NULL) {
        perror("Memory issues again?!");
        exit(1);
    }

    link->data = data;
    link->next = next;
    link->prev = prev;
    return link;
}

void printLinkedList(DLink head) {
    if (!head) {
        printf("\n");
        return;
    }

    printf("%d", head->data);
    if (head->next) {
        printf("<->");
    }

    printLinkedList(head->next);
}

void push(DLink *head, int data) {
    DLink newHead = createNode(data, *head, NULL);
    if (*head) {
        (*head)->prev = newHead;
    }
    *head = newHead;
}

void moveTheNodes(DLink *currentNodeFirst, DLink *currentNodeSecond) {
    if ((*currentNodeFirst)->next && !(*currentNodeSecond)->next) {
        *currentNodeFirst = (*currentNodeFirst)->next;
    } else if (!(*currentNodeFirst)->next && (*currentNodeSecond)->next) {
        *currentNodeSecond = (*currentNodeSecond)->next;
    } else {
        *currentNodeFirst = (*currentNodeFirst)->next;
        *currentNodeSecond = (*currentNodeSecond)->next;
    }
}

void addingWithTwoNodes(DLink *sumHead, DLink *currentNodeFirst, DLink *currentNodeSecond, int *newData, int *carryOver) {
    if ((*currentNodeFirst)->data + (*currentNodeSecond)->data + *carryOver > 9) {
        *newData = (*currentNodeFirst)->data + (*currentNodeSecond)->data + *carryOver - 10;
        *carryOver = 1;
    } else {
        *newData = (*currentNodeFirst)->data + (*currentNodeSecond)->data + *carryOver;
        *carryOver = 0;
    }

    if (!*sumHead) {
        *sumHead = createNode(*newData, NULL, NULL);
    } else {
        push(&*sumHead, *newData);
    }

    *currentNodeFirst = (*currentNodeFirst)->prev;
    *currentNodeSecond = (*currentNodeSecond)->prev;
}

void addingExtra(DLink *sumHead, DLink *notNullNode, int *carryOver) {
    if ((*notNullNode)->data + *carryOver > 9) {
        push(*&sumHead, (*notNullNode)->data + *carryOver - 10);
        *carryOver = 1;
        *notNullNode = (*notNullNode)->prev;
    } else {
        push(*&sumHead, (*notNullNode)->data + *carryOver);
        *carryOver = 0;
        *notNullNode = (*notNullNode)->prev;
    }
}

DLink sum(DLink firstNumber, DLink secondNumber) {
    if (!firstNumber || !secondNumber) {
        perror("Passed empty head node into sum function.");
        exit(1);
    }

    DLink currentNodeFirst = firstNumber;
    DLink currentNodeSecond = secondNumber;
    DLink sumHead = NULL;
    int newData = 0;
    int carryOver = 0;

    while(currentNodeFirst->next || currentNodeSecond->next) {
        moveTheNodes(&currentNodeFirst, &currentNodeSecond);
    }

    while (currentNodeFirst && currentNodeSecond) {
        addingWithTwoNodes(&sumHead, &currentNodeFirst, &currentNodeSecond, &newData, &carryOver);
    }

    while (currentNodeFirst || currentNodeSecond) {
        if (currentNodeFirst) {
            addingExtra(&sumHead, &currentNodeFirst, &carryOver);
        } else {
            addingExtra(&sumHead, &currentNodeSecond, &carryOver);
        }
    }

    if (carryOver == 1) {
        push(&sumHead, 1);
    }

    return sumHead;
}

void testCaseOne() {
// Test case one
    DLink first = NULL;
    push(&first, 9);
    push(&first, 9);
    push(&first, 9);

    DLink second = NULL;
    push(&second, 7);
    push(&second, 0);
    push(&second, 0);
    push(&second, 1);

    printLinkedList(sum(first, second));
}

void testCaseTwo() {
    // Test case two
    DLink first = NULL;
    push(&first, 9);
    push(&first, 9);

    DLink second = NULL;
    push(&second, 7);
    push(&second, 0);
    push(&second, 0);
    push(&second, 1);

    printLinkedList(sum(first, second));

}

void testCaseThree() {
    // Test case three
    DLink first = NULL;
    push(&first, 9);
    push(&first, 9);
    push(&first, 9);
    push(&first, 9);

    DLink second = NULL;
    push(&second, 1);
    push(&second, 0);
    push(&second, 0);
    push(&second, 1);

    printLinkedList(sum(first, second));

}

void testCaseFour() {
    // Test case four
    DLink first = NULL;
    push(&first, 9);
    push(&first, 9);
    push(&first, 9);
    push(&first, 9);

    DLink second = NULL;;
    push(&second, 1);
    push(&second, 0);
    push(&second, 1);

    printLinkedList(sum(first, second));
}

void testCaseFive() {
    // Test case five
    DLink first = NULL;
    push(&first, 9);
    push(&first, 9);
    push(&first, 9);
    push(&first, 9);

    DLink second = NULL;
    push(&second, 1);

    printLinkedList(sum(first, second));
}

int main() {
    testCaseOne();
    testCaseTwo();
    testCaseThree();
    testCaseFour();
    testCaseFive();

    // Thanks for teaching us C Seyed!
    // You made learning a language as daunting as C into an enjoyable experience, even the frustrating times.
    // I hope you continue your tenure at BCIT, the department and students would benefit greatly from it, you
    // have much knowledge to share and I hope you will be able to share it, in the years to come.

    return 0;
}
