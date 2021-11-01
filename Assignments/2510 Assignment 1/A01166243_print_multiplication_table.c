//
// Created by Janelle on 2020-01-10.
//

#include <stdio.h>

void printMultiplicationTable() {
    for (int row = 1; row <= 10; row++) {
        for (int multiple = 1; multiple <= 10; multiple++) {
            printf("%3d ", row * multiple);
        }
        printf("\n");
    }
}

int main() {
    printMultiplicationTable();
    return 0;
}
