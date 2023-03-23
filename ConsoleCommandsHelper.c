#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ConsoleCommandsHelper.h"
#include "ExceptionsHandler.h"
#include "FileHelper.h"

// Why you cannot return fixed size / const array in C?
// https://stackoverflow.com/questions/29088462/why-you-cannot-return-fixed-size-const-array-in-c

int getInt(int *var) {
    int clearBuffer, res = scanf("%d", var);
    while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF) {}
    return res;
}

int getSaveIntValue(int *value, char *messageToUser) {

    printf("%s", messageToUser);
    // char *repeatMessage = "";
    int res;
    do {
        // puts(repeatMessage);
        res = getInt(value);
        if (res == 0) {
            throughException(NOT_INT_VALUE);
        } else if (res == EOF) {
            return 0;
        }
        // repeatMessage = "Please, repeat input!";
    } while (res <= 0);
    return res;
}

int exitProgram(Table *table) {
    freeTable(table);
    printf("%s\n", "Goodbye, dear!");
    return 0;
}

int addElement(Table *inputTable) {

    int newKey, newValue;
    if (!getSaveIntValue(&newKey, "Please, input new KEY\n")) return exitProgram(inputTable);
    if (!getSaveIntValue(&newValue, "Please, input new VALUE\n")) return exitProgram(inputTable);

    inputNewRow(inputTable, newKey, newValue);
    return 1;
}

int findElementByKeyAndVersion(Table *inputTable) {
    int key, version;
    if (!getSaveIntValue(&key, "Please, input KEY\n")) return exitProgram(inputTable);
    if (!getSaveIntValue(&version, "Please, input VERSION\n")) return exitProgram(inputTable);

    Table newTable = initTable();
    int res = findRowsWithKeyAndVersion(inputTable, key, version, &newTable);
    printTable(&newTable);
    if (res) freeTable(&newTable);
}

int deleteElement(Table *inputTable) {
    int key;
    if (!getSaveIntValue(&key, "Please, input KEY\n"))
        return exitProgram(inputTable);
    if (!deleteElementByKey(inputTable, key))
        throughException(UNKNOWN_KEY);
    return 1;
}

int deleteOldVersionsWithKey(Table *inputTable) {
    int key;
    if (!getSaveIntValue(&key, "Please, input KEY\n"))
        return exitProgram(inputTable);
    if (!updateElementsWithKey(inputTable, key))
        throughException(UNKNOWN_KEY);
    return 1;
}

int printTable(Table *table) {

    if (table->tableSize == 0) {
        printf("Table is empty\n");
        return 1;
    }

    printf("\nCurren state of table:\n");
    printf("┌──────────────────────┐\n");
    printf("│ %s │ %s │ %s │\n", "KEY","RELEASE", "DATA");
    printf("│─────┼─────────┼──────│\n");
    for (int i = 0; i < table->tableSize; ++i) {
        KeySpace item = table->keySpace[i];
        printf("│ %.*d │ %.*d │ %.*d │\n", 3, item.key, 7, item.release, 4, item.info->data);
    }
    printf("└──────────────────────┘\n");
    return 1;
}

int findElementByKey(Table *inputTable) {
    int key;
    if (!getSaveIntValue(&key, "Please, input KEY\n")) return exitProgram(inputTable);

    Table newTable = initTable();
    int res = findRowsWithKey(inputTable, key, &newTable);
    printTable(&newTable);
    if (res) freeTable(&newTable);
    return 1;
}

int readTableFromFile(Table *table) {
    char fileName[80];
    printf("Please, input file name:\n");
    int res = scanf("%s", fileName);
    printf("fileName: %s\n", fileName);
    if (res == EOF) return exitProgram(table);
    char *fileSting = NULL;
    if (readFile(fileName, &fileSting)) {
        getTableFromString(fileSting, table);
    }
    return 1;

}