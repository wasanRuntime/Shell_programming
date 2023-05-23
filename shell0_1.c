#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main(void) {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("#cisfun$ ");

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;  // Exit the shell on EOF (Ctrl+D)
        }

        // Remove trailing newline character
        command[strcspn(command, "\n")] = '\0';

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            char *args[] = {command, NULL};

            execve(command, args, NULL);

            // execve will only return if an error occurred
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL);  // Wait for the child process to complete
        }
    }

    return 0;
}

