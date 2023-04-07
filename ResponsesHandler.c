#include <stdlib.h>
#include <string.h>
#include "ResponsesHandler.h"
#include "stdio.h"

char *getExceptionMessage(ResponsesTypes exceptionType) {
    switch (exceptionType) {
        case NOT_INT_VALUE_EXCEPTION:
            return strdup("given input is not integer");
        case INPUT_NOT_IN_RANGE_EXCEPTION:
            return strdup("input value is not int given range");
        case TABLE_OVERFLOW_EXCEPTION:
            return strdup("table is overflow, clear it first");
        case NO_SUCH_FILE_EXCEPTION:
            return strdup("no such fileDescriptor");
        case INCORRECT_FILE_FORMAT_EXCEPTION:
            return strdup("fileDescriptor format is incorrect");
        case UNKNOWN_KEY_EXCEPTION:
            return strdup("given key or version doesn't exist");
        default:
            return strdup("unknown error");
    }
}

void throughException(ResponsesTypes exceptionType) {
    char *errorMessage = getExceptionMessage(exceptionType);
    printf("\033[1;31m");
    printf("ERROR: %s\n", errorMessage);
    printf("\033[0m");
    free(errorMessage);
}

bool isException(ResponsesTypes response) {
    if (response == NOT_INT_VALUE_EXCEPTION
        || response == INPUT_NOT_IN_RANGE_EXCEPTION
        || response == TABLE_OVERFLOW_EXCEPTION
        || response == NO_SUCH_FILE_EXCEPTION
        || response == INCORRECT_FILE_FORMAT_EXCEPTION
        || response == UNKNOWN_KEY_EXCEPTION
        || response == FILE_EXCEPTION)
        return true;
    return false;
}