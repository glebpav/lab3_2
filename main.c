#include <stdio.h>
#include "DialogHelper.h"
#include "ConsoleCommandsHelper.h"

int main() {


    Table table;
    int operation = selectOperation(commandsMessages, countOfCommands);
    commandsPointers[operation](&table);
    return 0;
}
