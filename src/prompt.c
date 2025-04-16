#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "prompt.h"

// Method to build a prompt using the current working directory
char *build_prompt(){
    
    // Call getcwd and store in cwd 
    char *cwd = getcwd(NULL, 0);
    
    // Check if getcwd failed
    if(cwd == NULL){
        perror("cwd");
        return NULL;
    }

    // Allocate memory space for prompt
    size_t prompt_len = (strlen(cwd) + 3);
    char *prompt = malloc(prompt_len);

    // Check if prompt malloc failed
    if(prompt == NULL){
        perror("prompt malloc");
        free(prompt);
        return NULL;
    }

    // Create prompt by appending $ to cwd
    strcpy(prompt, cwd);
    strcat(prompt, "$ ");

    free(cwd);
    
    return prompt;
}