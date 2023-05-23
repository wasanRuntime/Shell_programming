#include<stdio.h>
#include <unistd.h>
int main(void)
{
	pid_t pid;
	printf("Before fork I was one\n");
	fork();
	if (pid == -1)
	{
		perror ("Unsuccessful\n");
		return 0;
	}
	printf("After fork I became two\n");

	if (pid == 0)
	{
		sleep(5);
		printf("I am the child\n");
	}
	else
	{
		printf("Iam the parent\n");
	}

	return 0;
}	
