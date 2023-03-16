#include <stdio.h>
#include "DialogHelper.h"
#include "ConsoleCommandsHelper.h"

int main() {
    Table table = initTable();
    int operation;

    do {
        operation = selectOperation(commandsMessages, countOfCommands);
        commandsPointers[operation](&table);
    } while (operation);

    return 0;
}
