#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH_OF_NAME 20
#define INITIAL_SIZE 5

struct Student {
    char *name;
    double GPA;
};

struct Student *memoryReallocationForArray(struct Student *studentArray, int usedLength, int *arraySize) {
    if (usedLength < *arraySize) {
        return studentArray;
    }
    *arraySize *= 2;
    struct Student *reallocatedArray = (struct Student *) realloc(studentArray, *arraySize * sizeof(struct Student));
    if (reallocatedArray == NULL) {
        printf("Could not allocate space for array.\n");
        exit(1);
    }
    return reallocatedArray;
}

void printArray(struct Student *studentArray, int index) {
    for (int arrayIndex = 0; arrayIndex < index; arrayIndex++) {
        if (studentArray[arrayIndex].GPA > 3.9) {
            printf("%s %lf\n", studentArray[arrayIndex].name, studentArray[arrayIndex].GPA);
        }
    }
}

void cleaningOutArray(struct Student *studentArray, int arraySize) {
    for (int arrayIndex = 0; arrayIndex < arraySize; arrayIndex++) {
        free(studentArray[arrayIndex].name);
    }
    for (int arrayIndex = 0; arrayIndex < arraySize; arrayIndex++) {
        free(studentArray);
    }
}

void sortingArray(struct Student *studentArray, int index) {
    for (int arrayIndexOne = 0; arrayIndexOne < index; arrayIndexOne++) {
        for (int arrayIndexTwo = arrayIndexOne + 1; arrayIndexTwo < index; arrayIndexTwo++) {
            if (studentArray[arrayIndexOne].GPA < studentArray[arrayIndexTwo].GPA) {
                struct Student temp = studentArray[arrayIndexOne];
                studentArray[arrayIndexOne] = studentArray[arrayIndexTwo];
                studentArray[arrayIndexTwo] = temp;
            }
        }
    }
}

void readStudentFile(char *fileName, struct Student *studentArray, int *arraySize) {
    FILE *file;
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("No file available to read.\n");
        return;
    }
    if (studentArray == NULL) {
        printf("Could not allocate space for array.\n");
        exit(1);
    }
    char name[MAX_LENGTH_OF_NAME];
    double GPA;
    int usedLength = 0, index = 0;
    while (fscanf(file, "%s %lf", name, &GPA) > 0) {
        usedLength++;
        studentArray = memoryReallocationForArray(studentArray, usedLength, arraySize);
        studentArray[index].name = strdup(name);
        studentArray[index].GPA = GPA;
        index++;
    }
    sortingArray(studentArray, index);
    printArray(studentArray, index);
    fclose(file);
}

int main(int argc, char *argv[]) {
    int arraySize = INITIAL_SIZE;
    int *arraySizePointer = &arraySize;
    struct Student *studentArray = (struct Student *) malloc(INITIAL_SIZE * sizeof(struct Student));
    readStudentFile(argv[1], studentArray, arraySizePointer);
    cleaningOutArray(studentArray, arraySize);
    return 0;
}
