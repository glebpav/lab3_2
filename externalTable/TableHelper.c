#include "TableHelper.h"
#include "../FileHelper.h"

Table initTable(FILE *file) {
    Table table = {NULL, 128, 0, file};
    return table;
}

void freeTable(Table *table) {
    if (table->keySpace != NULL && table->tableSize != 0) free(table->keySpace);
}

int inputNewRow(Table *table, int key, int value) {
    if (table->tableSize == table->maxTableSize) {
        throughException(TABLE_OVERFLOW);
        return 0;
    }

    int lastVersionOfThisKey = 0;
    for (int i = 0; i < table->tableSize; ++i) {
        KeySpace item = table->keySpace[i];
        if (item.key == key && item.release > lastVersionOfThisKey) lastVersionOfThisKey = item.release;
    }

    table->tableSize += 1;
    table->keySpace = realloc(table->keySpace, (table->tableSize) * sizeof(KeySpace));

    KeySpace newItem = {key, lastVersionOfThisKey + 1, value};
    table->keySpace[table->tableSize - 1] = newItem;
    return 1;
}

int findRowsWithKey(Table *inputTable, int key, Table *outTable) {
    int count = 0;
    for (int i = 0; i < inputTable->tableSize; ++i) {
        KeySpace item = inputTable->keySpace[i];
        if (item.key == key) {
            inputNewRow(outTable, item.key, item.data);
            count += 1;
        }
    }
    if (count == 0) return 0;
    return 1;
}

int findRowsWithKeyAndVersion(Table *inputTable, int key, int version, Table *outTable) {
    int count = 0;
    for (int i = 0; i < inputTable->tableSize; ++i) {
        KeySpace item = inputTable->keySpace[i];
        if (item.key == key && item.release == version) {
            inputNewRow(outTable, item.key, item.data);
            count += 1;
        }
    }
    if (count == 0) return 0;
    return 1;
}

int deleteElement(Table *table, int key) {
    int count = 0;
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
    if (count == 0) return 0;
    return 1;
}


int loadTable(Table *table, char *fileName) {
    fopen_s(&(table->file), fileName, "r+b");
    if (table->file == NULL)
        return 0;
    fread(&table->maxTableSize, sizeof(int), 1, table->file);
    table->keySpace = calloc(table->maxTableSize, sizeof(KeySpace));
    fread(&table->tableSize, sizeof(int), 1, table->file);
    fread(table->keySpace, sizeof(table->maxTableSize), table->tableSize, table->file);
    return 1;
}

int createFile(Table *table, char *fileName, int maxTableSize)
{
    table->maxTableSize = maxTableSize;
    table->tableSize = 0;
    if (fopen_s(&(table->file), fileName, "w+b") != 0){
        table->keySpace = NULL;
        return 0;
    }
    table->keySpace = (KeySpace *)calloc(table->maxTableSize, sizeof(KeySpace));
    fwrite(&table->maxTableSize, sizeof(int), 1, table->file);
    fwrite(&table->tableSize, sizeof(int), 1, table->file);
    fwrite(table->keySpace, sizeof(KeySpace), table->maxTableSize, table->file);
    return 1;
}

int saveTable(Table *table)
{
    fseek(table->file, sizeof(int), SEEK_SET);
    fwrite(&table->tableSize, sizeof(int), 1, table->file);
    fwrite(table->keySpace, sizeof(KeySpace), table->tableSize, table->file);
    fclose(table->file);
    table->file = NULL;
    return 1;
}