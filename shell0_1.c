#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 *main - Write a UNIX command line interpreter.
 *@void: returns nothing
 *Return: 0 on success
 **/

#define MAX_COMMAND_LENGTH 100

int main(void)
{
	pid_t pid;
	char command[MAX_COMMAND_LENGTH];

	for (;;)
	{
       		printf("#cisfun$ ");

        	if (fgets(command, sizeof(command), stdin) == NULL)
        	puts("");/*Goes to newline(Always)*/
        	break;  /*Exit the shell on EOF (Ctrl+D)*/
     
        	/*Remove trailing newline character*/
        	command[strcspn(command, "\n")] = '\0';

        	pid = fork();

        	if (pid == -1)
		{
        		perror("fork");
        		exit(EXIT_FAILURE);
        	}
		else if (pid == 0)
		{
           		/* Child process*/
        		char *args[] = {command, NULL};

         		execve(command, args, NULL);

                	/* execve will only return if an error occurred*/
        		perror("execve");
            		exit(EXIT_FAILURE);
        	}
		else
		{
        		/* Parent process*/
        		wait(NULL);  /* Wait for the child process to complete*/
		}
	}
	return (0);
}
