#include <stdio.h>
#include "ExceptionsHandler.h"
#include "ConsoleCommandsHelper.h"


int selectOperation(const char *commandsMessages[], int countOfMessages) {
    int userInput;
    printf("\n");
    for (int i = 0; i < countOfMessages; ++i) printf("%s\n", commandsMessages[i]);
    printf("Select one command out of given:\n");
    do {
        if (!getSaveIntValue(&userInput, "")) return 0;
        if (userInput > countOfMessages || userInput <= 0) throughException(INPUT_NOT_IN_RANGE);
        else break;
    } while (1);
    return userInput - 1;
}