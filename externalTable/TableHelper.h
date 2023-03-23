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
    FILE *file;
} Table;

Table initTable(FILE *file);

void freeTable(Table *table);
int inputNewRow(Table *table, int key, int value);
int findRowsWithKey(Table *inputTable, int key, Table *outTable);
int findRowsWithKeyAndVersion(Table *inputTable, int key, int version, Table *newTable);
int deleteElementByKey(Table *table, int key);
int updateElementsWithKey(Table *table, int key);

int loadTable(Table *table, char *fileName);
int createFile(Table *table, char *fileName, int maxTableSize);
int saveTable(Table *table);

#endif //LAB3_2_TABLEHELPER_H
