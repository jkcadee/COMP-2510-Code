#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

typedef struct Node* Link;

void printLinkedList(Link head) {
    if (!head) {
        printf("\n");
        return;
    }

    printf("%d", head->data);
    if (head->next) {
        printf("->");
    }

    printLinkedList(head->next);
}

Link createNode(int data) {
    Link link = (Link) malloc(sizeof(struct Node));
    if (link == NULL) {
        perror("Memory issues again?!");
        exit(1);
    }

    link->data = data;
    link->next = NULL;
    return link;
}

Link createNodeWithNextNode(int data, Link next) {
    Link link = createNode(data);
    link->next = next;
    return link;
}

int getLinkedListLength(Link head) {
    int length = 0;
    Link currentNode = head;
    while (currentNode) {
        currentNode = currentNode->next;
        length++;
    }
    return length;
}

int getLinkedListLengthRecursive(Link head) {
    if (!head) {
        return 0;
    }

    return 1 + getLinkedListLengthRecursive(head->next);
}

void push(Link *head, int data) {
    Link newHead = createNodeWithNextNode(data, *head);
    //4->20->10
    //5->4->20->10
    *head = newHead;
}

Link getTail(Link head) {
    if (!head) {
        return NULL;
    }

    if (!head->next) {
        return head;
    }

    return getTail(head->next);
}

void addLast(Link *head, int data) {
    Link newTail = createNode(data);
    if (!*head) {
        *head = newTail;
        return;
    }
    Link currentTail = getTail(*head);
    currentTail->next = newTail;
}

int removeTail(Link *head) {
    if (!*head) {
        perror("Empty list is passed to removeTail function.\n");
        exit(1);
    }

    Link currentNode = *head;
    if (!currentNode->next) {
        *head = NULL;
        int data = currentNode->data;
        free(currentNode);
        return data;
    }

    while (currentNode->next->next) {
        currentNode = currentNode->next;
    }

    Link oldTail = currentNode->next;
    int oldTailData = oldTail->data;
    free(oldTail);
    currentNode->next = NULL;
    return oldTailData;
}

int pop(Link *head) {
    if (!*head) {
        perror("Empty list is passed to pop function.\n");
        exit(1);
    }

    int data = (*head)->data;
    Link oldHead = *head;
    *head = (*head)->next;
    free(oldHead);
    return data;
}

Link copyList(Link head) {
    if (!head) {
        return NULL;
    }

    Link copiedNode = createNode(head->data);
    copiedNode->next = copyList(head->next);

    return copiedNode;
}

Link copyListReverse(Link head) {
    if (!head) {
        perror("List is empty.\n");
        exit(1);
    }

    Link currentNode = head;
    Link copiedNode = NULL;

    while (currentNode) {
        Link createdNewNode = createNode(currentNode->data);
        if (copiedNode == NULL) {
            copiedNode = createdNewNode;
            currentNode = currentNode->next;
        } else {
            createdNewNode->next = copiedNode;
            copiedNode = createdNewNode;
            currentNode = currentNode->next;
        }
    }

    return copiedNode;
}

void compactionOriginal(Link *head) {
    Link lastHoleNode = NULL;
    Link currentNode = *head;
    Link previousProcessNode = NULL;
    Link firstProcess = NULL;

    while (currentNode) {
        if (!currentNode->hole) {
            if (previousProcessNode != NULL) {
                currentNode->base = previousProcessNode->base + previousProcessNode->limit;
                previousProcessNode->next = currentNode;
                previousProcessNode = currentNode;
                currentNode = currentNode->next;
            } else {
                firstProcess = currentNode;
                firstProcess->base = 0;
                previousProcessNode = currentNode;
                currentNode = currentNode->next;
            }
        } else {
            if (lastHoleNode != NULL) {
                Link nextLastHoleNode = currentNode;

                lastHoleNode->limit += nextLastHoleNode->limit;

                currentNode = currentNode->next;
                free(nextLastHoleNode);
            } else {
                lastHoleNode = currentNode;
                currentNode = currentNode->next;
            }
        }
    }

    if (lastHoleNode != NULL) {
        lastHoleNode->next = NULL;
        if (previousProcessNode != NULL) {
            *head = firstProcess;
            previousProcessNode->next = lastHoleNode;
            lastHoleNode->base = previousProcessNode->base + previousProcessNode->limit;
        }
    }
}


int main() {
    Link head = NULL;
    addLast(&head, 5);
    addLast(&head, 4);
    addLast(&head, 20);
    addLast(&head, 10);
    addLast(&head, 89);

    Link newCopy = copyList(head);
    Link newCopyReverse = copyListReverse(head);

    addLast(&newCopy, 6);
    addLast(&newCopyReverse, 7);

    printf("Original list.\n");
    printLinkedList(head);
    printf("Copied list with modification.\n");
    printLinkedList(newCopy);
    printf("Reverse copied list with modification.\n");
    printLinkedList(newCopyReverse);

    return 0;
}
