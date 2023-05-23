#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

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

        char *arguments[MAX_ARGUMENTS];
        char *token = strtok(command, " ");
        int i = 0;

        while (token != NULL && i < MAX_ARGUMENTS - 1) {
            arguments[i] = token;
            token = strtok(NULL, " ");
            i++;
        }

        arguments[i] = NULL;

        if (arguments[0] != NULL) {
            if (strcmp(arguments[0], "exit") == 0) {
                // Exit the shell
                printf("Exiting the shell...\n");
                break;
            }

            pid_t pid = fork();

            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process
                execvp(arguments[0], arguments);

                // execvp will only return if an error occurred
                perror("execvp");
                exit(EXIT_FAILURE);
            } else {
                // Parent process
                wait(NULL);  // Wait for the child process to complete
            }
        }
    }

    return 0;
}

