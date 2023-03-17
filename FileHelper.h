#ifndef LAB3_2_FILEHELPER_H
#define LAB3_2_FILEHELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ExceptionsHandler.h"
#include "localeTable/TableHelper.h"

int isDigit(char *str);

int readFile(char *fileName, char **outputString);
int getTableFromString(char *inputString, Table *table);

#endif //LAB3_2_FILEHELPER_H
