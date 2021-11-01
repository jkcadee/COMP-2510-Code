//
// Created by Janelle on 2020-01-10.
//
#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int elements[], int size) {
    int reverseNumInArray = size - 1;
    if (size == 0) {
        return false;
    }
    for(int numInArray = 0; numInArray < size; numInArray++) {
        if (elements[numInArray] == elements[reverseNumInArray]) {
            reverseNumInArray--;
        }
        else {
            return false;
        }
    }
    return true;
}

int main() {
    int palindromeTest[] = {1};
    bool answer = isPalindrome(palindromeTest, 1);
    printf("%d", answer);
    return 0;
}
