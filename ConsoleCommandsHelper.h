#ifndef LAB3_2_CONSOLECOMMANDSHELPER_H
#define LAB3_2_CONSOLECOMMANDSHELPER_H

#ifdef B
#include "externalTable/TableHelper.h"
#else
#include "externalTable//TableHelper.h"
#endif

int getSaveIntValue(int *value, char *messageToUser);

int getSaveStingValue(char **value, char *messageToUser);

int getInt(int *var);

int exitProgram(Table *table);

int addElement(Table *inputTable);

int findElementByKey(Table *inputTable);

int findElementByKeyAndVersion(Table *inputTable);

int deleteElement(Table *inputTable);

int deleteOldVersionsWithKey(Table *inputTable);

int printTable(Table *table);

int readTableFromFile(Table *table);


#endif //LAB3_2_CONSOLECOMMANDSHELPER_H
