#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int turningXBit(int xBit, int number) {
    return xBit | number;
}

int shiftingBitsLeft(unsigned int bitShifter, unsigned int number) {
    return number << bitShifter;
}

int shiftingBitsRight(unsigned int bitShifter, unsigned int number) {
    return number >> bitShifter;
}

void swap(void *first, void *second, size_t byteSize) {
    char temp[byteSize];
    memcpy(temp, first, byteSize);
    memcpy(first, second, byteSize);
    memcpy(second, temp, byteSize);
}

bool intCompare(void *first, void *second) {
    int firstValue = *(int *) first;
    int secondValue = *(int *) second;
    return firstValue > secondValue;
}

bool charCompare(void *first, void *second) {
    char firstValue = *(char *) first;
    char secondValue = *(char *) second;
    return firstValue > secondValue;
}

bool doubleCompare(void *first, void *second) {
    double firstValue = *(double *) first;
    double secondValue = *(double *) second;
    return firstValue > secondValue;
}

bool stringCompare(void *first, void *second) {
    char *firstValue = *(char **) first;
    char *secondValue = *(char **) second;
    int stringSizeOne = 0;
    int stringSizeTwo = 0;

    while(*firstValue) {
        stringSizeOne++;
        firstValue++;
    }
    while(*secondValue) {
        stringSizeTwo++;
        secondValue++;
    }

    if (stringSizeOne == stringSizeTwo) {
        return strcmp(firstValue, secondValue);
    }
    return stringSizeOne > stringSizeTwo;
}

void bubbleSort(void *array, int arraySize, size_t byteSize, bool (*compare)(void*, void*)) {
    while (true) {
        bool swapped = false;
        for (int i = 1; i < arraySize; i++) {
            if (compare(array + (i - 1) * byteSize, array + i * byteSize)) {
                swapped = true;
                swap(array + (i - 1) *byteSize, array + i * byteSize, byteSize);
            }
        }
        if (!swapped) {
            return;
        }
    }
}

int main() {
    int arr[4] = {1, 5, 4, 2};
    char arrC[7] = {'a', 'z', 'b', 'y', 'r', 'g', 'p'};
    double arrD[5] = {0.9, 5.3, 129.1, 0.900001, 2.0};
    char *arrS[6] = {"Fates", "Awakening", "Fates", "Blazing Blade", "Three Houses", "Heroes"};

    bubbleSort(arr, 4, sizeof(int), intCompare);
    bubbleSort(arrC, 7, sizeof(char), charCompare);
    bubbleSort(arrD, 5, sizeof(double), doubleCompare);
    bubbleSort(arrS, 6, sizeof(char *), stringCompare);

    printf("Int Array:\n");
    for(int index = 0; index < 4; index++) {
        printf("Index: %d, Value: %d\n", index, arr[index]);
    }
    printf("Char Array:\n");
    for(int index = 0; index < 7; index++) {
        printf("Index: %d, Value: %c\n", index, arrC[index]);
    }
    printf("Double Array:\n");
    for(int index = 0; index < 5; index++) {
        printf("Index: %d, Value: %lf\n", index, arrD[index]);
    }
    printf("String Array:\n");
    for(int index = 0; index < 6; index++) {
        printf("Index: %d, Value: %s\n", index, arrS[index]);
    }

    return 0;
}
