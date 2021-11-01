#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_FILE_LINE_SIZE 10000

// If the first two characters in both strings are the same, this function will be invoked to check if the whole string is the same.
bool determineIfFirstWordStartsWithSecond(char *firstWord, char *secondWord) {
    if (strlen(firstWord) < strlen(secondWord)) {
        return false;
    }
    if (!*secondWord) {
        return true;
    }
    return (*firstWord == *secondWord && determineIfFirstWordStartsWithSecond(firstWord + 1, secondWord + 1));
}

// Scans line the inputted string for the specified word.
bool scanForWord(char fileContent[MAX_FILE_LINE_SIZE], char *argv, int originalStringLength, int *lineCounter) {
    ++*lineCounter;
    for (int currentWord = 0; currentWord < originalStringLength; currentWord++) {
        if (*fileContent == *argv) {
            if (determineIfFirstWordStartsWithSecond(fileContent, argv)) {
                printf("Line: %d, Position: %d\n", *lineCounter, currentWord + 1);
                return true;
            }
        }
        fileContent++;
    }
    return false;
}

// Reads the file and attempts to find the specified word. If there is no match, a statement saying so is printed.
void readAndFindWordFromFile(char *fileName, char *argv) {
    FILE *file;
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("No file available to read.\n");
        return;
    }
    char line[MAX_FILE_LINE_SIZE];
    strcpy(line, "");
    int lineCounter = 0;
    bool result = false;
    while(fgets(line, MAX_FILE_LINE_SIZE, file) != NULL && !result) {
        int currentLineSize = strlen(line);
        result = scanForWord(line, argv, currentLineSize, &lineCounter);
        fclose(file);
    }
    if (!result) {
        printf("This word not was found!\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    readAndFindWordFromFile(argv[1], argv[2]);
    return 0;
}
