#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ConsoleCommandsHelper.h"

// Why you cannot return fixed size / const array in C?
// https://stackoverflow.com/questions/29088462/why-you-cannot-return-fixed-size-const-array-in-c

int exitProgram(Table *table) {
    if (table->keySpace != NULL) free(table);
    printf("%s\n", "Goodbye, dear!");
}

int findElementByKey(Table *inputTable) {
    printf("hereeeee");
}

int addElement(Table *inputTable) {
    return 0;
}

int findElementByKeyAndVersion(Table *inputTable) {
    return 0;
}

int deleteElementByKey(Table *inputTable) {
    return 0;
}

int deleteOldVersionsWithKey(Table *inputTable) {
    return 0;
}