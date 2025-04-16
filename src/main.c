#include "prompt.h"
#include "input.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <spawn.h>
#include <sys/wait.h>


// Main method to drive program
int main(){
    
    while(1){
        char *prompt = build_prompt();
        printf("%s", prompt);
        char * input = read_input();

        if (strchr(input, '|')) {
            pipe_command(input);
        } else {
            execute_commands(input);
        }

        free(prompt);
    }
}
