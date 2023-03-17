#include "FileHelper.h"
#include "localeTable/TableHelper.h"
#include <errno.h>
#include "stdio.h"

int isDigit(char *text) {
    int j;
    j = strlen(text);
    while (j--) {
        if (text[j] > 47 && text[j] < 58) continue;
        return 0;
    }
    return 1;
}

int readFile(char *fileName, char **outputString) {
    FILE *fp;

    char *prefix = strdup("files/");
    char *filePath = calloc(strlen(prefix) + strlen(fileName) + 1, sizeof(char));
    filePath = strcat(filePath, prefix);
    filePath = strcat(filePath, fileName);

    if ((fp = fopen(filePath, "r+")) == NULL) {
        throughException(NO_SUCH_FILE);
        return 0;
    }

    free(prefix);
    free(filePath);

    char *item = calloc(128, sizeof(char));
    *outputString = calloc(128, sizeof(char));
    int lineSize = 0;

    while (1) {

        int ret = fscanf(fp, "%s", item);
        if (ret == 1) {
            printf("item with len %llu is: %s\n", strlen(item), item);
            *outputString = realloc(*outputString, (1 + lineSize + strlen(item)) * sizeof(char));
            *outputString = strcat(*outputString, item);
            lineSize = strlen(*outputString);
        } else if (errno != 0) {
            perror("scanf:");
            break;
        } else if (ret == EOF) {
            break;
        } else {
            puts("No or partial match.\n");
            break;
        }
    }
    if (feof(fp)) {
        fclose(fp);
    }

    free(item);
}

int getTableFromString(char *inputString, Table *table) {
    char *strDup = strdup(inputString);
    char *strBuf = strtok(strDup, ";");
    char **linesArray = NULL;
    int countOfLines = 0;
    while (strBuf != NULL) {
        printf("line of content is: %s\n", strBuf);
        linesArray = realloc(linesArray, (countOfLines + 1) * sizeof(char *));
        linesArray[countOfLines] = strdup(strBuf);
        countOfLines += 1;
        strBuf = strtok(NULL, ";");
    }
    freeTable(table);
    *table = initTable();
    KeySpace row = {0, 0, 0};
    for (int i = 0; i < countOfLines; i++) {
        strBuf = strtok(linesArray[i], ",");
        int columnCounter;
        columnCounter = 0;
        while (strBuf != NULL) {
            printf("col count %d, value %s\n", columnCounter, strBuf);
            if (!isDigit(strBuf) || strcmp("", strBuf) == 0) {
                throughException(INCORRECT_FILE_FORMAT);
                return 0;
            }
            switch (columnCounter) {
                case 0: {
                    row.key = atoi(strBuf);
                    break;
                }
                case 1: {
                    row.release = atoi(strBuf);
                    break;
                }
                case 2: {
                    row.data = atoi(strBuf);
                    break;
                }
                default: {
                    throughException(INCORRECT_FILE_FORMAT);
                    return 0;
                }
            }
            columnCounter += 1;
            strBuf = strtok(NULL, ",");
        }
        if (columnCounter > 3) {
            throughException(INCORRECT_FILE_FORMAT);
            return 0;
        }
        inputNewRow(table, row.key, row.data);

    }

}
