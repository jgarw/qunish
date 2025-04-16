#ifndef EXECUTOR_H
#define EXECUTOR_H

// Get environment variables
extern char **environ; 


// Method to spawn process to run external command
int spawn_process(char **args);
// Method to change directories
int cd(char *path);
// Method for executing pipe commands
int pipe_command(char *input);
// Method to handle executing commands based on input
int execute_commands(char *input);


#endif