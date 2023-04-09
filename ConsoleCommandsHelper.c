#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ConsoleCommandsHelper.h"
#include "ResponsesHandler.h"
#include "FileHelper.h"
#include "externalTable/TableHelper.h"

char *getLine(void) {
    char *line = malloc(100), *linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if (line == NULL)
        return NULL;

    for (;;) {
        c = fgetc(stdin);
        if (c == EOF)
            break;

        if (--len == 0) {
            len = lenmax;
            char *linen = realloc(linep, lenmax *= 2);

            if (linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if ((*line++ = c) == '\n')
            break;
    }
    *line--;
    *line = '\0';
    return linep;
}

int getInt(int *var) {
    int clearBuffer, res = scanf("%d", var);
    while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF) {}
    return res;
}

int getSaveIntValue(int *value, char *messageToUser) {

    printf("%s", messageToUser);
    int res;
    do {
        // puts(repeatMessage);
        res = getInt(value);
        if (res == 0) {
            throughException(NOT_INT_VALUE_EXCEPTION);
        } else if (res == EOF) {
            return 0;
        }
        // repeatMessage = "Please, repeat input!";
    } while (res <= 0);
    return res;
}

int getSaveStingValue(char **value, char *messageToUser) {
    printf("%s", messageToUser);
    *value = getLine();
    return value == NULL ? COMMON_EXCEPTION : SUCCESS_RESPONSE;
}

int exitProgram(Table *table) {
    destroyTable(table);
    printf("%s\n", "Goodbye, dear!");
    return 0;
}

int addElement(Table *inputTable) {

    int newKey, newValue;
    if (!getSaveIntValue(&newKey, "Please, input new KEY\n"))
        return exitProgram(inputTable);
    if (!getSaveIntValue(&newValue, "Please, input new VALUE\n"))
        return exitProgram(inputTable);

    inputNewRow(inputTable, newKey, newValue);
    return 1;
}

int findElementByKeyAndVersion(Table *inputTable) {
    /*int key, version;
    if (!getSaveIntValue(&key, "Please, input KEY\n"))
        return exitProgram(inputTable);
    if (!getSaveIntValue(&version, "Please, input VERSION\n"))
        return exitProgram(inputTable);


    //Table newTable = initLocaleTable(MAX_TABLE_SIZE);
    int res = findRowsWithKeyAndVersion(inputTable, key, version, &newTable);
    printTable(&newTable);
    if (res) destroyTable(&newTable);*/
}

int deleteElement(Table *inputTable) {
    int key;
    if (!getSaveIntValue(&key, "Please, input KEY\n"))
        return exitProgram(inputTable);
    if (!deleteElementByKey(inputTable, key))
        throughException(UNKNOWN_KEY_EXCEPTION);
    return 1;
}

int deleteOldVersionsWithKey(Table *inputTable) {
    int key;
    if (!getSaveIntValue(&key, "Please, input KEY\n"))
        return exitProgram(inputTable);
    if (!updateElementsWithKey(inputTable, key))
        throughException(UNKNOWN_KEY_EXCEPTION);
    return 1;
}

int printTable(Table *table) {


    if (table->tableSize == 0) {
        printf("Table is empty\n");
        return 1;
    }

    printf("\nCurren state of table:\n");
    printf("*----------------------*\n");
    printf("| %s | %s | %s |\n", "KEY","RELEASE", "DATA");
    printf("*-----*---------*------*\n");

    for (int i = 0; i < table->tableSize; ++i) {
        KeySpace item = table->keySpace[i];
        printf("| %.*d | %.*d | %.*d |\n", 3, item.key, 7, item.release, 4, item.info->data);
    }

    printf("*----------------------*\n");
    return 1;
}

int findElementByKey(Table *inputTable) {
    /*int key;
    if (!getSaveIntValue(&key, "Please, input KEY\n"))
        return exitProgram(inputTable);

    Table newTable = initLocaleTable(MAX_TABLE_SIZE);
    int res = findRowsWithKey(inputTable, key, &newTable);
    printTable(&newTable);
    if (res) destroyTable(&newTable);*/
    return 1;
}

int readTableFromFile(Table *table) {
    char fileName[80];
    printf("Please, input fileDescriptor name:\n");
    int res = scanf("%s", fileName);
    printf("fileName: %s\n", fileName);
    if (res == EOF) return exitProgram(table);
    char *fileSting = NULL;
    if (readFile(fileName, &fileSting)) {
        getTableFromString(fileSting, table);
    }
    return 1;

}