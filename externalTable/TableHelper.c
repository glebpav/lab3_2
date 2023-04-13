#include "TableHelper.h"
#include "../FileHelper.h"
#include "../utils.h"


Table initTable(FILE *file) {
    Table table = {NULL, 128, 0, file};
    return table;
}

void destroyTable(Table *table) {
    printf("destroyTable: called!\n");
    // for (int i = 0; i < table->tableSize; ++i) free(table->keySpace[i].info);
    if (table->keySpace != NULL) free(table->keySpace);
    if (table->file != NULL) fclose(table->file);
}

ResponsesTypes freeTable(Table *table) {
    if (table == NULL) return COMMON_EXCEPTION;
    if (table->keySpace == NULL) return SUCCESS_RESPONSE;

    for (int i = 0; i < table->tableSize; ++i)
        free(table->keySpace[i].info);

    return SUCCESS_RESPONSE;
}

ResponsesTypes copyRow(KeySpace *to, KeySpace *from) {
    if (from == NULL || to == NULL) return COMMON_EXCEPTION;
    to->info->data = from->info->data;
    to->release = from->release;
    to->offset = from->offset;
    to->key = from->key;
    return SUCCESS_RESPONSE;
}

void printPreloadedTable(Table *table) {
    if (table->tableSize == 0)
        printf("Table is empty\n");


    printf("\nCurren state of table:\n");
    printf("*----------------------*\n");
    printf("| %s | %s | %s |\n", "KEY","RELEASE", "DATA");
    printf("*-----*---------*------*\n");

    for (int i = 0; i < table->tableSize; ++i) {
        KeySpace item = table->keySpace[i];
        printf("| %.*d | %.*d | %.*d |\n", 3, item.key, 7, item.release, 4, item.info->data);
    }

    printf("*----------------------*\n");
}

int inputNewRow(Table *table, int key, int value) {

    if (isException(readKeys(table))) return 0;

    if (table->tableSize == table->maxTableSize) {
        throughException(TABLE_OVERFLOW_EXCEPTION);
        return 0;
    }

    int lastVersionOfThisKey = 0;
    for (int i = 0; i < table->tableSize; ++i) {
        KeySpace item = table->keySpace[i];
        if (item.key == key && item.release > lastVersionOfThisKey)
            lastVersionOfThisKey = item.release;
    }

    Item *info = calloc(1, sizeof(Item));
    KeySpace *newRow = calloc(1, sizeof(KeySpace));
    newRow->info = info;
    newRow->key = key;
    newRow->release = lastVersionOfThisKey + 1;
    newRow->offset = 0;

    writeNewRow(table, newRow);

    free(newRow);
    free(info);
    return 1;
}

int findRowsWithKey(Table *inputTable, int key, Table *outTable) {
    int count = 0;
    outTable->keySpace = NULL;
    outTable->tableSize = 0;

    readTable(inputTable, false);
    for (int i = 0; i < inputTable->tableSize; ++i) {
        KeySpace item = inputTable->keySpace[i];
        if (item.key == key) {
            outTable->tableSize += 1;
            outTable->keySpace = realloc(outTable->keySpace, outTable->tableSize * sizeof(KeySpace));
            outTable->keySpace[count].info = calloc(1, sizeof(Item));
            copyRow(&(outTable->keySpace[count]), &item);
            count += 1;
        }
    }
    freeTable(inputTable);
    if (count == 0) return 0;
    return 1;
}

int findRowsWithKeyAndVersion(Table *inputTable, int key, int version, Table *outTable) {
    int count = 0;
    readTable(inputTable, false);
    for (int i = 0; i < inputTable->tableSize; ++i) {
        KeySpace item = inputTable->keySpace[i];
        if (item.key == key && item.release == version) {
            outTable->tableSize += 1;
            outTable->keySpace = realloc(outTable->keySpace, outTable->tableSize * sizeof(KeySpace));
            outTable->keySpace[count].info = calloc(1, sizeof(Item));
            copyRow(&(outTable->keySpace[count]), &item);
            count += 1;
        }
    }
    freeTable(inputTable);
    if (count == 0) return 0;
    return 1;
}

