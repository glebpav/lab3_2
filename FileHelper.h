#ifndef LAB3_2_FILEHELPER_H
#define LAB3_2_FILEHELPER_H

#ifdef B
    #include "externalTable/TableHelper.h"
#else
    #include "localeTable/TableHelper.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ExceptionsHandler.h"

int isDigit(char *str);

int readFile(char *fileName, char **outputString);

int getTableFromString(char *inputString, Table *table);

#endif //LAB3_2_FILEHELPER_H
