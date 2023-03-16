#include <stdio.h>

int getInt(int *var) {
    int res = scanf("%d",  var);
    return res;
}

int selectOperation(const char *commandsMessages[], int countOfMessages) {
    char *repeatMessage = "";
    int userInput, i, res;

    do {
        puts(repeatMessage);
        for (i = 0; i < countOfMessages; ++i) puts(commandsMessages[i]);
        puts("Make your choice: --> ");
        res = getInt(&userInput);
        if (res == 0) {
            // Error: input value isn't an integer
            //TODO: handle error
        } else if (res == EOF) {
            // TODO: Exit program
            return 0;
        }
        repeatMessage = "Please, repeat input!";
    } while (res <= 0 || userInput >= countOfMessages);
    return userInput;
}