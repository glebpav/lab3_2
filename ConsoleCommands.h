#ifndef LAB3_2_CONSOLECOMMANDS_H
#define LAB3_2_CONSOLECOMMANDS_H

// TODO: implement preprocessing for locale/external table
#include "localeTable/TableHelper.h"

typedef int (*commandFunctionPtr)(Table *);

const char **getAvailableCommandsMessages(int *countOfCommands);
commandFunctionPtr *getAvailableCommands(int *countOfCommands);

int addElement(Table * inputTable);
int findElementByKey(Table *inputTable);
int findElementByKeyAndVersion(Table *inputTable);
int deleteElementByKey(Table *inputTable);
int deleteOldVersionsWithKey(Table *inputTable);

#endif //LAB3_2_CONSOLECOMMANDS_H
