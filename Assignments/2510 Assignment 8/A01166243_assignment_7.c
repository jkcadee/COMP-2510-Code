#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    bool hole;
    int processNumber;
    int base;
    int limit;
    struct Node *next;
};

typedef struct Node* Link;

void printMemory(Link head, int nodeNumber) {
    if (!head) {
        printf("\n");
        return;
    }

    if (head->processNumber > 0) {
        printf("Node: %d: P%d, base = %d, limit = %d\n", nodeNumber++, head->processNumber, head->base, head->limit);
    } else {
        printf("Node: %d: H (Hole), base = %d, limit = %d\n", nodeNumber++, head->base, head->limit);
    }

    printMemory(head->next, nodeNumber);
}

Link createNode(bool hole, int base, int limit) {
    Link link = (Link) malloc(sizeof(struct Node));
    if (link == NULL) {
        perror("Memory issues again?!");
        exit(1);
    }

    static int processID = 1;

    link->hole = hole;
    link->base = base;
    link->limit = limit;
    link->next = NULL;
    if (hole == false) {
        link->processNumber = processID;
        processID++;
    }
    return link;
}

int getLinkedListLengthRecursive(Link head) {
    if (!head) {
        return 0;
    }

    return 1 + getLinkedListLengthRecursive(head->next);
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

void addLast(Link *head, bool hole, int base, int limit) {
    Link newTail = createNode(hole, base, limit);
    if (!*head) {
        *head = newTail;
        return;
    }
    Link currentTail = getTail(*head);
    currentTail->next = newTail;
}

void mergeFreeBlocks(Link head) {
    Link firstHoleNode = NULL;
    Link currentNode = head;

    while (currentNode) {
        if (currentNode->hole == false) {
            firstHoleNode = NULL;
            currentNode = currentNode->next;
        } else if (firstHoleNode == NULL) {
            firstHoleNode = currentNode;
            currentNode = currentNode->next;
        } else {
            Link removedHoleNode = currentNode;

            firstHoleNode->limit += removedHoleNode->limit;

            if (!currentNode->next) {
                firstHoleNode->next = NULL;
                free(removedHoleNode);
                return;
            }
            currentNode = currentNode->next;
            firstHoleNode->next = currentNode;
            free(removedHoleNode);
        }
    }
}

void compaction(Link *head) {
    Link currentNode = *head;
    Link lastNode = NULL;

    while (currentNode) {
        if (!currentNode->hole) {
            lastNode = currentNode;
            currentNode = currentNode->next;
        } else {
            if (!currentNode->next) {
                if (lastNode != NULL) {
                    currentNode->base = lastNode->base + lastNode->limit;
                }
                currentNode = currentNode->next;
            } else {
                if (currentNode->next->hole) {
                    Link nextHole = currentNode->next;
                    currentNode->limit += nextHole->limit;
                    currentNode->next = nextHole->next;
                    free(nextHole);
                } else if (!currentNode->next->hole) {
                    Link temp = currentNode->next;
                    if (lastNode == NULL) {
                        temp->base = 0;
                        *head = temp;
                    } else {
                        temp->base = lastNode->base + lastNode->limit;
                        lastNode->next = temp;
                    }
                    currentNode->next = temp->next;
                    temp->next = currentNode;
                    lastNode = temp;
                }
            }
        }
    }
}

int main() {
    Link headBeginsWithHole = NULL;
    addLast(&headBeginsWithHole, true, 0, 1);
    addLast(&headBeginsWithHole, true, 1, 4);
    addLast(&headBeginsWithHole, true, 5, 3);
    addLast(&headBeginsWithHole, true, 8, 1);
    addLast(&headBeginsWithHole, false, 9, 1);
    addLast(&headBeginsWithHole, false, 10, 4);
    addLast(&headBeginsWithHole, true, 14, 1);
    addLast(&headBeginsWithHole, true, 15, 2);
    addLast(&headBeginsWithHole, true, 17, 7);
    addLast(&headBeginsWithHole, true, 24, 1);

    Link headBeginsWithProcess = NULL;
    addLast(&headBeginsWithProcess, false, 0, 1);
    addLast(&headBeginsWithProcess, false, 1, 4);
    addLast(&headBeginsWithProcess, true, 5, 3);
    addLast(&headBeginsWithProcess, true, 8, 1);
    addLast(&headBeginsWithProcess, false, 9, 1);
    addLast(&headBeginsWithProcess, false, 10, 4);
    addLast(&headBeginsWithProcess, true, 14, 1);
    addLast(&headBeginsWithProcess, true, 15, 2);
    addLast(&headBeginsWithProcess, true, 17, 7);
    addLast(&headBeginsWithProcess, true, 24, 1);

    Link allHoles = NULL;
    addLast(&allHoles, true, 0, 1);
    addLast(&allHoles, true, 1, 4);
    addLast(&allHoles, true, 5, 3);
    addLast(&allHoles, true, 8, 1);
    addLast(&allHoles, true, 9, 1);
    addLast(&allHoles, true, 10, 4);
    addLast(&allHoles, true, 14, 1);
    addLast(&allHoles, true, 15, 2);
    addLast(&allHoles, true, 17, 7);
    addLast(&allHoles, true, 24, 1);

    Link allProcesses = NULL;
    addLast(&allProcesses, false, 0, 1);
    addLast(&allProcesses, false, 1, 4);
    addLast(&allProcesses, false, 5, 3);
    addLast(&allProcesses, false, 8, 1);
    addLast(&allProcesses, false, 9, 1);
    addLast(&allProcesses, false, 10, 4);
    addLast(&allProcesses, false, 14, 1);
    addLast(&allProcesses, false, 15, 2);
    addLast(&allProcesses, false, 17, 7);
    addLast(&allProcesses, false, 24, 1);

    int nodeNumber = 1;

    printf("Original List\n");
    printMemory(headBeginsWithProcess, nodeNumber);

    mergeFreeBlocks(headBeginsWithProcess);
    printf("Merged List\n");
    printMemory(headBeginsWithProcess, nodeNumber);

    compaction(&headBeginsWithProcess);
    printf("Compacted List\n");
    printMemory(headBeginsWithProcess, nodeNumber);

    return 0;
}
