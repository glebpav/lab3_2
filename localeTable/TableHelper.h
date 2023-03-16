#ifndef LAB3_2_TABLEHELPER_H
#define LAB3_2_TABLEHELPER_H

#include <stdio.h>

typedef struct KeySpace {
    int key;
    int release;
    int *info; // it also could be just int (not pointer)
} KeySpace;

typedef struct Table {
    KeySpace *keySpace;
    const int maxSize;
    int tableLen;
} Table;

Table initTable();

#endif //LAB3_2_TABLEHELPER_H
