#ifndef LAB3_2_EXCEPTIONSHANDLER_H
#define LAB3_2_EXCEPTIONSHANDLER_H

typedef enum ExceptionsTypes {
    NOT_INT_VALUE,
    INPUT_NOT_IN_RANGE,
    TABLE_OVERFLOW,
    NO_SUCH_FILE,
    INCORRECT_FILE_FORMAT
} ExceptionsTypes;

char *getExceptionMessage(ExceptionsTypes exceptionType);
void throughException(ExceptionsTypes exceptions);

#endif //LAB3_2_EXCEPTIONSHANDLER_H
