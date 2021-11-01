#include <stdio.h>
#include <string.h>
#define MAX_FILE_LINE_SIZE 1000

void readFileToBeCopied(char *fileName, char fileContent[MAX_FILE_LINE_SIZE]) {
    FILE *file;
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("No file available to read.");
        return;
    }
    char line[MAX_FILE_LINE_SIZE];
    strcpy(line, "");
    while(fgets(line, MAX_FILE_LINE_SIZE, file) != NULL) {
        strcat(fileContent, line);
    }
    fclose(file);
}

void writeFileToBeCopied(char *fileName, char *fileContent) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("No file available to copy into.");
        return;
    }
    fwrite(fileContent, 1, strlen(fileContent), file);
    fclose(file);
}

int main(int argc, char *argv[]) {
    char fileContent[MAX_FILE_LINE_SIZE];
    if (argc < 3) {
        return -1;
    }
    readFileToBeCopied(argv[1], fileContent);
    writeFileToBeCopied(argv[2], fileContent);
    return 0;
}
