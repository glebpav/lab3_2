#ifndef LAB3_2_RESPONSESHANDLER_H
#define LAB3_2_RESPONSESHANDLER_H

#include <stdbool.h>

typedef enum ResponsesTypes {
    NOT_INT_VALUE_EXCEPTION,
    INPUT_NOT_IN_RANGE_EXCEPTION,
    TABLE_OVERFLOW_EXCEPTION,
    NO_SUCH_FILE_EXCEPTION,
    INCORRECT_FILE_FORMAT_EXCEPTION,
    UNKNOWN_KEY_EXCEPTION,
    COMMON_EXCEPTION,
    FILE_EXCEPTION,

    SUCCESS_RESPONSE
} ResponsesTypes;

bool isException(ResponsesTypes response);
char *getExceptionMessage(ResponsesTypes exceptionType);
void throughException(ResponsesTypes exceptions);

#endif //LAB3_2_RESPONSESHANDLER_H
