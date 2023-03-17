#ifndef LAB3_2_DIALOGHELPER_H
#define LAB3_2_DIALOGHELPER_H

// TODO: make preprocessing for locale/external table lib
#include "localeTable/TableHelper.h"
#include "ConsoleCommandsHelper.h"

const char *commandsMessages[] = {
        "1. Exit program",
        "2. Add element",
        "3. Find element(s) by KEY",
        "4. Find element by KEY and VERSION (*)",
        "5. Delete element by KEY",
        "6. Delete old versions of elements with KEY (*)",
        "7. Print all table",
        "8. Read table from file"
};

int (*commandsPointers[])(Table *) = {
        exitProgram,
        addElement,
        findElementByKey,
        findElementByKeyAndVersion,
        deleteElementByKey,
        deleteOldVersionsWithKey,
        printTable,
        readTableFromFile
};

const int countOfCommands = sizeof(commandsMessages) / sizeof(commandsMessages[0]);

int selectOperation(const char *commandsMessages[], int countOfMessages);

#endif //LAB3_2_DIALOGHELPER_H
