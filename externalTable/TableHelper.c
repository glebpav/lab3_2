#include "TableHelper.h"
#include "../FileHelper.h"
#include "../utils.h"


Table initTable(FILE *file) {
    Table table = {NULL, 128, 0, file};
    return table;
}

void destroyTable(Table *table) {
    // for (int i = 0; i < table->tableSize; ++i) free(table->keySpace[i].info);
    if (table->keySpace != NULL) free(table->keySpace);
    // if (table->file != NULL) fclose(table->file);
}

ResponsesTypes freeTable(Table *table) {
    if (table == NULL) return COMMON_EXCEPTION;
    if (table->keySpace == NULL) return SUCCESS_RESPONSE;

    for (int i = 0; i < table->tableSize; ++i)
        free(table->keySpace[i].info);

    return SUCCESS_RESPONSE;
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

    Item info = {value};
    KeySpace newRow = {key, lastVersionOfThisKey + 1, 0, &info};
    writeNewRow(table, newRow);

    // free(table->keySpace);

    return 1;
}

int findRowsWithKey(Table *inputTable, int key, Table *outTable) {
    /*int count = 0;
    for (int i = 0; i < inputTable->tableSize; ++i) {
        KeySpace item = inputTable->keySpace[i];
        if (item.key == key) {

            inputNewRow(outTable, item.key, item.data);
            count += 1;
        }
    }
    if (count == 0) return 0;*/
    return 1;
}

int findRowsWithKeyAndVersion(Table *inputTable, int key, int version, Table *outTable) {
    /*int count = 0;
    for (int i = 0; i < inputTable->tableSize; ++i) {
        KeySpace item = inputTable->keySpace[i];
        if (item.key == key && item.release == version) {
            inputNewRow(outTable, item.key, item.data);
            count += 1;
        }
    }
    if (count == 0) return 0;*/
    return 1;
}

int deleteElementByKey(Table *table, int key) {
    /*int count = 0;
    for (int i = 0; i < table->tableSize; ++i) {
        KeySpace item = table->keySpace[i];
        if (item.key == key) {
            count += 1;
            printf("delete version = %d\n", item.release);
            if (i != table->tableSize - 1) {
                table->keySpace[i].key = table->keySpace[table->tableSize - 1].key;
                table->keySpace[i].release = table->keySpace[table->tableSize - 1].release;
                table->keySpace[i].data = table->keySpace[table->tableSize - 1].data;
                table->tableSize -= 1;
                i -= 1;
            } else {
                table->tableSize -= 1;
            }
        }
    }
    if (count == 0) return 0;*/
    return 1;
}

int updateElementsWithKey(Table *table, int key) {
    /*int latestVersion = -1;
    int count = 0;
    for (int i = table->tableSize - 1; i >= 0; --i) {
        KeySpace item = table->keySpace[i];
        if (item.key == key && latestVersion < item.release) latestVersion = item.release;
    }
    for (int i = 0; i < table->tableSize; ++i) {
        KeySpace item = table->keySpace[i];
        if (item.key == key && item.release != latestVersion) {
            count += 1;
            printf("delete version = %d\n", item.release);
            if (i != table->tableSize - 1) {
                table->keySpace[i].key = table->keySpace[table->tableSize - 1].key;
                table->keySpace[i].release = table->keySpace[table->tableSize - 1].release;
                table->keySpace[i].data = table->keySpace[table->tableSize - 1].data;
                table->tableSize -= 1;
                i -= 1;
            } else {
                table->tableSize -= 1;
            }
        }
    }
    if (count == 0) return 0;*/
    return 1;
}


int insert(Table *table, int key, int version, int data) {
    // if(find(*table, k) >= 0) return 1;
    /*if (table->tableSize >= table->maxTableSize) return 2;
    table->keySpace[table->tableSize].key = key;
    table->keySpace[table->tableSize].release = version;
    fseek(table->file, 0, SEEK_END);
    table->keySpace[table->tableSize].offset = ftell(table->file);
    fwrite(data, sizeof(char), table->keySpace[table->tableSize].len, table->file);
    ++(table->tableSize);
    return 0;*/
}

ResponsesTypes readTable(Table *table, bool firstTime) {

    if (table == NULL) return FILE_EXCEPTION;
    if (table->file == NULL) return FILE_EXCEPTION;

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
    return 1;
}

int saveTable(Table *table) {
    fseek(table->file, sizeof(int), SEEK_SET);
    fwrite(&table->tableSize, sizeof(int), 1, table->file);
    fwrite(table->keySpace, sizeof(KeySpace), table->tableSize, table->file);
    fclose(table->file);
    table->file = NULL;
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

ResponsesTypes writeNewRow(Table *table, KeySpace row) {
    if (table == NULL) return COMMON_EXCEPTION;
    if (table->file == NULL) return FILE_EXCEPTION;
    if (table->maxTableSize == 0) return COMMON_EXCEPTION;
    if (table->maxTableSize == table->tableSize) return TABLE_OVERFLOW_EXCEPTION;

    long newKeysOffset = sizeof(int) * 2 + sizeof(KeySpace) * table->tableSize;
    long newItemOffset = sizeof(int) * 2 + sizeof(KeySpace) * table->maxTableSize + sizeof(Item) * table->tableSize;
    row.offset = newItemOffset;
    table->tableSize += 1;

    // rewrite table size
    fseek(table->file, sizeof(int), SEEK_SET);
    fwrite(&(table->tableSize), sizeof(int), 1, table->file);

    // write new key
    fseek(table->file, newKeysOffset, SEEK_SET);
    fwrite(&row, sizeof(KeySpace), 1, table->file);

    // write new data
    fseek(table->file, newItemOffset, SEEK_SET);
    fwrite(row.info, sizeof(Item), 1, table->file);
    return SUCCESS_RESPONSE;
}
