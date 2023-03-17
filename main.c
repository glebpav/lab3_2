#include <stdio.h>
#include "DialogHelper.h"
#include "ConsoleCommandsHelper.h"

// gcc main.c -o main ConsoleCommandsHelper.c DialogHelper.c ExceptionsHandler.c FileHelper.c localeTable/TableHelper.c

int main() {
    Table table = initTable(64);
    int operation, operationResponse;

    do {
        operation = selectOperation(commandsMessages, countOfCommands);
        operationResponse = commandsPointers[operation](&table);
    } while (operation && operationResponse);

    return 0;
}
