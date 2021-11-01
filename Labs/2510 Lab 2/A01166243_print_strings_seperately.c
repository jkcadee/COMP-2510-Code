#include <stdio.h>

void printTokens(char *inputStrings) {
    while(*inputStrings == ' ') { // Checking for white space in front of the string.
        inputStrings++;
    }
    while(*inputStrings) {
        if (*inputStrings != ' ') {
            printf("%c", *inputStrings++);
        } else {
            while(*inputStrings == ' ') {
                inputStrings++;
            }
            printf("\n");
        }
    }
}

int main() {
    printTokens("      It's not my  birthday.   ");
    printTokens("     ");
    printTokens("Hello world");
    printTokens("Hello   world");
    return 0;
}
