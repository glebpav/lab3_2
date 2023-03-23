#ifndef LAB3_2_TABLEHELPER_H
#define LAB3_2_TABLEHELPER_H

#include <stdio.h>
#define MAX_TABLE_SIZE 64

typedef struct Item {
    int data;
} Item;

typedef struct KeySpace {
    int key;
    int release;
    Item *info;
} KeySpace;

typedef struct Table {
    KeySpace *keySpace;
    int maxTableSize;
    int tableSize;
} Table;

Table initTable(const int size);

KeySpace initRow();

void freeTable(Table *table);

int inputNewRow(Table *table, int key, int value);

int findRowsWithKey(Table *inputTable, int key, Table *outTable);

int findRowsWithKeyAndVersion(Table *inputTable, int key, int version, Table *newTable);

int deleteElementByKey(Table *table, int key);

int deleteElementByKeyAndVersion(Table *table, int key, int version);

int updateElementsWithKey(Table *table, int key);

#endif //LAB3_2_TABLEHELPER_H
