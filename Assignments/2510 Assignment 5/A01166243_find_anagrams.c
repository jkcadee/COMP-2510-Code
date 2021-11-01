#include <stdio.h>
#include <stdbool.h>
#define MAX_NUMBER_OF_LINES 20
#define MAX_NUMBER_OF_ELEMENTS_ON_EACH_LINE 50
#define MAX_NUMBER 100

void swap(int *arrayElementOne, int *arrayElementTwo) {
    int temp = *arrayElementOne;
    *arrayElementOne = *arrayElementTwo;
    *arrayElementTwo = temp;
}

void sortingArrays(int arrayToBeSorted[], int arraySize) {
    int lowestIndex = 0;
    for (int currentIndex = 0; currentIndex < arraySize - 1; currentIndex++) {
        lowestIndex = currentIndex;
        for (int currentIndexTwo = currentIndex + 1; currentIndexTwo < arraySize; currentIndexTwo++) {
            if (arrayToBeSorted[currentIndexTwo] < arrayToBeSorted[lowestIndex]) {
                lowestIndex = currentIndexTwo;
            }
        }
        swap(&arrayToBeSorted[lowestIndex], &arrayToBeSorted[currentIndex]);
    }
}

bool areTheseArraysOfIntegersAnagrams(int arrayOne[], int arrayTwo[], int arraySize) {
    sortingArrays(arrayOne, arraySize);
    sortingArrays(arrayTwo, arraySize);
    for (int currentIndex = 0; currentIndex < arraySize; currentIndex++) {
       if (arrayOne[currentIndex] != arrayTwo[currentIndex]) {
           return false;
       }
    }
    return true;
}


void readNextNumberFromFile(FILE * file, int arrayOfNumArrays[MAX_NUMBER_OF_LINES][MAX_NUMBER_OF_ELEMENTS_ON_EACH_LINE], int numberOfRows, int numberOfColumns) {
    for (int currentIndex = 0; currentIndex < numberOfRows; currentIndex++) {
        for (int currentIndexTwo = 0; currentIndexTwo < numberOfColumns; currentIndexTwo++) {
            fscanf(file, "%d", &arrayOfNumArrays[currentIndex][currentIndexTwo]);
        }
    }
}

void processFile(char *fileName) {
    FILE * file;
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("No file available to read.");
        return;
    }
    int arrayOfNumArrays[MAX_NUMBER_OF_LINES][MAX_NUMBER_OF_ELEMENTS_ON_EACH_LINE], numberOfColumns, numberOfRows;
    fscanf(file, "%d %d", &numberOfRows, &numberOfColumns);
    for (int currentRow = 0; currentRow <= numberOfRows; currentRow++) {
        readNextNumberFromFile(file, arrayOfNumArrays, numberOfRows, numberOfColumns);
        for (int nextRow = currentRow + 1; nextRow < numberOfRows; nextRow++) {
            if (areTheseArraysOfIntegersAnagrams(arrayOfNumArrays[currentRow], arrayOfNumArrays[nextRow], numberOfColumns)) {
                printf("Found: Lines %d and %d", currentRow + 2, nextRow + 2);
                fclose(file);
                return;
            }
        }
    }
    fclose(file);
    printf("Not found!");
}

int main(int argc, char *argv[]) {
    processFile(argv[1]);


    return 0;
}
