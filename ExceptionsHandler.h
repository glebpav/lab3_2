#ifndef LAB3_2_EXCEPTIONSHANDLER_H
#define LAB3_2_EXCEPTIONSHANDLER_H

typedef enum ExceptionsTypes {
    NOT_INT_VALUE,
    INPUT_NOT_IN_RANGE
} ExceptionsTypes;

void throughException(ExceptionsTypes exceptions);

#endif //LAB3_2_EXCEPTIONSHANDLER_H
