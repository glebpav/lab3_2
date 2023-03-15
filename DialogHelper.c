#include <stdio.h>
#include "DialogHelper.h"

int selectOperation(char **commandsMessages, int countOfMessages) {

    char *errmsg = "";
    int rc;
    int i, n;

    do {
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";
        for (i = 0; i < countOfMessages; ++i) puts(commandsMessages[i]);
        puts("Make your choice: --> ");
        n = getInt(&rc);
        if (n == 0) rc = 0;
    } while (rc < 0 || rc >= commandsMessages);
}