#ifndef LAB3_2_DIALOGHELPER_H
#define LAB3_2_DIALOGHELPER_H

#include "externalTable/TableHelper.h"
#include "ConsoleCommandsHelper.h"

const char *commandsMessages[] = {
        "1. Exit program",
        "2. Add element",
        "3. Find element(s) by KEY",
        "4. Find element by KEY and VERSION (*)",
        "5. Delete element by KEY",
        "6. Delete old versions of elements with KEY (*)",
        "7. Print all table",
};

int (*commandsPointers[])(Table *) = {
        exitProgram,
        addElement,
        findElementByKey,
        findElementByKeyAndVersion,
        deleteElement,
        deleteOldVersionsWithKey,
        printTable,
        readTableFromFile
};

const int countOfCommands = sizeof(commandsMessages) / sizeof(commandsMessages[0]);

int presettingProgram(Table *table);

int selectOperation(const char *commandsMessages[], int countOfMessages);

#endif //LAB3_2_DIALOGHELPER_H
