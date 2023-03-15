#include "stdio.h"
#include "ConsoleCommands.h"

const char **getAvailableCommandsMessages(int *countOfCommands) {
    const char *availableCommands[] = {
            "1. Exit program",
            "2. Add element",
            "3. Find element(s) by KEY",
            "4. Find element by KEY and VERSION (*)",
            "5. Delete element by KEY",
            "7. Delete old versions of elements with KEY (*)",
            "6. Print all table"
    };
    *countOfCommands = sizeof(availableCommands) / sizeof(availableCommands[0]);
    return availableCommands;
}

commandFunctionPtr *getAvailableCommands(int *countOfCommands) {
    commandFunctionPtr *commandsFunctions = {
            NULL,
            addElement,
            findElementByKey,
            findElementByKeyAndVersion,
            deleteElementByKey,
            deleteOldVersionsWithKey
    };
    *countOfCommands = sizeof(commandFunctionPtr) / sizeof(commandFunctionPtr[0]);
    return commandsFunctions;
}