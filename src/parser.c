#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parser.h"

// Method to parse input into an array to use as command and arguments
char **parse_input(char *input){

    // Get the command entered from input
    char *token = strtok(input, " ");
    
    // Allocate memory for array 
    char **args = malloc(sizeof (char *) * 64);

    int i = 0;

    // Iterate through tokens, setting each array element to token value
    while(token && i < 63){
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    // NULL terminate end of array
    args[i] = NULL;

    return args;
}