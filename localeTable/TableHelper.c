#include <stdlib.h>
#include "TableHelper.h"
#include "../ExceptionsHandler.h"

Table initTable() {
    Table table = {NULL, 128, 0};
    return table;
}

KeySpace initRow() {
    KeySpace row = {-1, -1, calloc(1, sizeof(int))};
    return row;
}

void freeTable(Table *table) {
    if (table->keySpace != NULL && table->tableSize != 0) {
        for (int i = 0; i < table->tableSize; ++i) {
            free(table->keySpace[i].info);
        }
        free(table->keySpace);
    }
}

int inputNewRow(Table *table, int key, int value) {
    if (table->tableSize == table->maxTableSize) {
        throughException(TABLE_OVERFLOW);
        return 0;
    }

    int lastVersionOfThisKey = 0;
    for (int i = 0; i < table->tableSize; ++i) {
        KeySpace item = table->keySpace[i];
        if (item.key == key && item.release > lastVersionOfThisKey) {
            lastVersionOfThisKey = item.release;
        }
    }

    table->tableSize += 1;
    table->keySpace = realloc(table->keySpace, (table->tableSize) * sizeof(KeySpace));

    Item *newItem = calloc(1, sizeof(int));
    newItem->data = value;

    KeySpace newRow = {key, lastVersionOfThisKey + 1, newItem};
    table->keySpace[table->tableSize - 1] = newRow;
    return 1;
}

int findRowsWithKey(Table *inputTable, int key, Table *outTable) {
    int count = 0;
    for (int i = 0; i < inputTable->tableSize; ++i) {
        KeySpace item = inputTable->keySpace[i];
        if (item.key == key) {
            inputNewRow(outTable, item.key, item.info->data);
            count += 1;
        }
    }
    if (count == 0) return 0;
    return 1;
}

int findRowsWithKeyAndVersion(Table *inputTable, int key, int version, Table *outTable) {
    int count = findRowsWithKey(inputTable, key, outTable);
    if (count == 0) return 0;
    for (int i = 0; i < outTable->tableSize; ++i) {
        KeySpace item = outTable->keySpace[i];
        if (item.release != version) {
            deleteElementByKeyAndVersion(outTable, item.key, item.release);
            count--;
        }
    }
    if (count == 0) return 0;
    return 1;
}

int deleteElementByKey(Table *table, int key) {
    int count = 0;
    for (int i = 0; i < table->tableSize; ++i) {
        if (table->keySpace[i].key == key) {
            count += deleteElementByKeyAndVersion(table, key, table->keySpace[i].release);
            i -= 1;
        }
    }
    if (count == 0) return 0;
}

int deleteElementByKeyAndVersion(Table *table, int key, int version) {
    int count = 0;
    for (int i = 0; i < table->tableSize; ++i) {
        KeySpace item = table->keySpace[i];
        if (item.key == key && item.release == version) {
            count += 1;
            if (i != table->tableSize - 1) {
                table->keySpace[i].key = table->keySpace[table->tableSize - 1].key;
                table->keySpace[i].release = table->keySpace[table->tableSize - 1].release;
                table->keySpace[i].info->data = table->keySpace[table->tableSize - 1].info->data;
                table->tableSize -= 1;
                i -= 1;
            } else {
                table->tableSize -= 1;
            }
            free(table->keySpace[table->tableSize].info);
        }
    }
    if (count == 0) return 0;
    return 1;
}

int updateElementsWithKey(Table *table, int key) {
    int latestVersion = -1;
    int count = 0;
    for (int i = table->tableSize - 1; i >= 0; --i) {
        KeySpace item = table->keySpace[i];
        if (item.key == key && latestVersion < item.release) latestVersion = item.release;
    }
    for (int i = 0; i < table->tableSize; ++i) {
        if (table->keySpace[i].key == key && table->keySpace[i].release != latestVersion)
            count += deleteElementByKeyAndVersion(table, key, table->keySpace[i].release);
    }
    if (count == 0) return 0;
    return 1;
}