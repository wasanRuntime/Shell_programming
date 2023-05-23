#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGUMENTS 10
#define MAX_ARGUMENT_LENGTH 20

int main() {
    char* command[MAX_ARGUMENTS];

    for (int i = 0; i < MAX_ARGUMENTS; i++) {
        command[i] = malloc(MAX_ARGUMENT_LENGTH * sizeof(char));
    }

    while (1) {
        printf("#cisfun$ ");
        fflush(stdout);

        if (fgets(command[0], MAX_ARGUMENT_LENGTH, stdin) == NULL) {
            printf("\n");
            break;
        }

        command[0][strcspn(command[0], "\n")] = '\0';

        char* token = strtok(command[0], " ");
        int arg_index = 0;
        while (token != NULL && arg_index < MAX_ARGUMENTS) {
            strcpy(command[arg_index], token);
            token = strtok(NULL, " ");
            arg_index++;
        }

        if (strcmp(command[0], "exit") == 0) {
            break;
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execv(command[0], command) == -1) {
                perror("execv");
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

    for (int i = 0; i < MAX_ARGUMENTS; i++) {
        free(command[i]);
    }

    return 0;
}

