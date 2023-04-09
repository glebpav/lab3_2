#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "ResponsesHandler.h"
#include "ConsoleCommandsHelper.h"
#include "externalTable/TableHelper.h"


int presettingProgram(Table *table) {

    ResponsesTypes response;
    int userInput = 0;
    bool needsInput = true;
    char *fileName = NULL;

    printf("Hello, dear user!\n");
    while (needsInput) {

        if (!getSaveIntValue(&userInput, "If you want to use existing file enter 1 over-vise 0 \n"))
            return 0;

        response = getSaveStingValue(&fileName, "Please enter name of bin file:\n");
        if (isException(response)) {
            throughException(response);
            return 0;
        }

        if (userInput == 1) {
            response = loadTable(table, &fileName);
            if (isException(response)) {
                throughException(response);
            }

            printf("count of items: %d\n", table->tableSize);
            printf("max count of items: %d\n", table->maxTableSize);

            printTable(table);
            freeTable(table);

            needsInput = false;
        } else if (userInput == 0) {
            createFile(table, &fileName);
            needsInput = false;
        }
    }
    if (fileName != NULL) free(fileName);
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