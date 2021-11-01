#include <stdio.h>
#define MAX_COLUMNS 10

int fromBinary(int *binaryArray, int size) {
    if (size == 0) {
        return 0;
    }
    int number = fromBinary(binaryArray, size - 1);
    return 2 * number + binaryArray[size - 1];
}

void readNextNumberFromFile(FILE * file, int binaryArray[MAX_COLUMNS], int numberOfColumns) {
    int nums;
    for (int binaryLength = 0; binaryLength < numberOfColumns; binaryLength++) {
        fscanf(file, "%d", &nums);
        binaryArray[binaryLength] = nums;
    }
    printf("%d\n", fromBinary(binaryArray, numberOfColumns));
}

void processFile(char *fileName) {
    FILE * file;
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("No file available to read.");
        return;
    }
    int binaryArray[MAX_COLUMNS], numberOfColumns, numberOfRows;
    fscanf(file, "%d %d", &numberOfRows, &numberOfColumns);
    for (int currentRow = 0; currentRow < numberOfRows; currentRow++) {
        readNextNumberFromFile(file, binaryArray, numberOfColumns);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        processFile(argv[1]);
        return 0;
    }
}