#ifndef LAB3_2_TABLEHELPER_H
#define LAB3_2_TABLEHELPER_H

#include <stdio.h>
#include "../ResponsesHandler.h"

typedef struct Item {
    int data;
} Item;

typedef struct KeySpace {
    int key;
    int release;
    int offset;
    Item *info;
} KeySpace;

typedef struct Table {
    KeySpace *keySpace;
    int maxTableSize;
    int tableSize;
    FILE *file;
} Table;

Table initTable(FILE *file);
void destroyTable(Table *table);
ResponsesTypes freeTable(Table *table);

int inputNewRow(Table *table, int key, int value);
int findRowsWithKey(Table *inputTable, int key, Table *outTable);
int findRowsWithKeyAndVersion(Table *inputTable, int key, int version, Table *newTable);
int deleteElementByKey(Table *table, int key);
int updateElementsWithKey(Table *table, int key);

ResponsesTypes loadTable(Table *table, char **fileName);
ResponsesTypes readTable(Table *table, bool firstTime);
ResponsesTypes createFile(Table *table, char **fileName);
int saveTable(Table *table);

ResponsesTypes readKeys(Table *table);
ResponsesTypes writeNewRow(Table *table, KeySpace row);

#endif //LAB3_2_TABLEHELPER_H
