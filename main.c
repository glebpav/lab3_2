#include <stdio.h>
#include "DialogHelper.h"
#include "ConsoleCommandsHelper.h"

// gcc main.c -o main ConsoleCommandsHelper.c DialogHelper.c ExceptionsHandler.c FileHelper.c localeTable/TableHelper.c utils.c

int main() {

    Table table = initTable(NULL);
    int operation, operationResponse;

    if (!presettingProgram(&table)) return 0;
    do {
        operation = selectOperation(commandsMessages, countOfCommands);
        operationResponse = commandsPointers[operation](&table);
    } while (operation && operationResponse);
    destroyTable(&table);

    return 0;
}
