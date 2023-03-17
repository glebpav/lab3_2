#ifndef LAB3_2_TABLEHELPER_H
#define LAB3_2_TABLEHELPER_H

#include <stdio.h>

typedef struct KeySpace {
    int key;
    int release;
    int data;
} KeySpace;

typedef struct Table {
    KeySpace *keySpace;
    int maxTableSize;
    int tableSize;
} Table;

Table initTable();

void freeTable(Table *table);
int inputNewRow(Table *table, int key, int value);
int findRowsWithKey(Table *inputTable, int key, Table *outTable);
int findRowsWithKeyAndVersion(Table *inputTable, int key, int version, Table *newTable);
int deleteElement(Table *table, int key);
int updateElementsWithKey(Table *table, int key);

#endif //LAB3_2_TABLEHELPER_H
