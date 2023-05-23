#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>

#define MAX_ARGUMENTS 10
#define MAX_ARGUMENT_LENGTH 20

int main() {
    char command[MAX_ARGUMENTS][MAX_ARGUMENT_LENGTH];
    char* arguments[MAX_ARGUMENTS];

    while (1) {
        printf(":) ");
        fflush(stdout);

        if (fgets(command[0], sizeof(command[0]), stdin) == NULL) {
            printf("\n");
            break;
        }

        command[0][strcspn(command[0], "\n")] = '\0';

        char *token = strtok(command[0], " ");
        int arg_index = 0;
        while (token != NULL && arg_index < MAX_ARGUMENTS - 1) {
            arguments[arg_index] = token;
            token = strtok(NULL, " ");
            arg_index++;
        }
        arguments[arg_index] = NULL;

        if (strcmp(arguments[0], "exit") == 0) {
            exit(0);  // Terminate the shell
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execvp(arguments[0], arguments) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}

