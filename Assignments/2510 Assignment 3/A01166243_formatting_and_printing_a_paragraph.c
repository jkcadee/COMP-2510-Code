#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_WORDS_IN_PARAGRAPH 100
#define MAX_WORD_LENGTH 20

int getCurrentTokenSize(char *inputString) {
    int lengthOfString = 0;
    while(*inputString) {
        lengthOfString++;
        inputString++;
    }
    return lengthOfString;
}

int addingCharacterToArray(char tokens[][MAX_WORD_LENGTH], char *paragraph, int tokenArrayIndex, int characterCounter) {
    tokens[tokenArrayIndex][characterCounter] = *paragraph;
    return ++characterCounter;
}

int tokenize(char *paragraph, char tokens[][MAX_WORD_LENGTH]) {
    int tokenArrayIndex = 0;
    int characterCounter = 0;
    int totalWordCounter = 0;

    while(*paragraph) {
        if (*paragraph == ' ') {
            tokens[tokenArrayIndex][characterCounter] = '\0';
            if (characterCounter != 0) {
                totalWordCounter++;
                tokenArrayIndex++;
                characterCounter = 0;
            }
            paragraph++;
        } else {
            characterCounter = addingCharacterToArray(tokens, paragraph, tokenArrayIndex, characterCounter);
            paragraph++;
        }
    }
    tokens[tokenArrayIndex][characterCounter] = '\0';
    totalWordCounter++;
    return totalWordCounter;
}


int getNumberOfWordsForNextLine(char tokens[][MAX_WORD_LENGTH], int lineLength, int *totalCharacters, int totalNumberOfWords, int startingIndex) {
    int totalLineSize = 0;
    int wordCount = 0;
    int spaceAmount = 0;
    bool isTrue = true;

    while(isTrue) {
        if ((startingIndex + wordCount) >= totalNumberOfWords) {
            isTrue = false;
        } else {
            int currentSize = getCurrentTokenSize(tokens[wordCount]);
            if (currentSize == 0) {
                isTrue = false;
            } else {
                totalLineSize += currentSize;
                spaceAmount = lineLength - totalLineSize;
                if (totalLineSize <= lineLength && spaceAmount >= wordCount - 1) {
                    wordCount++;
                } else {
                    totalLineSize = totalLineSize - currentSize;
                    isTrue = false;
                }
            }
        }
    }
    *totalCharacters = totalLineSize;
    return wordCount;
}

void printLineWithWhiteSpaces(char tokens[][MAX_WORD_LENGTH], int startingIndex, int numberOfWords, int spaces, int remainder, int index) {
    printf("%s", tokens[index]);
    if(index < (startingIndex + numberOfWords) - 1) {
        int spaceLimit = spaces + ((index - startingIndex) < remainder ? 1 : 0);
        for (int amountOfSpacesToBePrinted = 0; amountOfSpacesToBePrinted <= spaceLimit; amountOfSpacesToBePrinted++) {
            printf(" ");
        }
    }
}

void formatAndPrintCurrentLine(char tokens[][MAX_WORD_LENGTH], int numberOfWords, int lineLength, int totalCharacters, int startingIndex) {
    int difference = numberOfWords - 1;
    int spaces = (lineLength - (totalCharacters + difference)) / difference;
    int remainder = (lineLength - (totalCharacters + difference)) % difference;

    for(int index = startingIndex; index < (startingIndex + numberOfWords); index++) {
        printLineWithWhiteSpaces(tokens, startingIndex, numberOfWords, spaces, remainder, index);
    }
}

int printParagraph(char tokenArray[][MAX_WORD_LENGTH], int startingIndex, int lineLength, int totalCharactersPerLine, int totalWordCount) {
    int wordCount = getNumberOfWordsForNextLine(&tokenArray[startingIndex], lineLength, &totalCharactersPerLine, totalWordCount, startingIndex);
    formatAndPrintCurrentLine(tokenArray, wordCount, lineLength, totalCharactersPerLine, startingIndex);
    printf("\n");
    return wordCount;
}

void formatAndPrintParagraph(char *paragraph, int lineLength) {
    char tokenArray[MAX_WORDS_IN_PARAGRAPH][MAX_WORD_LENGTH];
    memset(tokenArray, 0, 100);
    int startingIndex = 0;
    int totalCharactersPerLine = 0;
    int wordCount = 0;
    int isTrue = true;

    int totalWordCount = tokenize(paragraph, tokenArray);

    while(isTrue) {
        if (startingIndex >= totalWordCount) {
            isTrue = false;
        } else {
            wordCount = printParagraph(tokenArray, startingIndex, lineLength, totalCharactersPerLine, totalWordCount);
            startingIndex += wordCount;
        }
    }
}

int main() {
    char token[] = "I know we try, And the days, they go by, Until we get old, There's water in the flowers, let's grow. People, they lie, But hey, so do I, Until we get old, There's water in the flowers, let's grow. I know we try, And the days, they go by, Until we get old, There's water in the flowers, let's grow. People, they lie, But hey, so do I, Until we get old, There's water in the flowers, let's grow. I know we try, And the days, they go by, Until we get old, There's water in the flowers, let's";

    formatAndPrintParagraph(token, 40);

    return 0;
}