int deleteElementByKey(Table *table, int key) {
    int count = 0;
    readTable(table, false);
    for (int i = 0; i < table->tableSize; ++i) {
        KeySpace item = table->keySpace[i];
        if (item.key == key) {
            count += 1;
            printf("delete version = %d\n", item.release);
            if (i != table->tableSize - 1) {
                swapRows(table, i, table->tableSize - 1);
                table->tableSize -= 1;
                free(table->keySpace[table->tableSize].info);
                fseek(table->file, sizeof(int) * 1, SEEK_SET);
                fwrite(&(table->tableSize), sizeof(int), 1, table->file);
                i -= 1;
            } else {
                table->tableSize -= 1;
                fseek(table->file, sizeof(int) * 1, SEEK_SET);
                free(table->keySpace[table->tableSize].info);
                fwrite(&(table->tableSize), sizeof(int), 1, table->file);
            }
        }
    }
    freeTable(table);
    if (count == 0) return 0;
    return 1;
}

int updateElementsWithKey(Table *table, int key) {
    int latestVersion = -1;
    int count = 0;
    readTable(table, false);
    for (int i = table->tableSize - 1; i >= 0; --i) {
        KeySpace item = table->keySpace[i];
        if (item.key == key && latestVersion < item.release) latestVersion = item.release;
    }
    if (latestVersion == -1) return 0;
    for (int i = 0; i < table->tableSize; ++i) {
        KeySpace item = table->keySpace[i];
        if (item.key == key && item.release != latestVersion) {
            count += 1;
            printf("delete version = %d\n", item.release);
            if (i != table->tableSize - 1) {
                swapRows(table, i, table->tableSize - 1);
                table->tableSize -= 1;
                free(table->keySpace[table->tableSize].info);
                fseek(table->file, sizeof(int) * 1, SEEK_SET);
                fwrite(&(table->tableSize), sizeof(int), 1, table->file);
                i -= 1;
            } else {
                table->tableSize -= 1;
                fseek(table->file, sizeof(int) * 1, SEEK_SET);
                free(table->keySpace[table->tableSize].info);
                fwrite(&(table->tableSize), sizeof(int), 1, table->file);
            }
        }
    }

    freeTable(table);
    if (count == 0) return 0;
    return 1;
}

ResponsesTypes readTable(Table *table, bool firstTime) {

    if (table == NULL) return FILE_EXCEPTION;
    if (table->file == NULL) return FILE_EXCEPTION;

    fseek(table->file, 0, SEEK_SET);
    // reading of max Table size
    fread(&table->maxTableSize, sizeof(int), 1, table->file);
    // reading of Table size
    if (firstTime) table->keySpace = calloc(table->maxTableSize, sizeof(KeySpace));
    fread(&table->tableSize, sizeof(int), 1, table->file);
    // reading of keySpace
    fread(table->keySpace, sizeof(KeySpace), table->tableSize, table->file);
    for (int i = 0; i < table->tableSize; ++i) {
        table->keySpace[i].info = calloc(1, sizeof(Item));
        fseek(table->file, table->keySpace[i].offset, SEEK_SET);
        fread(table->keySpace[i].info, sizeof(Item), 1, table->file);
    }

    return SUCCESS_RESPONSE;
}

ResponsesTypes loadTable(Table *table, char **fileName) {

    ResponsesTypes response;

    response = getDirToFile(fileName);
    if (isException(response)) return response;
    table->file = fopen(*fileName, "r+b");
    int i = 0;
    fseek(table->file, 16, SEEK_SET);
    response = readTable(table, true);
    if (isException(response)) return response;

    return SUCCESS_RESPONSE;
}

ResponsesTypes createFile(Table *table, char **fileName) {

    ResponsesTypes response;

    response = getDirToFile(fileName);
    if (isException(response)) return response;

    table->file = fopen(*fileName, "w+b");
    if (table->file == NULL) {
        printf("Unsuccessful\n");
        return -1;
    }
    fwrite(&table->maxTableSize, sizeof(int), 1, table->file);
    fwrite(&table->tableSize, sizeof(int), 1, table->file);
    table->keySpace = calloc(table->maxTableSize, sizeof(KeySpace));
    fwrite(table->keySpace, sizeof(KeySpace), table->maxTableSize, table->file);
    printf("cursor position (after create table): %ld\n", ftell(table->file));
    return 1;
}

