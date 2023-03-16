#include "ExceptionsHandler.h"
#include "stdio.h"

void throughException(ExceptionsTypes exceptionType) {
    switch (exceptionType) {
        case NOT_INT_VALUE: {
            printf("%s\n", "ERROR: given input is not integer");
            break;
        }
        case INPUT_NOT_IN_RANGE: {
            printf("%s\n", "ERROR: input value is not int given range");
        }
    }
}