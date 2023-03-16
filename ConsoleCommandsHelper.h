#ifndef LAB3_2_CONSOLECOMMANDSHELPER_H
#define LAB3_2_CONSOLECOMMANDSHELPER_H

// TODO: implement preprocessing for locale/external table
#include "localeTable/TableHelper.h"

int addElement(Table *inputTable);

int findElementByKey(Table *inputTable);

int findElementByKeyAndVersion(Table *inputTable);

int deleteElementByKey(Table *inputTable);

int deleteOldVersionsWithKey(Table *inputTable);


#endif //LAB3_2_CONSOLECOMMANDSHELPER_H
