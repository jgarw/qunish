#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "input.h"

// Method to read input entered from user
char *read_input() {
    char *input = NULL;
    size_t size = 0;

    // Read input from the user
    ssize_t len = getline(&input, &size, stdin);

    if (len == -1) {
        perror("getline");
        free(input);
        return NULL;
    }

    // Remove trailing newline character
    if(input[len - 1] == '\n'){
        input[len -1] = '\0';
    }

    return input;
}