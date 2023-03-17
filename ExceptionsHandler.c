#include <stdlib.h>
#include <string.h>
#include "ExceptionsHandler.h"
#include "stdio.h"

char *getExceptionMessage(ExceptionsTypes exceptionType) {
    switch (exceptionType) {
        case NOT_INT_VALUE: return strdup("given input is not integer");
        case INPUT_NOT_IN_RANGE: return strdup("input value is not int given range");
        case TABLE_OVERFLOW: return strdup("table is overflow, clear it first");
        case NO_SUCH_FILE: return strdup("no such file");
        case INCORRECT_FILE_FORMAT: return strdup("file format is incorrect");
        case UNKNOWN_KEY: return strdup("given key or version doesn't exist");
        default: return strdup("unknown error");
    }
}

void throughException(ExceptionsTypes exceptionType) {
    char* errorMessage = getExceptionMessage(exceptionType);
    printf("ERROR: %s\n", errorMessage);
    free(errorMessage);
}