#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "ResponsesHandler.h"
#include "ConsoleCommandsHelper.h"
#include "externalTable/TableHelper.h"


int presettingProgram(Table *table) {

    int userInput = 0;
    bool needsInput = true;
    char *fileName;

    printf("Hello, dear user!\n");
    while (needsInput) {

        if (!getSaveIntValue(&userInput, "If you want to use existing file enter 1 over-vise 0 \n"))
            return 0;


        // TODO: check if it works correct
        ResponsesTypes responce = getSaveStingValue(&fileName, "Please enter name of bin file:\n");
        if (isException(responce)) {
            throughException(responce);
            return 0;
        }

        if (userInput == 1) {
            // TODO: implement reading file
            responce = loadTable(table, fileName);
            if (isException(responce)) {
                throughException(responce);
            }

            printf("address of keys array: %p\n", table->keySpace);
            printf("count of items: %d\n", table->tableSize);
            printf("max count of items: %d\n", table->maxTableSize);

            printTable(table);

            needsInput = false;
        } else if (userInput == 0) {
            createFile(table, fileName);
            needsInput = false;
        }
    }
    // free(fileName);
    return 1;


}

int selectOperation(const char *commandsMessages[], int countOfMessages) {
    int userInput;
    printf("\n");
    for (int i = 0; i < countOfMessages; ++i) printf("%s\n", commandsMessages[i]);
    printf("Select one command out of given:\n");
    do {
        if (!getSaveIntValue(&userInput, "")) return 0;
        if (userInput > countOfMessages || userInput <= 0) throughException(INPUT_NOT_IN_RANGE_EXCEPTION);
        else break;
    } while (1);
    return userInput - 1;
}