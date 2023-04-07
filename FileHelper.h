#ifndef LAB3_2_FILEHELPER_H
#define LAB3_2_FILEHELPER_H

#include "externalTable/TableHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ResponsesHandler.h"

int isDigit(char *str);

int readFile(char *fileName, char **outputString);

int getTableFromString(char *inputString, Table *table);

#endif //LAB3_2_FILEHELPER_H
