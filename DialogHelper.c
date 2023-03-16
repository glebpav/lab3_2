#include <stdio.h>
#include "ExceptionsHandler.h"

int getInt(int *var) {
    int clearBuffer, res = scanf("%d", var);
    while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF) {}
    return res;
}

int selectOperation(const char *commandsMessages[], int countOfMessages) {
    char *repeatMessage = "";
    int userInput, i, res;

    do {
        puts(" ");
        puts(repeatMessage);
        for (i = 0; i < countOfMessages; ++i) puts(commandsMessages[i]);
        puts("\nSelect one command out of given:");
        res = getInt(&userInput);
        if (res == 0) {
            throughException(NOT_INT_VALUE);
        } else if (userInput >= countOfMessages || userInput <= 0) {
            throughException(INPUT_NOT_IN_RANGE);
        } else if (res == EOF) {
            // TODO: Exit program
            return 0;
        }
        repeatMessage = "Please, repeat input!";
    } while (res <= 0 || userInput >= countOfMessages || userInput <= 0);
    return userInput - 1;
}