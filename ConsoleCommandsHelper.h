#ifndef LAB3_2_CONSOLECOMMANDSHELPER_H
#define LAB3_2_CONSOLECOMMANDSHELPER_H

// TODO: implement preprocessing for locale/external table
#include "localeTable/TableHelper.h"

int getSaveIntValue(int *value, char *messageToUser);

int getInt(int *var);

int exitProgram(Table *table);

int addElement(Table *inputTable);

int findElementByKey(Table *inputTable);

int findElementByKeyAndVersion(Table *inputTable);

int deleteElementByKey(Table *inputTable);

int deleteOldVersionsWithKey(Table *inputTable);

int printTable(Table *table);

int readTableFromFile(Table *table);


#endif //LAB3_2_CONSOLECOMMANDSHELPER_H
