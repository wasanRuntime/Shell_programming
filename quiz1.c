#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * main - Write a UNIX command line interpreter.
 * @void: returns nothing
 * Return: 0 on success
 **/

int main(void)
{
	pid_t pid;
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		printf("#cisfun$ ");

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			puts("");/*Gets to the next line*/
			break;    /* Exit the shell on EOF (Ctrl+D)*/
		}

		command[strcspn(command, "\n")] = '\0';
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/*child running*/
			char *args[] = {command, NULL};

			execve(command, args, NULL);

			/*execve will only return when an error occurred*/
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			/*parent process wait for the child process to complete*/
			wait(NULL);
		}
	}
	return (0);
}

