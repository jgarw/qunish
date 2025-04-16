#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <spawn.h>
#include <sys/wait.h>
#include "executor.h"
#include "parser.h"

// Get environment variables
extern char **environ; 

// Method to change directories
int cd(char *path){
    return chdir(path);
}


// Method to spawn process to run external command
int spawn_process(char **args){

    pid_t pid;
    int status;

    // Spawn process using arg[0] as command, and subsequent array elements as arguments
    if(posix_spawnp(&pid, args[0], NULL, NULL, args, environ) != 0){
        perror("spawn error");
        return 1;
    }

    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    return 0;
    
}

// Method for executing pipe commands
int pipe_command(char *input){

    // pipefd[0] = read, pipefd[1] = write
    int pipefd[2];

    // Create pipe
    if(pipe(pipefd) != 0){
        perror("pipe failed");
        return 1;
    }

    // Iterator for splitting commands
    int i = 0;

    // Split input into commands seperated by |
    char *token = strtok(input, "|");

    // Allocate memory for array of commands
    char **cmds = malloc(sizeof (char *) * 64);

    // Iterate through input and split at every pipe |
    while(token != NULL && i < 63){
        cmds[i++] = strdup(token);
        token = strtok(NULL, "|");
    }

    // NULL terminate array of commands
    cmds[i] = NULL;

    // Use parse_input method to split the cmds elements into commands and arguments and store in argv# arrays
    char **argv1 = parse_input(cmds[0]);
    char **argv2 = parse_input(cmds[1]);

    pid_t pid1, pid2;

    // Setup actions for write end posix spawn
    posix_spawn_file_actions_t actions1;
    posix_spawn_file_actions_init(&actions1);
    // Set pipefd[1] to write
    posix_spawn_file_actions_adddup2(&actions1, pipefd[1], STDOUT_FILENO);
    // Close unused read end pipefd[1]
    posix_spawn_file_actions_addclose(&actions1, pipefd[0]);

    // Spawn process using commands and arguments extracted from cmds array and stored into argv1
    if (posix_spawnp(&pid1, argv1[0], &actions1, NULL, argv1, environ) != 0) {
        perror("posix_spawnp (cmd1)");
        return 1;
    }

    posix_spawn_file_actions_destroy(&actions1);
    free(argv1);

    posix_spawn_file_actions_t actions2;
    posix_spawn_file_actions_init(&actions2);
    posix_spawn_file_actions_adddup2(&actions2, pipefd[0], STDIN_FILENO);
    posix_spawn_file_actions_addclose(&actions2, pipefd[1]);

    // Spawn process using commands and arguments extracted from cmds array and stored into argv1
    if (posix_spawnp(&pid2, argv2[0], &actions2, NULL, argv2, environ) != 0) {
        perror("posix_spawnp (cmd2)");
        return 1;
    }

    posix_spawn_file_actions_destroy(&actions2);
    free(argv2);

    free(cmds);

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;


}

// Method to handle executing commands based on input
int execute_commands(char *input){
    char **args = parse_input(input);
        
        // Handle "exit" command
        if(strcmp(args[0], "exit") == 0){
            printf("Exiting shell...\n");
            free(input);
            free(args);
            exit(0);
        }
        else if(strcmp(args[0], "cd") == 0){
            cd(args[1]);
        }
        else{
            spawn_process(args);
        }

        free(input);
        free(args);
        return 0;
}