#include "prompt.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <spawn.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>


// Main method to drive program
int main(){
    
    while(1){
        char *prompt = build_prompt();
        
        char * input = readline(prompt);

        add_history(input);

        if (strchr(input, '|')) {
            pipe_command(input);
        } else {
            execute_commands(input);
        }

        free(input);
        free(prompt);
    }
}
