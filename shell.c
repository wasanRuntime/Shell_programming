#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("#cisfun$ ");
        fflush(stdout);  // Make sure the prompt is displayed

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;  // Handle end of file (Ctrl+D)
        }

        command[strcspn(command, "\n")] = '\0';  // Remove trailing newline character

        if (strcmp(command, "exit") == 0) {
            break;
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            char *args[] = {command, NULL};
            if (execv(command, args) == -1) {
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

    return 0;
}

