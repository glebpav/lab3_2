#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "ExceptionsHandler.h"
#include "ConsoleCommandsHelper.h"
#include "externalTable/TableHelper.h"


int presettingProgram(Table *table) {

    int userInput = 0;
    bool needsInput = true;

    printf("Hello, dear user!\n");
    while (needsInput) {
        getSaveIntValue(&userInput, "If you want to use existing file enter 1 over-vise 0 \n");
        if (userInput == 1) {
            // TODO: implement reading file
            printf("Uooops, I can't\n");
            needsInput = false;
        } else if (userInput == 0){
            char *fileName;
            // TODO: check if it works correct
            if (getSaveStingValue(&fileName)) return 0;
            createFile(table, fileName);
            free(fileName);
            needsInput = false;
        }
    } return 0;



}

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