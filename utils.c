#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

ResponsesTypes getDirToFile(char **fileName) {
    if (fileName == NULL) return COMMON_EXCEPTION;

    char *postfix = strdup(".bin");
    char *prefix = strdup("files/");

    char *dirToFile = calloc((strlen(prefix) + strlen(*fileName) + strlen(postfix) + 1), sizeof(char));
    *fileName = realloc(*fileName,(strlen(prefix) + strlen(*fileName) + strlen(postfix) + 1) * sizeof(char));

    strcpy(dirToFile, prefix);
    strcat(dirToFile, *fileName);
    strcat(dirToFile, postfix);
    strcpy(*fileName, dirToFile);

    free(dirToFile);
    free(postfix);
    free(prefix);
    if (fileName == NULL) return COMMON_EXCEPTION;
    return SUCCESS_RESPONSE;
}