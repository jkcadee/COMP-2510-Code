//
// Created by Janelle on 2020-01-10.
//
#include <stdio.h>
#include <math.h>

int getNumbersWithDigits(int digit[], int numberOfDigits) {
    int arrayNumber = 0;
    int powersOfTen = numberOfDigits;
    for (int numInArray = 0; numInArray < numberOfDigits; numInArray++) {
        arrayNumber += digit[numInArray] * pow(10, powersOfTen - 1);
        powersOfTen--;
    }
    return arrayNumber;
}

int main() {
    int numbersWithDigitsTest[] = {1, 0, 9, 3};
    int numberWithDigits = getNumbersWithDigits(numbersWithDigitsTest, 4);
    printf("%d", numberWithDigits);
    return 0;
}
