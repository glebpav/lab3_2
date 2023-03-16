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
        "6. Print all table",
        "7. Delete old versions of elements with KEY (*)"
};

int (*commandsPointers[])(Table *) = {
        NULL,
        addElement,
        findElementByKey,
        findElementByKeyAndVersion,
        deleteElementByKey,
        deleteOldVersionsWithKey
};

const int countOfCommands = sizeof(commandsMessages) / sizeof(commandsMessages[0]);

int selectOperation(const char *commandsMessages[], int countOfMessages);
int getInt(int *var);

#endif //LAB3_2_DIALOGHELPER_H