ResponsesTypes readKeys(Table *table) {
    if (table->file == NULL) return FILE_EXCEPTION;

    fseek(table->file, 0, SEEK_SET);
    fread(&table->maxTableSize, sizeof(int), 1, table->file);
    fread(&table->tableSize, sizeof(int), 1, table->file);
    // table->keySpace = realloc(table->keySpace, table->maxTableSize * sizeof(KeySpace));
    fread(table->keySpace, sizeof(KeySpace), table->tableSize, table->file);

    return SUCCESS_RESPONSE;
}

ResponsesTypes writeNewRow(Table *table, KeySpace *row) {
    if (table == NULL) return COMMON_EXCEPTION;
    if (table->file == NULL) return FILE_EXCEPTION;
    if (table->maxTableSize == 0) return COMMON_EXCEPTION;
    if (table->maxTableSize == table->tableSize) return TABLE_OVERFLOW_EXCEPTION;

    long newKeysOffset = sizeof(int) * 2 + sizeof(KeySpace) * table->tableSize;
    long newItemOffset = sizeof(int) * 2 + sizeof(KeySpace) * table->maxTableSize + sizeof(Item) * table->tableSize;
    row->offset = newItemOffset;
    table->tableSize += 1;

    // rewrite table size
    fseek(table->file, sizeof(int), SEEK_SET);
    fwrite(&(table->tableSize), sizeof(int), 1, table->file);

    // write new key
    fseek(table->file, newKeysOffset, SEEK_SET);
    // printf("from here\n");
    fwrite(row, sizeof(KeySpace), 1, table->file);
    // printf("from here2\n");
    // write new data
    // Item *initedItem = calloc(1, sizeof(Item));
    // memset(initedItem, 0, sizeof(Item));
    // initedItem->data = row.info->data;
    fseek(table->file, newItemOffset, SEEK_SET);

    // printf("new Item Offset: %ld\n", newItemOffset);
    // printf("cursor position (after fseek): %ld\n", ftell(table->file));

    fwrite(row->info, sizeof(Item), 1, table->file);
    return SUCCESS_RESPONSE;
}

ResponsesTypes swapRows(Table *table, int swappingIdx1, int swappingIdx2) {
    if (table == NULL) return COMMON_EXCEPTION;
    if (table->file == NULL) return FILE_EXCEPTION;
    if (table->maxTableSize == 0) return COMMON_EXCEPTION;

    long keysOffset1 = sizeof(int) * 2 + sizeof(KeySpace) * swappingIdx1;
    long keysOffset2 = sizeof(int) * 2 + sizeof(KeySpace) * swappingIdx2;

    long itemOffset1 = sizeof(int) * 2 + sizeof(KeySpace) * table->maxTableSize + sizeof(Item) * swappingIdx1;
    long itemOffset2 = sizeof(int) * 2 + sizeof(KeySpace) * table->maxTableSize + sizeof(Item) * swappingIdx2;

    KeySpace *row1 = calloc(1, sizeof(KeySpace));
    KeySpace *row2 = calloc(1, sizeof(KeySpace));
    row1->info = calloc(1, sizeof(Item));
    row2->info = calloc(1, sizeof(Item));

    copyRow(row1, &(table->keySpace[swappingIdx1]));
    copyRow(row2, &(table->keySpace[swappingIdx2]));

    fseek(table->file, keysOffset1, SEEK_SET);
    fwrite(row2, sizeof(KeySpace), 1, table->file);

    fseek(table->file, keysOffset2, SEEK_SET);
    fwrite(row1, sizeof(KeySpace), 1, table->file);

    fseek(table->file, itemOffset1, SEEK_SET);
    fwrite(row2->info, sizeof(Item), 1, table->file);

    fseek(table->file, itemOffset2, SEEK_SET);
    fwrite(row1->info, sizeof(Item), 1, table->file);

    copyRow(&(table->keySpace[swappingIdx1]), row2);
    copyRow(&(table->keySpace[swappingIdx2]), row1);

    free(row1->info);
    free(row2->info);
    free(row1);
    free(row2);
    return SUCCESS_RESPONSE;
}
